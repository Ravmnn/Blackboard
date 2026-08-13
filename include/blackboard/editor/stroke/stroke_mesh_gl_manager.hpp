#pragma once

#include <blackboard/editor/stroke/stroke_renderer_gl.hpp>
#include <blackboard/editor/stroke/stroke_mesh_manager.hpp>




namespace bb::editor
{




class StrokeMeshGLManager : public editor::StrokeMeshManager
{
public:
    explicit StrokeMeshGLManager(editor::StrokeRendererGL& renderer) noexcept;


    void draw() noexcept override { draw_composition(); }

    void draw_composition() const noexcept;
    void clear_composition() const noexcept;


    void draw_stored_meshes_to_composition() const noexcept { draw_stored_meshes(); }
    void draw_stroke_to_composition(const Stroke& stroke) noexcept { draw_stroke(stroke); }


    [[nodiscard]] editor::StrokeRendererGL* renderer_as_gl() const noexcept {
        return dynamic_cast<editor::StrokeRendererGL*>(renderer);
    }
};




}