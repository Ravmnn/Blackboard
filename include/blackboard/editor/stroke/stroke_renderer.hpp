#pragma once

#include <vector>
#include <memory>
#include <optional>

#include <raylib.h>




namespace bb::editor
{




class StrokeMesh;


class StrokeRenderer
{
public:
    std::optional<Rectangle> view_area;


    void draw_stroke_meshes(const std::vector<std::unique_ptr<StrokeMesh>>& meshes) noexcept;
    void draw_stroke_meshes(const std::vector<StrokeMesh*>& meshes) noexcept;
    void draw_stroke_meshes(const std::vector<StrokeMesh>& meshes) noexcept;

    virtual void draw_stroke_mesh(const StrokeMesh& mesh) noexcept = 0;
};




}