#pragma once

#include <cstdint>

#include <vector>
#include <memory>

#include <raylib.h>

#include <blackboard/drawable.hpp>
#include <blackboard/editor/stroke/stroke_mesh.hpp>




namespace bb::editor
{




class StrokeMesh;
class StrokeMeshNode;


struct StrokeMeshGLVertex
{
    Vector2 position;
    Color color;
    float thickness;

    float border_distance;


    StrokeMeshGLVertex(const StrokeMeshNode& node, const Vector2& position, float border_distance) noexcept;
};


class StrokeMeshGL : public Drawable
{
private:
    uint32_t vbo_ = 0;
    uint32_t vao_ = 0;
    bool has_gl_data_ = false;


public:
    std::unique_ptr<StrokeMesh> source;
    std::vector<StrokeMeshGLVertex> vertices;


    ~StrokeMeshGL() noexcept override { unload_gl_data(); }


    void draw() noexcept override;


    void load_gl_data() noexcept;
    void unload_gl_data() noexcept;


    [[nodiscard]] uint32_t vbo() const noexcept { return vbo_; }
    [[nodiscard]] uint32_t vao() const noexcept { return vao_; }
};




}