//
// Created by f3m on 07/05/25.
//

#include "logger.h"

#include <stdarg.h>
#include <time.h>


void logE_impl(FILE *file, const char *file_name, const int line, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    fprintf(file, RED "Error in %s at line %d: " RESET, file_name, line);
    vfprintf(file, msg, args);
    va_end(args);
    fflush(file);
}
void logD(FILE *file, const char *msg, ...)
{
#ifdef Debug
    char buffer[20];
    const time_t t = time(NULL);
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", localtime(&t));

    va_list args;
    va_start(args, msg);
    fprintf(file, YELLOW "DEBUG %s: " RESET, buffer);
    vfprintf(file, msg, args);
    va_end(args);
    fflush(file);
#endif
}
