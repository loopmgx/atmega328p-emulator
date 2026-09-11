#ifndef ERROR_H
#define ERROR_H

void error(const char* fmt, const char* funct, const int ret);
int warning(const char* fmt, const char* funct, const int ret);

#endif // ERROR_H
