#include "Game/Level.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

Level::Level(const sf::Texture& texture)
    : m_sprite{ texture }
{
}

//Tile Level::getTile(u64 row, u64 col) const {
//    return m_tiles[row][col];
//}

bool Level::handleLevelCollision(sf::FloatRect& pBounds, AABB::Axis axis) {
    auto tBounds = sf::FloatRect{ 0.f, 0.f, Tile::Size, Tile::Size };

    const auto leftTile   = static_cast<int>((pBounds.left / Tile::Size));
    const auto rightTile  = static_cast<int>((pBounds.left + pBounds.width) / Tile::Size);
    const auto topTile    = static_cast<int>((pBounds.top / Tile::Size));
    const auto bottomTile = static_cast<int>((pBounds.top + pBounds.height) / Tile::Size);

    for (auto row = topTile; row <= bottomTile; row++) {
        for (auto col = leftTile; col <= rightTile; col++) {
            if (m_tiles[row][col] == Tile::Block) {
                tBounds.left = static_cast<float>(col * Tile::Size);
                tBounds.top  = static_cast<float>(row * Tile::Size);
                if (pBounds.intersects(tBounds)) {
                    if (axis == AABB::Axis::Hori) {
                        pBounds.left = AABB::resolveHorizontal(pBounds, tBounds);
                    } else {
                        pBounds.top = AABB::resolveVertical(pBounds, tBounds);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

void Level::draw(sf::RenderWindow& window)
{
    // This should be done once and cached.
    for (auto row = 0; row < m_tiles.size(); ++row) {
        float rowOffset = static_cast<float>(row * Tile::Size);
        for (auto col = 0; col < m_tiles[row].size(); ++col) {
            const auto tile = m_tiles[row][col];
            if (tile > 0) {
                switch (tile) {
                    case Tile::Block: {
                        m_sprite.setTextureRect({ 0, 0, 16, 16 });
                    } break;
                    case Tile::Temp: {
                        m_sprite.setTextureRect({ 0, 0, 16, 16 });
                    } break;
                }
                m_sprite.setPosition({ static_cast<float>(col * Tile::Size), rowOffset });
                window.draw(m_sprite);
            }
        }
    }
}
