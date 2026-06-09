#pragma once

#include <raymath.h>






namespace bb
{




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




// inline Vector2 max(const Vector2& a, const Vector2& b) noexcept {
//     return Vector2M
// }




}