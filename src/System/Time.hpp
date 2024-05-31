#pragma once

#include "System/Types.hpp"

struct Time {
    s64 nanoseconds{ 0 };
};

// Returns time in seconds;
inline constexpr f32 timeAsSeconds(s64 nanoseconds) {
    return static_cast<f32>(nanoseconds) * 1e-9f;
}

// Returns time in seconds, converted to times underlying type.
inline constexpr Time timeFromSeconds(f32 seconds) {
    return Time{ static_cast<s64>(seconds * 1e9) };
}

inline constexpr Time operator+(const Time& t1, const Time& t2) {
    return Time{ t1.nanoseconds + t2.nanoseconds };
}

inline constexpr Time operator-(const Time& t1, const Time& t2) {
    return Time{ t1.nanoseconds - t2.nanoseconds };
}

inline constexpr Time& operator+=(Time& t1, const Time& t2) {
    t1.nanoseconds += t2.nanoseconds;
    return t1;
}

inline constexpr Time& operator-=(Time& t1, const Time& t2) {
    t1.nanoseconds -= t2.nanoseconds;
    return t1;
}

inline constexpr bool operator<(const Time& t1, const Time& t2) {
    return t1.nanoseconds < t2.nanoseconds;
}

inline constexpr bool operator<=(const Time& t1, const Time& t2) {
    return t1.nanoseconds <= t2.nanoseconds;
}

inline constexpr bool operator>(const Time& t1, const Time& t2) {
    return t1.nanoseconds > t2.nanoseconds;
}

inline constexpr bool operator>=(const Time& t1, const Time& t2) {
    return t1.nanoseconds >= t2.nanoseconds;
}
