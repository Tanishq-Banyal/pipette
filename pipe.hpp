#include <cstdio>
#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <cstddef>
#include <fcntl.h>

namespace pipette
{

class pipe
{
private:
	FILE* fp = NULL;
public:
	int open(const char* cmdline, bool write = false);
	size_t read(uint8_t* buffer, size_t size) const;
	size_t write(uint8_t* buffer, size_t size) const;
	int close();
	~pipe() {close();}
};

}
