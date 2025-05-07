//
// Created by f3m on 07/05/25.
//

#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#define RED       "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW    "\033[33m"
#define BLUE      "\033[34m"
#define BOLD      "\033[1m"
#define ITALIC    "\033[3m"
#define UNDERLINE "\033[4m"
#define RESET     "\033[0m"


void logE(FILE *file, const char *msg, ...);
void logD(FILE *file, const char *msg, ...);
