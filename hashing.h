#ifndef HASHING_H
#define HASHING_H

#include <stdlib.h>
#include <stdint.h>

#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261

uint32_t simple_hash(char *key) {
    uint32_t hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash += key[i];
    }
    return hash;
    //return 0;
}


uint32_t djb2(char *key) {
    uint32_t hash = 5381;
    int c;
    while ((c = *key++))
        hash = ((hash << 5) + hash) + c;
    return hash;
//    return 0;
}

uint32_t fnv_hash(char *key)
{
    uint32_t hash = FNV_OFFSET_32;
    int c;
    while ((c = *key++))
    {
        hash ^= c; 
        hash *= FNV_PRIME_32;   
    }
    return hash;
}

uint32_t jenkins_one_at_a_time_hash(char *key)
{
    uint32_t hash, c;
    hash = 0;
    while ((c = *key++))
    {
        hash += c;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

#endif