#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <bitset>

enum class KeyState { None, Press, Hold, Release };

class Keyboard
{
  public:
    using Key = sf::Keyboard::Key;

    void update();
    void setKey(Key key);
    bool checkKey(Key key, KeyState state) const;

  private:
    std::bitset<sf::Keyboard::Key::KeyCount> currState{};
    std::bitset<sf::Keyboard::Key::KeyCount> prevState{};
};
