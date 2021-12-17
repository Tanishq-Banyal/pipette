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

namespace pipette {
int pipe::open(const char *cmdline, bool write) {
  fp = popen(cmdline,
             write ? "w" : "r"); // rb & wb are not working for some reason
  if (!fp)
    return 0; // return WEXITSTATUS(pclose(fp));
  // fcntl(fileno(fp), F_SETPIPE_SZ, 67108864/*64MB*/);	// Increasing Pipe
  // Buffer
  else
    return 1;
}

int pipe::close() {
  if (fp) {
    return pclose(fp);
    fp = NULL;
  } else
    return 0;
}

size_t pipe::read(uint8_t *buffer, size_t size) const {
  return fread(buffer, 1, size, fp);
}

size_t pipe::write(uint8_t *buffer, size_t size) const {
  return fwrite(buffer, 1, size, fp);
}
int pipe_bi::open(const char *cmdline) {
  if (::pipe(parent_pipes) == -1)
    return -1;
  if (::pipe(child_pipes) == -1)
    return -1;
  pid = fork();
  if (pid != 0) {
    ::close(parent_pipes[0]);
    ::close(child_pipes[1]);
  } else {
    ::close(parent_pipes[1]);
    ::close(child_pipes[0]);
    dup2(parent_pipes[0], 0);
    dup2(child_pipes[1], 1);
    system(cmdline);
  }
  // fcntl(fileno(fp), F_SETPIPE_SZ, 67108864/*64MB*/);	// Increasing Pipe
  // Buffer
  return 0;
}

int pipe_bi::close() {
  ::close(parent_pipes[1]);
  ::close(child_pipes[0]);
  kill(pid, SIGTERM);
  return 0;
}

size_t pipe_bi::read(void *buffer, size_t size) const {
  return ::read(child_pipes[0], buffer, size);
}

size_t pipe_bi::write(void *buffer, size_t size) const {
  return ::write(parent_pipes[1], buffer, size);
}

} // namespace pipette
