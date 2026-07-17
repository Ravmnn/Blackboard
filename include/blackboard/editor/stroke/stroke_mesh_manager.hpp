#pragma once

#include <blackboard/drawable.hpp>
#include <blackboard/editor/stroke/stroke_mesh.hpp>
#include <blackboard/editor/stroke/stroke_mesh_generator.hpp>
#include <blackboard/editor/stroke/stroke_renderer_rl.hpp>
#include <blackboard/editor/stroke/stroke_renderer_gl.hpp>




namespace bb::editor
{




class StrokeMeshManager : public Drawable
{
public:
    std::vector<std::unique_ptr<StrokeMesh>> meshes;

    StrokeMeshGenerator generator;
    StrokeRenderer* renderer;


    StrokeMeshManager(StrokeRenderer& renderer) noexcept;


    void draw() noexcept override;

    void draw_stroke(const Stroke& stroke) const noexcept;
    void draw_stroke_mesh(const StrokeMesh& mesh) const noexcept;


    void add_stroke(const Stroke& stroke) noexcept;
    void remove_mesh(const StrokeMesh& mesh) noexcept;
};




}