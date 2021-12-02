
// This file needs some refactoring including windows compatibility

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
   ~pipe() { Close(); }

	int open(const char* cmdline, bool write = false)
	{
		fp = popen(cmdline, write ? "w" : "r");	// rb & wb are not working for some reason
		if (!fp) return -1; // return WEXITSTATUS(pclose(fp));
		fcntl(fileno(fp), F_SETPIPE_SZ, 67108864/*64MB*/);	// Increasing Pipe Buffer
		return 0;
	}

	int close()
	{
		if (fp)
		{
			pclose(fp);
			fp = NULL;
		}
		return 0;
	}

	size_t read(uint8_t* buffer, size_t size)
	{
        return fread(buffer, 1, size, fp);
    }

	size_t write(uint8_t* buffer, size_t size)
	{
		return fwrite(buffer, 1, size, fp);
	}
};

}
