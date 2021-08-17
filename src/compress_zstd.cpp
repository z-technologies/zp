#include "ztech/zp/compress/zstd.hpp"

#include "zstd.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <vector>

namespace ztech::zp::compress {

compression_zstd::compression_zstd(compression_strength strength)
    : compression_algorithm{strength},
      cctx_(ZSTD_createCCtx()), dctx_{ZSTD_createDCtx()} {
    assert(cctx_ != NULL); // !NOLINT
    assert(dctx_ != NULL); // !NOLINT
}

compression_zstd::~compression_zstd() {
    ZSTD_freeCCtx(cctx_);
    ZSTD_freeDCtx(dctx_);
}

auto compression_zstd::compress(const std::vector<std::uint8_t>& buf)
    -> std::vector<std::uint8_t> {
    constexpr std::array<int, 5> compression_levels{1, 3, 7, 8, 12};

    std::vector<std::uint8_t> compressed(ZSTD_compressBound(buf.size()));

    const auto ret = ZSTD_compressCCtx(
        cctx_,
        compressed.data(),
        compressed.size(),
        buf.data(),
        buf.size(),
        compression_levels[static_cast<int>(strength())]); // !NOLINT
    compressed.resize(ret);

    return compressed;
}

auto compression_zstd::decompress(const std::vector<std::uint8_t>& buf)
    -> std::vector<std::uint8_t> {
    const std::size_t decompressed_size{
        ZSTD_getFrameContentSize(buf.data(), buf.size())};

    assert(decompressed_size != ZSTD_CONTENTSIZE_ERROR);   // !NOLINT
    assert(decompressed_size != ZSTD_CONTENTSIZE_UNKNOWN); // !NOLINT

    std::vector<std::uint8_t> decompressed(decompressed_size);

    auto ret = ZSTD_decompressDCtx(dctx_,
                                   decompressed.data(),
                                   decompressed.size(),
                                   buf.data(),
                                   buf.size());
    decompressed.resize(ret);

    return decompressed;
}

} // namespace ztech::zp::compress
