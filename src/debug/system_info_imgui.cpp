#include <blackboard/debug/system_info_imgui.hpp>

#include <format>
#include <string>

#include <hwinfo/hwinfo.h>

#include <blackboard/debug/imgui_widget.hpp>
#include <blackboard/rendering/frame_buffer.hpp>




using
bb::debug::SystemInfoImGui,
bb::rendering::FrameBuffer;




namespace
{


template <typename T>
bool report_error(std::string_view module, const hwinfo::result<T>& result)
{
    if (result)
        return false;

    ImGui::Text("%.*s unavailable: %s", static_cast<int>(module.size()), module.data(), result.error().message().c_str());
    return true;
}


}




void SystemInfoImGui::draw() noexcept
{
    if (!is_open)
        return;

    ImGuiWidget::begin_window("System Info", { 700, 500 }, is_open);

        draw_computer();
        ImGui::NewLine();
        ImGui::NewLine();

        draw_os();
        ImGui::NewLine();
        ImGui::NewLine();

        draw_mainboard();
        ImGui::NewLine();
        ImGui::NewLine();

        draw_cpu();
        ImGui::NewLine();
        ImGui::NewLine();

        draw_gpu();
        ImGui::NewLine();
        ImGui::NewLine();

        draw_graphics();
        ImGui::NewLine();
        ImGui::NewLine();

        draw_memory();
        ImGui::NewLine();
        ImGui::NewLine();

        draw_disks();
        ImGui::NewLine();
        ImGui::NewLine();

    ImGuiWidget::end_window();
}




void SystemInfoImGui::draw_computer() noexcept
{
    ImGuiWidget::separator("Computer");

    const auto computer = hwinfo::computer();
    if (report_error("Computer", computer))
        return;

    ImGuiWidget::optional_text_value("Manufacturer", computer->vendor);
    ImGuiWidget::optional_text_value("Product family", computer->family);
    ImGuiWidget::optional_text_value("Model", computer->model);
    ImGuiWidget::text_value("Chassis", hwinfo::to_string(computer->chassis));
}




void SystemInfoImGui::draw_os() noexcept
{
    ImGuiWidget::separator("Operating System");

    const auto os = hwinfo::os();
    if (report_error("Operating system", os))
        return;

    ImGuiWidget::text_value("Name", os->name);
    ImGuiWidget::text_value("Version", os->version);
    ImGuiWidget::text_value("Architecture", os->architecture);
}




void SystemInfoImGui::draw_mainboard() noexcept
{
    ImGuiWidget::separator("Mainboard");

    const auto board = hwinfo::mainboard();
    if (report_error("Mainboard", board))
        return;

    ImGuiWidget::optional_text_value("Model", board->name);
    ImGuiWidget::optional_text_value("Manufacturer", board->vendor);
    ImGuiWidget::optional_text_value("BIOS version", board->firmware_version);
}




void SystemInfoImGui::draw_cpu() noexcept
{
    ImGuiWidget::separator("CPU");

    const auto cpus = hwinfo::cpus();
    if (report_error("CPU", cpus))
        return;

    if (cpus->empty())
    {
        ImGui::TextUnformatted("No CPUs found");
        return;
    }

    for (const auto& cpu : *cpus)
    {
        ImGui::Text("CPU package %u", cpu.socket);
        ImGui::Indent();
        ImGuiWidget::text_value("Model", cpu.model);
        ImGuiWidget::text_value("Cores / threads", std::format("{} / {}", cpu.physical_cores, cpu.logical_cores));
        ImGui::Unindent();
    }
}




void SystemInfoImGui::draw_gpu() noexcept
{
    ImGuiWidget::separator("GPU");

    const auto gpus = hwinfo::gpus();
    if (report_error("GPU", gpus))
        return;

    if (gpus->empty())
    {
        ImGui::TextUnformatted("No GPUs found");
        return;
    }

    for (const auto& gpu : *gpus)
    {
        ImGui::Text("GPU %u", gpu.index);
        ImGui::Indent();
        ImGuiWidget::text_value("Model", gpu.name);
        ImGuiWidget::text_value("Manufacturer", gpu.vendor);
        ImGuiWidget::optional_text_value("Driver", gpu.driver_version);
        ImGuiWidget::optional_text_value("VRAM", gpu.dedicated_memory);
        ImGui::Unindent();
    }
}


void SystemInfoImGui::draw_graphics() noexcept
{
    ImGuiWidget::separator("Graphics");

    ImGui::Text("Supported Multisampling Values:");
    ImGui::Indent();
    ImGuiWidget::text_value("Color", FrameBuffer::supported_samples(GL_RGB8));
    ImGuiWidget::text_value("Depth", FrameBuffer::supported_samples(GL_DEPTH_COMPONENT24));
    ImGuiWidget::text_value("Stencil", FrameBuffer::supported_samples(GL_STENCIL_INDEX8));
    ImGuiWidget::text_value("Depth + Stencil", FrameBuffer::supported_samples(GL_DEPTH24_STENCIL8));
    ImGui::Unindent();
}




void SystemInfoImGui::draw_memory() noexcept
{
    ImGuiWidget::separator("Memory");

    const auto memory = hwinfo::memory();
    if (report_error("Memory", memory))
        return;

    ImGuiWidget::text_value("Total", memory->total);
}




void SystemInfoImGui::draw_disks() noexcept
{
    ImGuiWidget::separator("Disks");

    const auto disks = hwinfo::disks();
    if (report_error("Disks", disks))
        return;

    if (disks->empty())
    {
        ImGui::TextUnformatted("No disks found");
        return;
    }

    for (const auto& disk : *disks)
    {
        ImGui::Text("Disk %u", disk.index);
        ImGui::Indent();
        ImGuiWidget::text_value("Disk", disk.model.value_or(std::format("Disk {}", disk.index)));
        ImGuiWidget::text_value("Size", disk.size);
        ImGui::Unindent();
    }
}