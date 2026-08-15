#pragma once




namespace bb::editor
{




class StrokeMesh;
class StrokeMeshNode;


class StrokeMeshDebugRenderer
{
public:
    static constexpr float DebugCircleRadius = 1;

    bool draw_points = false;
    bool draw_samples = false;
    bool draw_edges = false;


    void draw(const StrokeMesh& mesh) const noexcept;


    [[nodiscard]] bool any_draw_enabled() const noexcept { return draw_points || draw_samples || draw_edges; }


private:
    static void debug_draw_point(const StrokeMeshNode& node) noexcept;
    static void debug_draw_sample(const StrokeMeshNode& node) noexcept;
    static void debug_draw_edge(const StrokeMeshNode& node) noexcept;
};




}