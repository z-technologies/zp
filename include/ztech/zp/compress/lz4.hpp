#ifndef ZTECH_ZP_COMPRESS_LZ4_HPP
#define ZTECH_ZP_COMPRESS_LZ4_HPP

#include "ztech/zp/compress/compression_algorithm.hpp"

#include "lz4.h"

#include <cstdint>
#include <vector>

namespace ztech::zp::compress {

class compression_lz4 final : public compression_algorithm {
  public:
    using compression_algorithm::compression_algorithm;

    compression_lz4(compression_lz4&& rhs)      = default;
    compression_lz4(const compression_lz4& rhs) = delete;

    ~compression_lz4() override = default;

    auto compress(const std::vector<std::uint8_t>& buf)
        -> std::vector<std::uint8_t> override;
    auto decompress(const std::vector<std::uint8_t>& buf)
        -> std::vector<std::uint8_t> override;

    auto operator=(const compression_lz4& rhs) -> compression_lz4& = delete;
    auto operator=(compression_lz4&& rhs) -> compression_lz4& = default;
};

} // namespace ztech::zp::compress

#endif
