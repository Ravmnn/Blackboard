#include <blackboard/editor/stroke/stroke_mesh_gl.hpp>

#include <rlgl.h>

#include <blackboard/editor/stroke/stroke_mesh.hpp>




using bb::editor::StrokeMeshGL,
    bb::editor::StrokeMeshGLVertex;




void StrokeMeshGL::draw() noexcept
{
    if (!has_gl_data_)
        return;

    rlEnableVertexArray(vao_);
    rlDrawVertexArray(0, (int)vertices.size());
    rlDisableVertexArray();
}




void StrokeMeshGL::load_gl_data() noexcept
{
    vao_ = rlLoadVertexArray();
    vbo_ = rlLoadVertexBuffer(vertices.data(), (int)(vertices.size() * sizeof(StrokeMeshGLVertex)), false);

    rlEnableVertexArray(vao_);
    rlEnableVertexBuffer(vbo_);

    rlSetVertexAttribute(0, 2, RL_FLOAT, false, sizeof(StrokeMeshGLVertex), 0);
    rlSetVertexAttribute(1, 4, RL_UNSIGNED_BYTE, true, sizeof(StrokeMeshGLVertex), offsetof(StrokeMeshGLVertex, color));
    rlSetVertexAttribute(2, 1, RL_FLOAT, false, sizeof(StrokeMeshGLVertex), offsetof(StrokeMeshGLVertex, thickness));
    rlSetVertexAttribute(3, 1, RL_FLOAT, false, sizeof(StrokeMeshGLVertex), offsetof(StrokeMeshGLVertex, border_distance));

    rlEnableVertexAttribute(0);
    rlEnableVertexAttribute(1);
    rlEnableVertexAttribute(2);
    rlEnableVertexAttribute(3);

    rlDisableVertexArray();

    has_gl_data_ = true;
}


void StrokeMeshGL::unload_gl_data() noexcept
{
    if (!has_gl_data_)
        return;

    rlUnloadVertexBuffer(vbo_);
    rlUnloadVertexArray(vao_);

    vao_ = vbo_ = 0;
    has_gl_data_ = false;
}




StrokeMeshGL StrokeMeshGL::from_stroke(const StrokeMesh& mesh) noexcept
{
    StrokeMeshGL mesh_gl;
    mesh_gl.vertices.reserve(mesh.size());

    if (!mesh.size())
        return mesh_gl;

    for (size_t i = 0; i < mesh.size() - 1; i++)
        add_vertices_from_stroke_node(mesh_gl.vertices, mesh[i], mesh[i + 1]);

    return mesh_gl;
}


void StrokeMeshGL::add_vertices_from_stroke_node(std::vector<StrokeMeshGLVertex>& vertices, const StrokeMeshNode& current, const StrokeMeshNode& next)
{
    vertices.push_back({ current.position(), current.color(), current.thickness(), 1 });
    vertices.push_back({ current.edge.top, current.color(), current.thickness(), 0 });
    vertices.push_back({ next.position(), current.color(), current.thickness(), 1 });

    vertices.push_back({ next.position(), current.color(), current.thickness(), 1 });
    vertices.push_back({ next.edge.top, current.color(), current.thickness(), 0 });
    vertices.push_back({ current.edge.top, current.color(), current.thickness(), 0 });

    vertices.push_back({ current.position(), current.color(), current.thickness(), 1 });
    vertices.push_back({ current.edge.bottom, current.color(), current.thickness(), 0 });
    vertices.push_back({ next.position(), current.color(), current.thickness(), 1 });

    vertices.push_back({ next.position(), current.color(), current.thickness(), 1 });
    vertices.push_back({ current.edge.bottom, current.color(), current.thickness(), 0 });
    vertices.push_back({ next.edge.bottom, current.color(), current.thickness(), 0 });
}