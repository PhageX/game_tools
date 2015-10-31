#include "sigsearch.hpp"

#include <cstdint>

namespace sigsearch {

uintptr_t find_signature(const uint8_t* pattern, const uint8_t* mask, size_t search_size, uintptr_t scan_start, uintptr_t scan_end) {
    if (scan_end < scan_start) {
        std::swap(scan_start, scan_end);
    }

    for (uintptr_t search_base = scan_start; search_base < scan_end; search_base++) {
        auto scan_pos = search_base;
        size_t search_pos = 0;
        for (; search_pos < search_size; search_pos++, scan_pos++) {
            if (mask[search_pos] != 0 && *reinterpret_cast<uint8_t*>(scan_pos) != pattern[search_pos]) {
                break;
            }
        }

        if (search_pos == search_size) {
            return search_base;
        }
    }

    return 0;
}

}; // namespace sigsearch
