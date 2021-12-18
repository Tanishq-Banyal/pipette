// Pipe Implementation for Unix

#include <cerrno>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

#include "pipe_bi.hpp"

namespace pipette
{
int
pipe_bi::open (const char *cmdline)
{
  if (::pipe (parent_pipes) == -1)
    return -1;
  if (::pipe (child_pipes) == -1)
    return -1;
  pid = fork ();
  if (pid != 0)
    {
      ::close (parent_pipes[0]);
      ::close (child_pipes[1]);
    }
  else
    {
      ::close (parent_pipes[1]);
      ::close (child_pipes[0]);
      dup2 (parent_pipes[0], 0);
      dup2 (child_pipes[1], 1);
      system (cmdline);
    }
  // fcntl(fileno(fp), F_SETPIPE_SZ, 67108864/*64MB*/);	// Increasing Pipe
  // Buffer
  return 0;
}

int
pipe_bi::close ()
{
  ::close (parent_pipes[1]);
  ::close (child_pipes[0]);
  kill (pid, SIGTERM);
  return 0;
}

size_t
pipe_bi::read (void *buffer, size_t size) const
{
  return ::read (child_pipes[0], buffer, size);
}

size_t
pipe_bi::write (void *buffer, size_t size) const
{
  return ::write (parent_pipes[1], buffer, size);
}

} // namespace pipette
