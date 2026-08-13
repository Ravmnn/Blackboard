#include <blackboard/editor/stroke/stroke_mesh_gl_builder.hpp>

#include <blackboard/editor/stroke/stroke_mesh.hpp>




using
bb::editor::StrokeMeshGL,
bb::editor::StrokeMeshGLBuilder;




StrokeMeshGL StrokeMeshGLBuilder::build(const StrokeMesh& mesh) noexcept
{
    StrokeMeshGL mesh_gl;
    mesh_gl.vertices.reserve(mesh.size() * 12);

    if (!mesh.size())
        return mesh_gl;

    add_cap_vertices_from_stroke(mesh_gl.vertices, mesh);
    add_vertices_from_stroke(mesh_gl.vertices, mesh);

    return mesh_gl;
}


void StrokeMeshGLBuilder::add_vertices_from_stroke(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMesh& mesh) noexcept
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
    // current top triangle
    vertices.emplace_back(current, current.position(), 1);
    vertices.emplace_back(current, current.edge.top, 0);
    vertices.emplace_back(current, next.position(), 1);

    // next top triangle
    vertices.emplace_back(current, next.position(), 1);
    vertices.emplace_back(current, next.edge.top, 0);
    vertices.emplace_back(current, current.edge.top, 0);

    // current bottom triangle
    vertices.emplace_back(current, current.position(), 1);
    vertices.emplace_back(current, current.edge.bottom, 0);
    vertices.emplace_back(current, next.position(), 1);

    // next bottom triangle
    vertices.emplace_back(current, next.position(), 1);
    vertices.emplace_back(current, current.edge.bottom, 0);
    vertices.emplace_back(current, next.edge.bottom, 0);
}


void StrokeMeshGLBuilder::add_cap_vertices_from_stroke_node(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMeshNode& node) noexcept
{
    const std::vector<SectionTriangle> triangles = get_cap_triangles(node);

    for (size_t i = 0; i < triangles.size(); i++)
    {
        SectionTriangle triangle = triangles[i];

        if (i == 0)
            triangle.current = (node.is_begin() ? node.edge.top : node.edge.bottom);

        if (i + 1 >= triangles.size())
            triangle.next = (node.is_begin() ? node.edge.bottom : node.edge.top);

        add_triangle_vertices(vertices, node, triangle);
    }
}


void StrokeMeshGLBuilder::add_triangle_vertices(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMeshNode& node, const SectionTriangle& triangle) noexcept
{
    vertices.emplace_back(node, triangle.center, 1);
    vertices.emplace_back(node, triangle.current, 0);
    vertices.emplace_back(node, triangle.next, 0);
}


std::vector<bb::SectionTriangle> StrokeMeshGLBuilder::get_cap_triangles(const StrokeMeshNode& node) noexcept
{
    const Vector2 direction = node.is_begin() ? node.backward_direction() : node.forward_direction();
    const std::vector<SectionTriangle> triangles = Draw::calculate_semi_circle_section_triangles(node.position(), direction, node.half_thickness(), 50);

    return triangles;
}