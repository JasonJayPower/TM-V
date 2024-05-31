#pragma once
#include "Asset/Types.hpp"

namespace sf {
    class Font;
    class Texture;
}  // namespace sf

template <typename T, typename E>
class AssetManager;

class ContextManager
{
  public:
    AssetManager<sf::Font, FontID>* fontMgr      = nullptr;
    AssetManager<sf::Texture, TexID>* textureMgr = nullptr;
};
