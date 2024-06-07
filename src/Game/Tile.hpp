#pragma once

#include "System/Types.hpp"

class Tile {
  public:
    using Type = s32;

    static constexpr s32 Size = 16;

    static constexpr Type None  = 0;
    static constexpr Type Block = 1;
    static constexpr Type Temp  = 2;
    // TODO - Add more tiles types if needed.




    // Constructors
    Tile() = default;
    Tile(Type type);

    Type getType() const;

  private:
    Type m_type = None;
};
