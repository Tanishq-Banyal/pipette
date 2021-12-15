#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>

#include "fifo.hpp"

namespace pipette
{

int fifo::open(const char* path, const char mode)
{
	if (!fd)
	{
		fd = mkfifo(path, mode == 'w' ? O_WRONLY : O_RDONLY);
	}
	else return 69;
}

int fifo::read(void* buf, size_t num) const
{
	return ::read(fd, buf, num);
}

int fifo::write(const void* buf, size_t num) const
{
	return ::write(fd, buf, num);
}

int fifo::close()
{
	if (fd) return ::close(fd);
	else return 69;
}

}
