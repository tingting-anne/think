#ifndef _THINK_UTILS_H_
#define _THINK_UTILS_H_
//math
int log2i(unsigned int x);

//system
int linux_system(const char* command);

//net
char * Ip2Str(const unsigned int iIp, char *pStr);
unsigned int Str2Ip(const char *pStr);
int nonblock(int fd);

#endif //_THINK_UTILS_H_
