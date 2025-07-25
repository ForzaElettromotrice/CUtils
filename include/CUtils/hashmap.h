//
// Created by f3m on 07/05/25.
//

#pragma once

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Hashmap
{
    size_t n;
    size_t dim;
    uint64_t *keys;
    void **values;
} Hashmap_t;

int initHashmap(Hashmap_t *hashmap, size_t dim);
void freeHashmap(const Hashmap_t *hashmap);

int setByHash(uint64_t hashKey, const void *val, size_t size, Hashmap_t *hashmap);
int setByStr(const char *key, const void *val, size_t size, Hashmap_t *hashmap);

void *getByHash(uint64_t hashKey, const Hashmap_t *hashmap);
void *getByStr(const char *key, const Hashmap_t *hashmap);

void removeKey(const char *key, const Hashmap_t *hashmap);
#ifdef __cplusplus
}
#endif

