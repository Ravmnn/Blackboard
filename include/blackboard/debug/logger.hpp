#pragma once

#include <optional>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <blackboard/stopwatch.hpp>




namespace bb::debug
{




class Logger
{
private:
    inline static std::stringstream string_stream_;

    inline static std::unique_ptr<std::ofstream> log_file_ = nullptr;
    inline static std::vector<std::ostream*> custom_streams_;

    inline static Stopwatch stopwatch_;


public:
    inline static bool log_to_stdout = false;
    inline static bool log_to_file = false;

    inline static std::optional<std::filesystem::path> log_file_directory;


    static void info(const std::string& text, const bool duration = false) { log_line("Info: " + text, duration); }
    static void warning(const std::string& text, const bool duration = false) { log_line("Warning: " + text, duration); }
    static void error(const std::string& text, const bool duration = false) { log_line("Error: " + text, duration); }

    static void reset_stopwatch() noexcept { stopwatch_.reset(); }


    static bool create_log_file() noexcept;
    static void close_log_file() noexcept;


    static void add_custom_stream(std::ostream& stream) noexcept { custom_streams_.push_back(&stream); }

    static void clear_streams() noexcept { custom_streams_.clear(); }


    static std::string get_all_logs() noexcept { return string_stream_.str(); }


private:
    static std::string get_log_file_name() noexcept;

    static void log_line(const std::string& text, bool duration) { log(text + '\n', duration); }
    static void log(const std::string& text, bool duration);

    static void write_line_to_all_streams(const std::string& text) { write_to_all_streams(text + '\n'); }
    static void write_to_all_streams(const std::string& text);
};




}