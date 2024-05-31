#pragma once

#include <memory>


template <typename T, typename E>
class AssetManager
{
    using Assets = std::unique_ptr<T[]>;

  public:
    const T& get(const E idx) const noexcept {
        return m_assets[std::underlying_type_t<E>(idx)];
    }

    template <typename... Args>
    bool load(const E idx, Args&&... args) {
        return m_assets[std::underlying_type_t<E>(idx)].loadFromFile(std::forward<Args>(args)...);
    }

  private:
    Assets m_assets = std::make_unique<T[]>(std::underlying_type_t<E>(E::Count));
};
