#ifndef ZTECH_ZP_MESSAGE_HPP
#define ZTECH_ZP_MESSAGE_HPP

#include "ztech/zp/message_header.hpp"

#include <cstdint>
#include <vector>

namespace ztech::zp {

inline namespace v1 {

template <typename TCommand>
requires ztech::zp::detail::is_command_error_code<TCommand>
struct message {
    ztech::zp::v1::message_header<TCommand> header;
    std::vector<std::uint8_t>               body;
};

} // namespace v1

} // namespace ztech::zp
#endif
