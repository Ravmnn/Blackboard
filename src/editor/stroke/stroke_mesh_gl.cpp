#include <blackboard/editor/stroke/stroke_mesh_gl.hpp>

#include <rlgl.h>
#include <glad.h>

#include <blackboard/editor/stroke/stroke_mesh.hpp>




using bb::editor::StrokeMeshGL,
    bb::editor::StrokeMeshGLVertex;




StrokeMeshGLVertex::StrokeMeshGLVertex(const StrokeMeshNode& node, const Vector2& position, const float border_distance) noexcept
    : position(position), color(node.color()), thickness(node.thickness()), border_distance(border_distance)
{}




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

    rlSetVertexAttribute(0, 2, GL_FLOAT, false, sizeof(StrokeMeshGLVertex), offsetof(StrokeMeshGLVertex, position));
    rlSetVertexAttribute(1, 4, GL_UNSIGNED_BYTE, true, sizeof(StrokeMeshGLVertex), offsetof(StrokeMeshGLVertex, color));
    rlSetVertexAttribute(2, 1, GL_FLOAT, false, sizeof(StrokeMeshGLVertex), offsetof(StrokeMeshGLVertex, thickness));
    rlSetVertexAttribute(3, 1, GL_FLOAT, false, sizeof(StrokeMeshGLVertex), offsetof(StrokeMeshGLVertex, border_distance));

    rlEnableVertexAttribute(0);
    rlEnableVertexAttribute(1);
    rlEnableVertexAttribute(2);
    rlEnableVertexAttribute(3);
    rlEnableVertexAttribute(4);

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