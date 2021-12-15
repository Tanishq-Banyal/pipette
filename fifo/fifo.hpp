#include <cstdio>

namespace pipette
{

class fifo
{
private:
	int fd = 0;

public:
	int open(const char* path, const char mode);
	int read(void* buf, size_t num) const;
	int write(const void* buf, size_t num) const;
	int close();
	fifo(const char* path, const char mode) {open(path, mode);}
   ~fifo() {close();}
};

}
