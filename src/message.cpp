#include "ztech/zp/message.hpp"
#include "ztech/zp/crc.hpp"
#include "ztech/zp/detail/encoding.hpp"
#include "ztech/zp/flags.hpp"

#include <boost/endian.hpp>

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

    if ((header_.flags & ztech::zp::flags::has_body_checksum) ==
        ztech::zp::flags::has_body_checksum) {
        ztech::zp::crc_calculator<body_crc_type> crc_calc{};
        crc_calc.process(body_);

        const auto be_crc = boost::endian::native_to_big(crc_calc.value());
        ztech::zp::detail::append_uint(be_crc, retbuf);
    }

    return retbuf;
}

} // namespace ztech::zp
