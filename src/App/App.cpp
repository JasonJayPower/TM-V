#include "App/App.hpp"

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Window.hpp>

#include "Manager/ContextManager.hpp"
#include "Manager/SceneManager.hpp"
#include "Scene/Types.hpp"
#include "System/Clock.hpp"
#include "System/Time.hpp"

// Allows forward Declare with unique_ptr
App::App()
    : m_window    { sf::RenderWindow(sf::VideoMode(400, 224), "") }
    , m_keyboard  {}
    , m_fontMgr   {}
    , m_textureMgr{}
    , m_sceneMgr  { nullptr } {
}

App::~App() = default;

void App::setup() {
    m_window.setKeyRepeatEnabled(false);
    m_window.setView(sf::View({ 32.f, 0.f, 400.f, 224.f }));

    // Create / load all assets
    m_textureMgr.load(TexID::TextureA, "assets/texture/a.png");
    m_textureMgr.load(TexID::TextureB, "assets/texture/b.png");


    // Create the SceneManager with ContextManager
    std::unique_ptr<ContextManager> contextMgr = std::make_unique<ContextManager>();

    contextMgr->fontMgr    = &m_fontMgr;
    contextMgr->textureMgr = &m_textureMgr;

    m_sceneMgr = std::make_unique<SceneManager>(std::move(contextMgr));

    // Add Scenes
    m_sceneMgr->addScene(SceneName::Title);
    m_sceneMgr->addScene(SceneName::Game);
    m_sceneMgr->addScene(SceneName::Test);
    if (m_sceneMgr->isSceneStackEmpty()) {
        m_window.close();
    }
}

void App::run() {
    constexpr Time TimePerFrame = timeFromSeconds(1.f / 60.f);

    sf::Event e              = {};
    Clock clock              = {};
    Time timeSinceLastUpdate = {};

    while (m_window.isOpen()) {
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate >= TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents(e);
            update();
        }
        render();
        lateUpdate();
    }
}

void App::processEvents(sf::Event& e) {
    m_keyboard.update();
    while (m_window.pollEvent(e)) {
        switch (e.type) {
            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased: {
                m_keyboard.setKey(e.key.code);
            } break;
            case sf::Event::Closed: {
                m_window.close();
            } break;
        }
    }
    m_sceneMgr->input(m_keyboard);
}

void App::update() {
    m_sceneMgr->update();
}

void App::render() {
    m_window.clear(sf::Color::Green);
    m_sceneMgr->render(m_window);
    m_window.display();
}

void App::lateUpdate() {
    m_sceneMgr->processSceneRequests();
    if (m_sceneMgr->isSceneStackEmpty()) {
        m_window.close();
    }
}
