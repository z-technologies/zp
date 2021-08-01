#ifndef ZTECH_ZP_UTIL_SERIALIZATION_HPP
#define ZTECH_ZP_UTIL_SERIALIZATION_HPP

#include <span>
#include <type_traits>

#include "msgpack/adaptor/raw.hpp"
#include "msgpack/pack.hpp"
#include "msgpack/unpack.hpp"

namespace ztech::zp::util {

namespace detail {

template <template <typename...> typename Container, typename T>
concept compatible_stl_container = requires(Container<T> c) {
    requires std::is_integral_v<T> && sizeof(T) == 1;
    {c.insert(c.begin(), std::declval<typename Container<T>::iterator>(),
              std::declval<typename Container<T>::iterator>())};
};

template <typename Buffer>
concept writable_buffer = requires(Buffer b) {
    {b.write(std::declval<const char*>(), std::declval<std::size_t>())};
};

} // namespace detail

template <template <typename...> typename Container, typename T>
requires detail::compatible_stl_container<Container, T>
class stl_container_wrapper {
  public:
    explicit stl_container_wrapper(Container<T>& wrapped) : wrapped_{wrapped} {
    }

    inline void write(const char* data, std::size_t len) {
        wrapped_.insert(std::end(wrapped_), &data[0], &data[len]); // NOLINT
    }

    inline auto data() const noexcept -> const T* {
        return wrapped_.data();
    }

    [[nodiscard]] inline auto size() const noexcept -> std::size_t {
        return wrapped_.size();
    }

    inline void clear() {
        wrapped_.clear();
    }

  private:
    Container<T>& wrapped_;
};

template <detail::writable_buffer Buffer, typename T>
void serialize(Buffer& buf, const T& value) {
    msgpack::pack(buf, value);
}

template <typename Buffer, typename T>
[[nodiscard]] auto deserialize(const Buffer& buf, T& out) -> bool {
    auto handle = msgpack::unpack(reinterpret_cast<const char*>(buf.data()),
                                  buf.size()); // NOLINT

    if (handle->is_nil()) {
        return false;
    }

    auto obj = handle.get();
    return obj.template convert_if_not_nil<T>(out);
}

} // namespace ztech::zp::util

#endif
