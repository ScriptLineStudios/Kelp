#ifndef HASH_H
#define HASH_H

#include <stdint.h>

uint64_t hash(const char *key);

#endif

#ifdef HASH_IMPLEMENTATION 

//thanks https://stackoverflow.com/questions/7666509/hash-function-for-string
uint64_t hash(const char *key)
{
    uint64_t h = 525201411107845655;
    for (;*key;++key) {
        h ^= *key;
        h *= 0x5bd1e9955bd1e995;
        h ^= h >> 47;
    }
    return h;
}

#endif