#ifndef ZTECH_ZP_COMPRESS_ZSTD_HPP
#define ZTECH_ZP_COMPRESS_ZSTD_HPP

#include "ztech/zp/compress/compression_algorithm.hpp"

#include "zstd.h"

#include <cstdint>
#include <vector>

namespace ztech::zp::compress {

class compression_zstd final : public compression_algorithm {
  public:
    explicit compression_zstd(compression_strength strength);

    compression_zstd(compression_zstd&& rhs)      = default;
    compression_zstd(const compression_zstd& rhs) = delete;

    ~compression_zstd() override;

    auto compress(const std::vector<std::uint8_t>& buf)
        -> std::vector<std::uint8_t> override;
    auto decompress(const std::vector<std::uint8_t>& buf)
        -> std::vector<std::uint8_t> override;

    auto operator=(const compression_zstd& rhs) -> compression_zstd& = delete;
    auto operator=(compression_zstd&& rhs) -> compression_zstd& = default;

  private:
    ZSTD_CCtx* cctx_;
    ZSTD_DCtx* dctx_;
};

} // namespace ztech::zp::compress

#endif
