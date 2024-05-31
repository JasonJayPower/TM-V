#include "Keyboard.hpp"

void Keyboard::update() {
    prevState = currState;
}

void Keyboard::setKey(Key key) {
    if (key != Key::Unknown) {
        // Requires window.setKeyRepeatEnabled(false);
        currState.flip(key);
    }
}

bool Keyboard::checkKey(Key key, KeyState state) const {
    if (prevState[key]) {
        return !currState[key] ? KeyState::Release == state : KeyState::Hold == state;
    }
    return (currState[key] && (KeyState::Press == state || KeyState::Hold == state));
}
