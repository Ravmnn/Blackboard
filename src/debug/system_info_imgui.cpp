#include <blackboard/debug/system_info_imgui.hpp>

#include <format>
#include <optional>
#include <string>
#include <string_view>

#include <hwinfo/hwinfo.h>

#include <blackboard/debug/imgui_widget.hpp>




using bb::debug::SystemInfoImGui;




namespace
{


template <typename T>
void text(std::string_view label, const T& value)
{
    const std::string formatted = std::format("{}", value);
    ImGui::Text("%.*s: %s", static_cast<int>(label.size()), label.data(), formatted.c_str());
}


template <typename T>
void optional_text(std::string_view label, const std::optional<T>& value)
{
    if (value)
        text(label, *value);
}


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

    optional_text("Manufacturer", computer->vendor);
    optional_text("Product family", computer->family);
    optional_text("Model", computer->model);
    text("Chassis", hwinfo::to_string(computer->chassis));
}


void SystemInfoImGui::draw_os() noexcept
{
    ImGuiWidget::separator("Operating System");

    const auto os = hwinfo::os();
    if (report_error("Operating system", os))
        return;

    text("Name", os->name);
    text("Version", os->version);
    text("Architecture", os->architecture);
}


void SystemInfoImGui::draw_mainboard() noexcept
{
    ImGuiWidget::separator("Mainboard");

    const auto board = hwinfo::mainboard();
    if (report_error("Mainboard", board))
        return;

    optional_text("Model", board->name);
    optional_text("Manufacturer", board->vendor);
    optional_text("BIOS version", board->firmware_version);
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
        text("Model", cpu.model);
        text("Cores / threads", std::format("{} / {}", cpu.physical_cores, cpu.logical_cores));
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
        text("Model", gpu.name);
        text("Manufacturer", gpu.vendor);
        optional_text("Driver", gpu.driver_version);
        optional_text("VRAM", gpu.dedicated_memory);
        ImGui::Unindent();
    }
}


void SystemInfoImGui::draw_memory() noexcept
{
    ImGuiWidget::separator("Memory");

    const auto memory = hwinfo::memory();
    if (report_error("Memory", memory))
        return;

    text("Total", memory->total);
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
        text("Disk", disk.model.value_or(std::format("Disk {}", disk.index)));
        text("Size", disk.size);
        ImGui::Unindent();
    }
}