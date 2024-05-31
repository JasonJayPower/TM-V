#pragma once

#include <type_traits>

template <typename E>
inline constexpr auto to_underlying(E e) noexcept {
    return static_cast<std::underlying_type_t<E>>(e);
}
