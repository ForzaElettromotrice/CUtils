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


#define logE(file, msg, ...) logE_impl(file, __FILE_NAME__, __LINE__, msg, ##__VA_ARGS__)

void logE_impl(FILE *file, const char *file_name, const int line, const char *msg, ...);
void logD(FILE *file, const char *msg, ...);
