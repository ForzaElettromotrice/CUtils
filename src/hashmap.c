//
// Created by f3m on 07/05/25.
//

#include "hashmap.h"

#include <errno.h>
#include <logger.h>
#include <stdint.h>
#include <string.h>
#include <xxhash.h>

struct Hashmap
{
    size_t n;
    size_t dim;
    uint64_t *keys;
    void **values;
};

int initHashmap(Hashmap_t *hashmap, size_t dim)
{
    if (dim == 0)
        dim = 512;
    hashmap->dim = dim;
    hashmap->keys = calloc(dim, sizeof(uint64_t));
    if (!hashmap->keys)
    {
        logE(stderr, "calloc:%s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    hashmap->values = calloc(dim, sizeof(void *));
    if (!hashmap->values)
    {
        free(hashmap->keys);
        logE(stderr, "calloc:%s\n", strerror(errno));
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
void freeHashmap(const Hashmap_t *hashmap)
{
    free(hashmap->keys);
    for (int i = 0; i < hashmap->dim; ++i)
    {
        if (hashmap->values[i] == NULL)
            continue;

        free(hashmap->values[i]);
    }
    free(hashmap->values);
}

void checkBalance(Hashmap_t *hashmap)
{
    //TODO: se il balance è sotto il 25% allora conviene ridurre la dimensione
    if (hashmap->n < hashmap->dim / 100 * 75)
        return;
    const size_t newDim = hashmap->dim * 2;
    uint64_t *temp = realloc(hashmap->keys, newDim);
    if (!temp)
    {
        logE(stderr, "realloc: %s\n", strerror(errno));
        return;
    }
    hashmap->keys = temp;
    void **temp2 = realloc(hashmap->values, newDim);
    if (!temp2)
    {
        logE(stderr, "realloc: %s\n", strerror(errno));
        return;
    }
    hashmap->values = temp2;


    size_t mSize = 0;
    uint64_t *toMoveK = malloc(hashmap->n * sizeof(uint64_t));
    if (!toMoveK)
    {
        logE(stderr, "malloc: %s\n", strerror(errno));
        return;
    }
    void **toMoveV = malloc(hashmap->n * sizeof(void *));
    if (!toMoveV)
    {
        free(toMoveK);
        logE(stderr, "malloc: %s\n", strerror(errno));
        return;
    }

    hashmap->dim = newDim;


    for (int i = 0; i < newDim; ++i)
    {
        const uint64_t hash = hashmap->keys[i];
        void *value = hashmap->values[i];

        if (hash == 0)
            continue;

        toMoveK[mSize] = hash;
        toMoveV[mSize++] = value;
        hashmap->keys[i] = 0;
        hashmap->values[i] = NULL;
    }

    for (int i = 0; i < mSize; ++i)
    {
        const uint64_t hashKey = toMoveK[i];

        size_t hashIdx = hashKey % hashmap->dim;

        uint64_t found = hashmap->keys[hashIdx++];
        while (found != 0)
        {
            if (found == hashKey)
                break;
            if (hashIdx == hashmap->dim)
                hashIdx = 0;
            found = hashmap->keys[hashIdx++];
        }
        hashIdx--;

        hashmap->keys[hashIdx] = hashKey;
        hashmap->values[hashIdx] = toMoveV[i];
    }

    free(toMoveK);
    free(toMoveV);
}


int setByKey(const char *key, const void *val, const size_t size, Hashmap_t *hashmap)
{
    const uint64_t hashKey = XXH3_64bits(key, strlen(key));

    size_t hashIdx = hashKey % hashmap->dim;

    uint64_t found = hashmap->keys[hashIdx++];
    while (found != 0)
    {
        if (found == hashKey)
            break;
        if (hashIdx == hashmap->dim)
            hashIdx = 0;
        found = hashmap->keys[hashIdx++];
    }
    hashIdx--;


    void *value = malloc(size);
    if (!value)
    {
        logE(stderr, "calloc: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    hashmap->keys[hashIdx] = hashKey;
    memcpy(value, val, size);
    hashmap->values[hashIdx] = value;

    hashmap->n++;

    checkBalance(hashmap);

    return EXIT_SUCCESS;
}
void *getByKey(const char *key, const Hashmap_t *hashmap)
{
    const uint64_t hashKey = XXH3_64bits(key, strlen(key));

    uint64_t hashIdx = hashKey % hashmap->dim;

    uint64_t found = hashmap->keys[hashIdx];
    while (found != 0)
    {
        if (found == hashKey)
            return hashmap->values[hashIdx];
        hashIdx++;
        if (hashIdx == hashmap->dim)
            hashIdx = 0;

        found = hashmap->keys[hashIdx];
    }

    return NULL;
}

void removeKey(const char *key, const Hashmap_t *hashmap)
{
    const uint64_t hashKey = XXH3_64bits(key, strlen(key));

    uint64_t hashIdx = hashKey % hashmap->dim;

    uint64_t found = hashmap->keys[hashIdx];
    while (found != 0)
    {
        if (found == hashKey)
        {
            hashmap->keys[hashIdx] = 0;
            free(hashmap->values[hashIdx]);
            hashmap->values[hashIdx] = NULL;
        }
        hashIdx++;
        if (hashIdx == hashmap->dim)
            hashIdx = 0;
        found = hashmap->keys[hashIdx];
    }
}
