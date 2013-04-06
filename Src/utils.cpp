#ifndef _THINK_UTILS_
#define _THINK_UTILS_
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>

inline int log2i(unsigned int x)
{
	int r = 31;

	if (!x)
		return 0;
	if (!(x & 0xffff0000u)) {
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u)) {
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u)) {
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u)) {
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u)) {
		x <<= 1;
		r -= 1;
	}
	return r;
}

inline int linux_system(const char* command)
{
	if (command == NULL)
	{
		return (1);
	}

	int status = -1;
	pid_t pid = vfork();

	if (pid < 0)
	{
		printf("vfork() failed>>>>\n");
		status = -1;
	}
	else if (pid == 0)
	{
		printf("inclild ppid=%d pid=%d>>>>>\n", getppid(), getpid());
		execl("/bin/sh", "sh", "-c", command, (char*)0);
		_exit(127);	// 子进程执行正常则不会执行此语句
	}
	else
	{
		//tracef("in parent pid =%d>>>>\n", getppid());
		while (waitpid(pid, &status, 0) < 0)
		{
			if (errno != EINTR)
			{
				status = -1;
				break;
			}
		}
	}

	return status;
}

/*ipv4*/
char * Ip2Str(const unsigned int iIp, char *pStr)
{
	unsigned char i;
	unsigned char cIp[4];

	for (i=0; i<4; i++)
		cIp[i] = (unsigned char)( (iIp>>(i*8)) & (0xff) );

	sprintf(pStr, "%d.%d.%d.%d", cIp[0], cIp[1], cIp[2], cIp[3]);
	return pStr;
}


unsigned int Str2Ip(const char *pStr)
{
	signed char j = 0;
	unsigned char cIp;
	unsigned int uiRet = 0;
	const char *p = pStr;

	cIp = (unsigned char)atoi(p);
	uiRet |= ( ((unsigned int)(cIp)) << (j*8) );
	j++;

	while ( (*p != 0)
	        && j >= 0)
	{
		if (*p != '.')
		{
			p++;
			continue;
		}

		cIp = (unsigned char)atoi(++p);
		uiRet |= ( ((unsigned int)(cIp)) << (j*8) );
		j++;

	}

	return uiRet;
}

int nonblock(int fd)
{
	int	ret = -1;
#if defined(WIN32)
	unsigned long	on = 1;

	return (ioctlsocket(fd, FIONBIO, &on));
#else
	int	flags;

	if ((flags = fcntl(fd, F_GETFL, 0)) == -1)
		printf("nonblock: fcntl(F_GETFL): %d", errno);
	else if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) != 0)
		printf("nonblock: fcntl(F_SETFL): %d", errno);
	else
		ret = 0;	/* Success */

	return (ret);
#endif 
}


#endif //_THINK_UTILS_H_
