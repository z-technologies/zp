#ifndef ZTECH_ZP_MESSAGE_HPP
#define ZTECH_ZP_MESSAGE_HPP

#include "ztech/zp/message_header.hpp"

#include <cstdint>
#include <sstream>

namespace ztech::zp {
inline namespace v1 {

template <typename TCommandErrorCode>
requires ztech::zp::detail::is_command_error_code<TCommandErrorCode>
struct message {
    ztech::zp::v1::message_header<TCommandErrorCode> header;
    std::stringstream                                body;
};

} // namespace v1
} // namespace ztech::zp

#endif
