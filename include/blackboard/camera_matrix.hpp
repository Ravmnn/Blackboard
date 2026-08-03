#pragma once

#include <raylib.h>
#include <raymath.h>




namespace bb
{




class CameraMatrix
{
public:
    static Matrix get_orthographic_matrix_from_camera(const Camera2D& camera) noexcept
    {
        const Matrix view = GetCameraMatrix2D(camera);
        const Matrix ortho =  MatrixOrtho(0, GetScreenWidth(), GetScreenHeight(), 0, -1, 1);
        const Matrix mvp = MatrixMultiply(view, ortho);

        return mvp;
    }
};




}