#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>

namespace pipette
{

class pipe_bi
{
private:
  int parent_pipes[2];
  int child_pipes[2];
  int pid;

public:
  int open (const char *cmdline);
  size_t read (void *buffer, size_t size) const;
  size_t write (void *buffer, size_t size) const;
  int close ();
  ~pipe_bi () { close (); }
};
} // namespace pipette
