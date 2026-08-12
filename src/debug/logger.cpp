#include <blackboard/debug/logger.hpp>

#include <format>
#include <filesystem>

#include <blackboard/current_time.hpp>




using bb::debug::Logger;

using namespace std::chrono;

namespace fs = std::filesystem;




bool Logger::create_log_file() noexcept
{
    if (!log_file_directory)
        return false;

    try
    {
        fs::create_directories(*log_file_directory);
        log_file_ = std::make_unique<std::ofstream>(get_log_file_name());
    }
    catch (...)
    {
        return false;
    }

    return true;
}


std::string Logger::get_log_file_name() noexcept
{
    const auto ymd = CurrentTime::year_month_day();
    const auto hms = CurrentTime::hour_minute_second();
    const std::string file_name = *log_file_directory / std::format("log.{:%F}.{:%H}h{:%M}m{:%S}s.txt", ymd, hms.hours(), hms.minutes(), hms.seconds());

    return file_name;
}


void Logger::close_log_file() noexcept
{
    if (!log_file_)
        return;

    log_file_->close();
    log_file_ = nullptr;
}




void Logger::log(const std::string& text, const bool duration)
{
    std::stringstream stream;
    std::stringstream aux;

    stream << '[' << CurrentTime::hour_minute_second_with_ms() << ']';

    if (duration)
        aux << std::fixed << std::setprecision(3) << '(' << std::setw(7) << std::setfill('0') << stopwatch_.elapsed_ms_double().count() << "ms" << ')';

    stream << ' ' << std::left << std::setw(16) << aux.str();
    stream << " " << text;

    stopwatch_.reset();

    write_to_all_streams(stream.str());
}




void Logger::write_to_all_streams(const std::string& text)
{
    string_stream_ << text;

    if (log_to_stdout)
        std::cout << text << std::flush;

    if (log_file_)
        *log_file_ << text << std::flush;

    for (auto& stream : custom_streams_)
        *stream << text << std::flush;
}