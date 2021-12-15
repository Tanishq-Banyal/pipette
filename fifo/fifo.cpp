#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
	#include "fifo_nix.cpp"
#elif defined(_WIN32) || defined(_WIN64)
	#include "fifo_win.cpp"
#else
	#error "Unsupported OS !"
#endif
