#include "balloon.h"

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

bool BalloonHasher::balloon_hash(uint8_t* out, size_t out_len, const uint8_t* nonce, size_t nonce_len, const uint8_t* salt, size_t salt_len) {
    uint256_t cnt = 0;
    uint8_t **buf = (uint8_t **) calloc(s_cost, sizeof(uint8_t*)); 
    for(int i = 0; i < s_cost; i++) {
        buf[i] = (uint8_t *) calloc(BLOCK_SIZE, sizeof(uint8_t));
    }
    SHA256_CTX c;

    // Step 1. Expand input into buffer.
    if (!SHA256_Init(&c)) return false;
    if (!SHA256_Update(&c, (uint8_t*)&cnt, sizeof((uint8_t *)&cnt))) return false;
    if (!SHA256_Update(&c, salt, salt_len)) return false;
    if (!SHA256_Update(&c, nonce, nonce_len)) return false;
    if (!SHA256_Final(buf[0], &c)) return false;
    cnt++;

    for (int m = 1; m < s_cost; m++) {
        if (!SHA256_Init(&c)) return false;
        if (!SHA256_Update(&c, (uint8_t*)&cnt, sizeof((uint8_t *)&cnt))) return false;
        if (!SHA256_Update(&c, buf[m - 1], BLOCK_SIZE)) return false;
        if (!SHA256_Final(buf[m], &c)) return false;
        cnt++;
    }

    // Step 2. Mix buffer contents.
    for (uint256_t t = 0; t < t_cost; t++) {
        for (uint256_t m = 0; m < s_cost; m++) {
            // Step 2a. Hash last and current blocks.
            if (!SHA256_Init(&c)) return false;
            if (!SHA256_Update(&c, (uint8_t*)&cnt, sizeof((uint8_t *)&cnt))) return false;
            if (m == 0)  {if (!SHA256_Update(&c, buf[s_cost - 1], BLOCK_SIZE)) return false;}
            else {if (!SHA256_Update(&c, buf[(int)m - 1], BLOCK_SIZE)) return false;}
            if (!SHA256_Update(&c, buf[(int)m], BLOCK_SIZE)) return false;
            if (!SHA256_Final(buf[(int)m], &c)) return false;
            cnt++;

            // Step 2b. Hash in pseudorandomly chosen blocks.
            for (uint256_t i = 0; i < delta; i++) {
                uint256_t idx_block, other;
                if (!SHA256_Init(&c)) return false;
                if (!SHA256_Update(&c, (uint8_t *)&t, sizeof((uint8_t *)&t))) return false;
                if (!SHA256_Update(&c, (uint8_t *)&m, sizeof((uint8_t *)&m))) return false;
                if (!SHA256_Update(&c, (uint8_t *)&i, sizeof((uint8_t *)&i))) return false;
                if (!SHA256_Final((uint8_t *)&idx_block, &c)) return false;
                if (!SHA256_Init(&c)) return false;
                if (!SHA256_Update(&c, (uint8_t*)&cnt, sizeof((uint8_t *)&cnt))) return false;
                if (!SHA256_Update(&c, salt, salt_len)) return false;
                if (!SHA256_Update(&c, (uint8_t *)&idx_block, BLOCK_SIZE)) return false;
                if (!SHA256_Final((uint8_t *)&other, &c)) return false;
                cnt++;

                uint256_t other_mod = integer_modulus(other, s_cost);
                if (!SHA256_Init(&c)) return false;
                if (!SHA256_Update(&c, (uint8_t*)&cnt, sizeof((uint8_t *)&cnt))) return false;
                if (!SHA256_Update(&c, buf[(int)m], BLOCK_SIZE)) return false;           
                if (!SHA256_Update(&c, buf[(int)other_mod], BLOCK_SIZE)) return false;
                if (!SHA256_Final(buf[(int)m], &c)) return false;
                cnt++;
            }
        }
    }

    // Step 3. Extract output from buffer.
    assert(out_len == BLOCK_SIZE);
    memcpy(out, buf[s_cost - 1], out_len);
    for(int i = 0; i < s_cost; i++) {
        free(buf[i]);
    }
    free(buf);
    return true;
}