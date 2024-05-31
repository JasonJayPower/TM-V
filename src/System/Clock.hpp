#pragma once

#include <chrono>

#include "System/Time.hpp"

class Clock
{
    using ClockType = std::chrono::steady_clock;
    using TimePoint = std::chrono::time_point<ClockType>;

  public:
    Time elapsedTime() const noexcept;
    Time restart() noexcept;

  private:
    TimePoint m_start = ClockType::now();
};
