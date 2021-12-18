// Pipe Implementation for Unix

#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

#include "pipe.hpp"

namespace pipette
{
int
pipe::open (const char *cmdline, bool write)
{
  fp = popen (cmdline,
              write ? "w" : "r"); // rb & wb are not working for some reason
  if (!fp)
    return 0; // return WEXITSTATUS(pclose(fp));
  // fcntl(fileno(fp), F_SETPIPE_SZ, 67108864/*64MB*/);	// Increasing Pipe
  // Buffer
  else
    return 1;
}

int
pipe::close ()
{
  if (fp)
    {
      return pclose (fp);
      fp = NULL;
    }
  else
    return 0;
}

size_t
pipe::read (uint8_t *buffer, size_t size) const
{
  return fread (buffer, 1, size, fp);
}

size_t
pipe::write (uint8_t *buffer, size_t size) const
{
  return fwrite (buffer, 1, size, fp);
}
} // namespace pipette
