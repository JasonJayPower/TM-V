#include "Game/Tile.hpp"

Tile::Tile(Type type)
    : m_type{ type } {
}

Tile::Type Tile::getType() const {
    return m_type;
}
