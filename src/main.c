//
// Created by f3m on 07/05/25.
//

#include <stdlib.h>
#include <xxhash.h>

#include "../include/CUtils/logger.h"

int main()
{
    printf("%ld\n", XXH3_64bits("0", 1));
    logE(stderr, "prova\n");

    return EXIT_SUCCESS;
}
