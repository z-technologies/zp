#include "ztech/zp/message.hpp"
#include "ztech/zp/crc.hpp"
#include "ztech/zp/detail/encoding.hpp"
#include "ztech/zp/flags.hpp"

#include <cassert>
#include <cstdint>
#include <cstring>
#include <vector>

namespace ztech::zp {

auto message::flatten() const noexcept -> std::vector<std::uint8_t> {
    assert(header_.body_length == body_.size());

    std::vector<std::uint8_t> retbuf{};

    header_.encode(retbuf);
    std::copy(std::cbegin(body_), std::cend(body_),
              std::back_inserter<>(retbuf));

    return retbuf;
}

} // namespace ztech::zp
