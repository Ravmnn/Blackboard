#pragma once

#include <blackboard/drawable.hpp>
#include <blackboard/editor/stroke/stroke_mesh.hpp>
#include <blackboard/editor/stroke/stroke_mesh_generator.hpp>
#include <blackboard/editor/stroke/stroke_mesh_renderer.hpp>
#include <blackboard/editor/stroke/stroke_renderer.hpp>




namespace bb::editor
{




class StrokeMeshManager : public Drawable
{
public:
    std::vector<std::unique_ptr<StrokeMesh>> meshes;

    StrokeMeshGenerator generator;
    StrokeMeshRenderer default_mesh_renderer;
    StrokeRenderer renderer;


    StrokeMeshManager() noexcept;


    void draw() noexcept override;

    void draw_stroke(const Stroke& stroke) noexcept;


    void add_stroke(const Stroke& stroke) noexcept;
    void remove_mesh(const StrokeMesh& mesh) noexcept;
};




}