#pragma once

enum class SceneName {
    Title = 0,
    Game,
    Test,
    None,
    Count // Must be last
};

// Constexpr function to get the name of the scene as a string
inline constexpr const char* getSceneName(SceneName name) {
    switch (name) {
        case SceneName::Title: return "Title";
        case SceneName::Game: return "Game";
        case SceneName::None: return "None";
        default: return "SceneName::Unknown";
    }
}

enum class SceneAction {
    None = 0,
    Add,
    ChangeTo,
    RemoveAll,
};

struct SceneRequest {
    SceneAction action = SceneAction::None;
    SceneName name     = SceneName::None;
};
