#ifndef ZTECH_ZP_MESSAGE_READER_HPP
#define ZTECH_ZP_MESSAGE_READER_HPP

#include "msgpack/v3/unpack_decl.hpp"
#include "ztech/zp/message.hpp"
#include "ztech/zp/message_header.hpp"

#include "msgpack/unpack.hpp"

namespace ztech::zp {
inline namespace v1 {

template <typename TErrorCode>
requires ztech::zp::detail::is_command_error_code<TErrorCode>
struct message_reader {
    explicit message_reader(ztech::zp::v1::message<TErrorCode> &response)
        : response_(response) {}

    template <typename T>
    auto operator>>(T &value) -> message_reader<TErrorCode> & {
        msgpack::unpack(response_.body, value);
        response_.header.actual_length = response_.body.tellp();

        return *this;
    }

  private:
    ztech::zp::v1::message<TErrorCode> &response_;
};

} // namespace v1
} // namespace ztech::zp
#endif
