#include <blackboard/editor/stroke/stroke_mesh_gl_builder.hpp>

#include <blackboard/draw.hpp>
#include <blackboard/editor/stroke/stroke_mesh.hpp>




using bb::editor::StrokeMeshGLBuilder,
    bb::editor::StrokeMeshGL;




StrokeMeshGL StrokeMeshGLBuilder::build(const StrokeMesh& mesh) noexcept
{
    StrokeMeshGL mesh_gl;
    mesh_gl.vertices.reserve(mesh.size());

    if (!mesh.size())
        return mesh_gl;

    add_cap_vertices_from_stroke(mesh_gl.vertices, mesh);
    add_vertices_from_stroke(mesh_gl.vertices, mesh);

    return mesh_gl;
}


void StrokeMeshGLBuilder::add_vertices_from_stroke(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMesh& mesh) const noexcept
{
    for (size_t i = 0; i < mesh.size() - 1; i++)
        add_vertices_from_stroke_node(vertices, mesh[i], mesh[i + 1]);
}


void StrokeMeshGLBuilder::add_cap_vertices_from_stroke(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMesh& mesh) const noexcept
{
    for (const auto& current : mesh)
         if (current.is_extremity() || current.curvature() >= cap_curvature)
            add_cap_vertices_from_stroke_node(vertices, current);
}


void StrokeMeshGLBuilder::add_vertices_from_stroke_node(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMeshNode& current, const StrokeMeshNode& next) noexcept
{
    vertices.emplace_back(current, current.position(), 1);
    vertices.emplace_back(current, current.edge.top, 0);
    vertices.emplace_back(current, next.position(), 1);

    vertices.emplace_back(current, next.position(), 1);
    vertices.emplace_back(current, next.edge.top, 0);
    vertices.emplace_back(current, current.edge.top, 0);

    vertices.emplace_back(current, current.position(), 1);
    vertices.emplace_back(current, current.edge.bottom, 0);
    vertices.emplace_back(current, next.position(), 1);

    vertices.emplace_back(current, next.position(), 1);
    vertices.emplace_back(current, current.edge.bottom, 0);
    vertices.emplace_back(current, next.edge.bottom, 0);
}


void StrokeMeshGLBuilder::add_cap_vertices_from_stroke_node(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMeshNode& node) noexcept
{
    const Vector2 direction = node.is_begin() ? node.backward_direction() : node.forward_direction();
    const std::vector<SectionTriangle> triangles = Draw::calculate_semi_circle_section_triangles(node.position(), direction, node.half_thickness(), 50);

    for (const auto& triangle : triangles)
    {
        vertices.emplace_back(node, triangle.center, 1);
        vertices.emplace_back(node, triangle.current, 0);
        vertices.emplace_back(node, triangle.next, 0);
    }
}