#pragma once

#include <SFML/Graphics/Rect.hpp>

#include "System/Types.hpp"

namespace AABB {
    inline f32 resolveHorizontal(const sf::FloatRect& r1, const sf::FloatRect& r2) {
        return r1.left < r2.left ? (r2.left - r1.width) : (r2.left + r2.width);
    }

    inline f32 resolveVertical(const sf::FloatRect& r1, const sf::FloatRect& r2) {
        return r1.top < r2.top ? (r2.top - r1.height) : (r2.top + r2.height);
    }
}  // namespace AABB