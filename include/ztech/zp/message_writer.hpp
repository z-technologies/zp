#ifndef ZTECH_ZP_MESSAGE_WRITER_HPP
#define ZTECH_ZP_MESSAGE_WRITER_HPP

#include "ztech/zp/message.hpp"
#include "ztech/zp/message_header.hpp"

#include "msgpack/pack.hpp"


namespace ztech::zp {
inline namespace v1 {

template <typename TCommand>
requires ztech::zp::detail::is_command_error_code<TCommand>
struct message_writer {
    explicit message_writer(ztech::zp::v1::message<TCommand> &request)
        : request_{request} {}

    template <typename T>
    auto operator<<(const T &value) -> message_writer<TCommand> & {
        msgpack::pack(request_.body, value);
        request_.header.actual_length = request_.body.tellp();

        return *this;
    }

  private:
    ztech::zp::v1::message<TCommand> &request_;
};

} // namespace v1
} // namespace ztech::zp

#endif
