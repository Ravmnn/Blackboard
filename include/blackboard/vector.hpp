#pragma once

#include <raymath.h>




inline bool operator >(const Vector2& left, const Vector2& right) {
    return left.x > right.x && left.y > right.y;
}


inline bool operator <(const Vector2& left, const Vector2& right) {
    return left.x < right.x && left.y < right.y;
}


inline bool operator >=(const Vector2& left, const Vector2& right) {
    return left.x >= right.x && left.y >= right.y;
}


inline bool operator <=(const Vector2& left, const Vector2& right) {
    return left.x <= right.x && left.y <= right.y;
}