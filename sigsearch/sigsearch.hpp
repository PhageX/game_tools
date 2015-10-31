#include <cstdint>
#include <array>
#include <utility>

namespace sigsearch {

template <size_t search_size>
class Signature {
public:
    constexpr Signature(std::array<uint8_t, search_size>&& pattern, std::array<uint8_t, search_size>&& mask, int offset) :
        pattern_(pattern), mask_(mask), offset_(offset) {}

    const std::array<uint8_t, search_size>& pattern() const { return pattern_; }
    const std::array<uint8_t, search_size>& mask() const { return mask_; }
    int offset() const { return offset_; }
     
    void destory();

private:
    std::array<uint8_t, search_size> pattern_;
    std::array<uint8_t, search_size> mask_;
    int offset_;
};

template <size_t search_size>
void Signature<search_size>::destory() {
    std::fill(pattern_.begin(), pattern_.end(), 0);
    std::fill(mask_.begin(), mask_.end(), 0);
}

uintptr_t find_signature(const uint8_t* pattern, const uint8_t* mask, size_t search_size, uintptr_t start, uintptr_t end);

template <class ret_type = uintptr_t, size_t search_size>
ret_type find_signature(const Signature<search_size>& sig, uintptr_t start, uintptr_t end) {
    auto result = find_signature(sig.pattern().data(), sig.mask().data(), search_size, start, end);

    if (result) {
        // Potential under/overflow here
        return (ret_type)(result + sig.offset());
    }

    return 0;
}

template <class ret_type = uintptr_t, size_t search_size>
ret_type find_signature(const Signature<search_size>& sig, std::pair<uintptr_t, size_t> memory_range) {
    return find_signature<ret_type>(sig, memory_range.first, memory_range.first + memory_range.second);
}

}; // namespace sigsearch
