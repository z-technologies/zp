#ifndef ZTECH_ZP_CRC_HPP
#define ZTECH_ZP_CRC_HPP

#include <boost/crc.hpp>

#include <cstdint>
#include <span>
#include <string>
#include <type_traits>
#include <vector>

namespace ztech::zp {

template <typename T = std::uint32_t>
requires std::is_same_v<T, std::uint16_t> || std::is_same_v<T, std::uint32_t>
class crc_calculator final {
    using crc_type =
        typename std::conditional_t<std::is_same_v<T, std::uint16_t>,
                                    boost::crc_16_type, boost::crc_32_type>;

  public:
    static constexpr std::size_t byte_count{sizeof(T)};
    static constexpr std::size_t bit_count{bit_count * 8};

    inline void process(const uint8_t* buf, std::size_t len) {
        checksum_.process_bytes(buf, len);
    }

    inline void process(std::span<std::uint8_t> buf) {
        process(buf.data(), buf.size());
    }

    inline void process(const std::vector<std::uint8_t>& buf) {
        process(buf.data(), buf.size());
    }

    inline void process(const char* buf, std::size_t len) {
        process(reinterpret_cast<const std::uint8_t*>(buf), len); // !NOLINT
    }

    inline void process(const std::string& str) {
        process(str.data(), str.size());
    }

    [[nodiscard]] inline auto value() const noexcept -> T {
        return checksum_.checksum();
    }

    inline explicit operator T() {
        return value();
    }

  private:
    crc_type checksum_{};
};

} // namespace ztech::zp

#endif
