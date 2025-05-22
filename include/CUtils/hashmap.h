//
// Created by f3m on 07/05/25.
//

#pragma once

#include <stdlib.h>


typedef struct Hashmap Hashmap_t;

int initHashmap(Hashmap_t *hashmap, size_t dim);
void freeHashmap(const Hashmap_t *hashmap);

int setByKey(const char *key, const void *val, size_t size, const Hashmap_t *hashmap);
void *getByKey(const char *key, const Hashmap_t *hashmap);

void removeKey(const char *key, const Hashmap_t *hashmap);
