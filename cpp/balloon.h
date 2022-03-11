#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <vector>
#include <openssl/sha.h>

#define BLOCK_SIZE (32u)

class BalloonHasher {
    public:
        int s_cost = 256;
        int t_cost = 3;
        int delta = 3;

    public:
        typedef std::vector<uint8_t> bytes_t;
        bool balloon_hash (uint8_t* out, size_t out_len, const uint8_t* nonce, size_t nonce_len, const uint8_t* salt, size_t salt_len);
};