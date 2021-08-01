#ifndef ZTECH_ZP_UTIL_SERIALIZATION_HPP
#define ZTECH_ZP_UTIL_SERIALIZATION_HPP

#include <span>
#include <type_traits>

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

    inline void write(std::span<T> data) {
        wrapped_.insert(std::end(wrapped_), std::cbegin(data), std::cend(data));
    }

    inline void write(const char* data, std::size_t len) {
        write(std::span<T>{data, len});
    }

  private:
    Container<T>& wrapped_;
};

template <detail::writable_buffer Buffer, typename T>
void serialize(Buffer& buf, const T& value) {
    msgpack::pack(buf, value);
}

template <typename Buffer, typename T>
void deserialize(const Buffer& buf, T& out) {
    auto handle = msgpack::unpack(buf.data(), buf.size());

    auto obj = handle.get();
    obj.template convert<T>(out);
}

} // namespace ztech::zp::util

#endif
