#pragma once

#include "blackboard/draw.hpp"
#include <blackboard/editor/stroke/stroke_mesh_gl.hpp>
#include <vector>




namespace bb::editor
{




class StrokeMeshGLBuilder
{
public:
    float cap_curvature = 0.2;


    StrokeMeshGL build(const StrokeMesh& mesh) noexcept;


private:
    static void add_vertices_from_stroke(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMesh& mesh) noexcept;
    void add_cap_vertices_from_stroke(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMesh& mesh) const noexcept;

    static void add_vertices_from_stroke_node(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMeshNode& current, const StrokeMeshNode& next) noexcept;
    static void add_cap_vertices_from_stroke_node(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMeshNode& node) noexcept;

    static void add_triangle_vertices(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMeshNode& node, const SectionTriangle& triangle) noexcept;

    static std::vector<SectionTriangle> get_cap_triangles(const StrokeMeshNode& node) noexcept;
};




}