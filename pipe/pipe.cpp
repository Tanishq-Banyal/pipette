#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	#include "pipe_nix.cpp"
#elif defined(_WIN32) || defined(_WIN64)
	#include "pipe_win.cpp"
#else
	#error "Unsupported OS !"
#endif
