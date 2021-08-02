#ifndef ZTECH_ZP_UTIL_MESSAGE_BUILDER_HPP
#define ZTECH_ZP_UTIL_MESSAGE_BUILDER_HPP

#include "ztech/zp/flags.hpp"
#include "ztech/zp/message_header.hpp"

#include <atomic>
#include <cstdint>
#include <limits>
#include <vector>

namespace ztech::zp {
inline namespace v1 {

class message_body_builder;

class message_builder {
  public:
    message_builder(std::uint16_t type, std::uint16_t command);

    auto with_version(std::uint8_t version) noexcept -> message_builder&;
    auto with_type(std::uint16_t type) noexcept -> message_builder&;
    auto with_command(std::uint16_t command) noexcept -> message_builder&;
    auto with_tag(std::uint16_t tag) noexcept -> message_builder&;
    auto with_flags(ztech::zp::v1::flags flags) noexcept -> message_builder&;
    auto end_of_message() noexcept -> message_builder&;
    auto end_of_stream() noexcept -> message_builder&;
    auto end_of_session() noexcept -> message_builder&;
    auto require_ack() noexcept -> message_builder&;
    auto include_checksum() noexcept -> message_builder&;

  private:
    template <
        typename T = decltype(std::declval<ztech::zp::message_header>().tag)>
    [[nodiscard]] static inline auto next_tag() noexcept -> T {
        using limits = std::numeric_limits<T>;

        static std::atomic<T> current_tag{};

        const auto ret = current_tag.load();

        if (current_tag == limits::max()) {
            current_tag = limits::min();
        } else {
            ++current_tag;
        }

        return ret;
    }

    ztech::zp::v1::message_header header_{};
};

} // namespace v1
} // namespace ztech::zp

#endif
