#include "Clock.hpp"

Time Clock::elapsedTime() const noexcept {
    return Time{ (ClockType::now() - m_start).count() };
}

Time Clock::restart() noexcept {
    const TimePoint now = ClockType::now();
    Time elapsed        = Time{ (now - m_start).count() };
    m_start             = now;
    return elapsed;
}