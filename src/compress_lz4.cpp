#include "ztech/zp/compress/lz4.hpp"

#include "lz4.h"

#include <array>
#include <cassert>
#include <cstdint>
#include <vector>

namespace ztech::zp::compress {

auto compression_lz4::compress(const std::vector<std::uint8_t>& buf)
    -> std::vector<std::uint8_t> {
    std::vector<std::uint8_t> compressed(
        LZ4_compressBound(static_cast<int>(buf.size())));

    const auto ret =
        LZ4_compress_default(reinterpret_cast<const char*>(buf.data()),
                             reinterpret_cast<char*>(compressed.data()),
                             static_cast<int>(buf.size()),
                             static_cast<int>(compressed.size()));
    compressed.resize(ret);

    return compressed;
}

auto compression_lz4::decompress(const std::vector<std::uint8_t>& buf)
    -> std::vector<std::uint8_t> {
    std::vector<std::uint8_t> decompressed(buf.size());

    const auto ret =
        LZ4_decompress_safe(reinterpret_cast<const char*>(buf.data()),
                            reinterpret_cast<char*>(decompressed.data()),
                            static_cast<int>(buf.size()),
                            static_cast<int>(decompressed.size()));
    decompressed.resize(ret);

    return decompressed;
}

} // namespace ztech::zp::compress
