#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/stat.h>

#include "fifo.hpp"

namespace pipette
{

int fifo::open(const char* path, const char mode)
{
	if (!fp) return mkfifo(path, mode == 'w' ? O_WRONLY : O_RDONLY);
	else return 69;
}

int fifo::read(void* buf, size_t num) const
{
	return std::fread(buf, 1, num, fp);
}

int fifo::write(void* buf, size_t num) const
{
	return std::fwrite(buf, 1, num, fp);
}

int fifo::close()
{
	if (fp) return std::fclose(fp);
	else return 69;
}

}
