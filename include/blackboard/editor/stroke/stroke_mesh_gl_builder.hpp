#pragma once

#include <blackboard/editor/stroke/stroke_mesh_gl.hpp>




namespace bb::editor
{




class StrokeMeshGLBuilder
{
public:
    float cap_curvature = 0.2;


    StrokeMeshGL build(const StrokeMesh& mesh) noexcept;


private:
    void add_vertices_from_stroke(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMesh& mesh) const noexcept;
    void add_cap_vertices_from_stroke(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMesh& mesh) const noexcept;

    static void add_vertices_from_stroke_node(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMeshNode& current, const StrokeMeshNode& next) noexcept;
    static void add_cap_vertices_from_stroke_node(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMeshNode& node) noexcept;
};




}