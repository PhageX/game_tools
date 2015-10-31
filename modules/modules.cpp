#include "modules.hpp"

#include <Windows.h>

using std::pair;
using std::string;

namespace modules {

pair<uintptr_t, size_t> get_memory_location(HMODULE module, HANDLE process) {
    if(process == HANDLE(-1)) {
        // In case this ocnstant changes in other versions of windows
        process = GetCurrentProcess();
    }

    MODULEINFO modinfo;

    if(GetModuleInformation(process, module, &modinfo, sizeof(modinfo)) == FALSE) {
        return std::make_pair(0, 0);
    }

    return std::make_pair(reinterpret_cast<uintptr_t>(modinfo.lpBaseOfDll), static_cast<size_t>(modinfo.SizeOfImage));
}

string get_directory(HMODULE module) {
	char buf[MAX_PATH];

	DWORD path_length = GetModuleFileName(module, buf, MAX_PATH);

	if (path_length == 0) {
		return "";
	}

	string path(buf, path_length);
	
	auto x = path.substr(0, path.find_last_of("\\") + 1);
	return x;
}

}; //namespace modules
