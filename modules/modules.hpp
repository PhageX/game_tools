#include <windows.h>
#include <Psapi.h>
#include <utility>
#include <string>

namespace modules {

std::pair<uintptr_t, size_t> get_memory_location(HMODULE module, HANDLE process = HANDLE(-1));
std::string get_directory(HMODULE module);

}; //namespace modules
