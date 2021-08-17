#ifndef ZTECH_ZP_COMPRESS_COMPRESSOIN_ALGORITHM_HPP
#define ZTECH_ZP_COMPRESS_COMPRESSOIN_ALGORITHM_HPP

#include <cstdint>
#include <vector>

namespace ztech::zp::compress {

enum class compression_strength : std::uint32_t {
    lowest,
    low,
    medium,
    high,
    highest
};

class compression_algorithm {
  public:
    explicit compression_algorithm(compression_strength strength)
        : strength_{strength} {
    }

    compression_algorithm(compression_algorithm&& rhs)      = default;
    compression_algorithm(const compression_algorithm& rhs) = delete;

    virtual ~compression_algorithm() = default;

    virtual auto compress(const std::vector<std::uint8_t>& buf)
        -> std::vector<std::uint8_t> = 0;
    virtual auto decompress(const std::vector<std::uint8_t>& buf)
        -> std::vector<std::uint8_t> = 0;

    [[nodiscard]] inline auto strength() const noexcept
        -> compression_strength {
        return strength_;
    }

    auto operator                 =(const compression_algorithm& rhs)
        -> compression_algorithm& = delete;
    auto operator                 =(compression_algorithm&& rhs)
        -> compression_algorithm& = default;

  private:
    compression_strength strength_;
};

} // namespace ztech::zp::compress

#endif
