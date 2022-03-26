#include "balloon.h"
#include <assert.h>

void _init(uint8_t* integer) {
    for (int i = 0; i < BLOCK_SIZE; i++)
        integer[i] = 0;
}

void _increment(uint8_t* integer) {
    // if integer overflows, it just goes back to zero
    int i = BLOCK_SIZE - 1;
    bool carry;
    do {
        if (integer[i] >= 255) {
            carry = true;
            integer[i--] = 0;
        }
        else {
            carry = false;
            integer[i--]++;
        }
    } while (carry && i >= 0);
}

uint32_t _to_integer(uint8_t* integer) {
    uint32_t result = 0;
    int digit = 1;
    for (int i = BLOCK_SIZE - 1; i > BLOCK_SIZE - 5; i--) {
        result += digit * integer[i];
        digit <<= 8;
    }
    return result;
}

uint32_t _modulus(uint8_t* integer, int exp) {
    int _exp = exp;
    int mul = 1;
    int index = BLOCK_SIZE - 1;
    uint32_t result = 0;
    while (_exp >= 8) {
        result += mul * integer[index--];
        mul <<= 8;
        _exp -= 8;
    }
    result += mul * (integer[index] - ((integer[index] >> _exp) << _exp));
    return result;
}

bool BalloonHasher::balloon_hash(uint8_t* out, size_t out_len, const uint8_t* nonce, size_t nonce_len, const uint8_t* salt, size_t salt_len) {
    int exp_s_cost = 1;
    exp_s_cost <<= s_cost;

    uint8_t cnt[BLOCK_SIZE];
    _init(cnt);

    uint8_t **buf = (uint8_t **) calloc(exp_s_cost, sizeof(uint8_t*)); 
    for(int i = 0; i < exp_s_cost; i++) {
        buf[i] = (uint8_t *) calloc(BLOCK_SIZE, sizeof(uint8_t));
    }

    // Step 1. Expand input into buffer.
    SHA256_CTX c;
    if (!SHA256_Init(&c)) return false;
    if (!SHA256_Update(&c, cnt, BLOCK_SIZE)) return false;
    if (!SHA256_Update(&c, salt, salt_len)) return false;
    if (!SHA256_Update(&c, nonce, nonce_len)) return false;
    if (!SHA256_Final(buf[0], &c)) return false;
    _increment(cnt);

    for (int m = 1; m < exp_s_cost; m++) {
        if (!SHA256_Init(&c)) return false;
        if (!SHA256_Update(&c, cnt, BLOCK_SIZE)) return false;
        if (!SHA256_Update(&c, buf[m - 1], BLOCK_SIZE)) return false;
        if (!SHA256_Final(buf[m], &c)) return false;
        _increment(cnt);
    }

    uint8_t t[BLOCK_SIZE], m[BLOCK_SIZE], i[BLOCK_SIZE];
    // Step 2. Mix buffer contents.
    for (_init(t); _to_integer(t) < t_cost; _increment(t)) {
        for (_init(m); _to_integer(m) < exp_s_cost; _increment(m)) {
            int m_index = _to_integer(m);
            // Step 2a. Hash last and current blocks.
            if (!SHA256_Init(&c)) return false;
            if (!SHA256_Update(&c, cnt, BLOCK_SIZE)) return false;
            if (m_index == 0)  {if (!SHA256_Update(&c, buf[exp_s_cost - 1], BLOCK_SIZE)) return false;}
            else {if (!SHA256_Update(&c, buf[m_index - 1], BLOCK_SIZE)) return false;}
            if (!SHA256_Update(&c, buf[m_index], BLOCK_SIZE)) return false;
            if (!SHA256_Final(buf[m_index], &c)) return false;
            _increment(cnt);

            // Step 2b. Hash in pseudorandomly chosen blocks.
            for (_init(i); _to_integer(i) < delta; _increment(i)) {
                uint8_t idx_block[BLOCK_SIZE], other[BLOCK_SIZE];
                if (!SHA256_Init(&c)) return false;
                if (!SHA256_Update(&c, t, BLOCK_SIZE)) return false;
                if (!SHA256_Update(&c, m, BLOCK_SIZE)) return false;
                if (!SHA256_Update(&c, i, BLOCK_SIZE)) return false;
                if (!SHA256_Final(idx_block, &c)) return false;
                if (!SHA256_Init(&c)) return false;
                if (!SHA256_Update(&c, cnt, BLOCK_SIZE)) return false;
                if (!SHA256_Update(&c, salt, salt_len)) return false;
                if (!SHA256_Update(&c, idx_block, BLOCK_SIZE)) return false;
                if (!SHA256_Final(other, &c)) return false;
                _increment(cnt);

                uint32_t other_mod = _modulus(other, s_cost);
                if (!SHA256_Init(&c)) return false;
                if (!SHA256_Update(&c, cnt, BLOCK_SIZE)) return false;
                if (!SHA256_Update(&c, buf[m_index], BLOCK_SIZE)) return false;
                if (!SHA256_Update(&c, buf[other_mod], BLOCK_SIZE)) return false;
                if (!SHA256_Final(buf[m_index], &c)) return false;
                _increment(cnt);
            }
        }
    }

    // Step 3. Extract output from buffer.
    assert(out_len == BLOCK_SIZE);
    memcpy(out, buf[exp_s_cost - 1], out_len);
    for(int i = 0; i < exp_s_cost; i++) {
        free(buf[i]);
    }
    free(buf);
    return true;
}