#pragma once

#if __cplusplus < 201703L
#error "For now, this library requires C++17 or higher."
#endif


#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
/**
 * @brief Enables virtual terminal processing in the console.
 * @return true if successful, false if not.
 * @details
 * This function enables virtual terminal processing in the console. This is
 * required to use ANSI escape codes on Windows. If the function fails, it
 * returns false. Otherwise, it returns true.
 * @note This function is only available on Windows.
 */
inline bool enableVirtualTerminal() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return false;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return false;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) return false;

    return true;
}
#endif


#include <iostream>
#include <string_view>
#include <fstream>
#include <mutex>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>

// A simple logging system from MayakUI.
// Made with love by Maya4ok! ❤️
// Use setAdditionalInfo() to enable/disable file and line information.
// Use MAYAK_LOG_TRACE(), MAYAK_LOG_DEBUG(), MAYAK_LOG_INFO(), etc. to log messages.
// Is thread-safe!
namespace mayak::logger {

    // Time formats
    // For getTimestamp() method
    enum class TimeFormat {
        DateOnly, // YYYY-MM-DD
        TimeOnly, // HH:MM:SS
        DateTime, // YYYY-MM-DD HH:MM:SS
        FileCompatible // YYYY-MM-DD_HH-MM-SS
    };

    // Log levels.
    // If you set the log level to INFO, only INFO and higher will be logged.
    enum class LogLevel : uint8_t {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERR,
        FATAL
    };

        /**
     * @brief Returns the current timestamp as a string.
     * @param format The format of the timestamp. Default is TimeFormat::DateTime.
     * @return The current timestamp as a string.
     * @details
     * The returned string will be in the format specified by the TimeFormat parameter.
     * The default format is YYYY-MM-DD HH:MM:SS.
     * TimeFormat::DateOnly returns YYYY-MM-DD.
     * TimeFormat::TimeOnly returns HH:MM:SS.
     * TimeFormat::FileCompatible returns YYYY-MM-DD_HH-MM-SS.
     * @note Not only internal, but also used by MAYAK_LOG_TRACE(), MAYAK_LOG_DEBUG(), etc.
     */
    inline std::string getTimestamp(TimeFormat format = TimeFormat::DateTime) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);

        std::tm now_tm{};
        #ifdef _WIN32
            localtime_s(&now_tm, &now_c);
        #else
            localtime_r(&now_c, &now_tm);
        #endif

        std::stringstream ss;
        switch (format) {
            case TimeFormat::DateOnly:
                ss << std::put_time(&now_tm, "%Y-%m-%d");
                break;
            case TimeFormat::TimeOnly:
                ss << std::put_time(&now_tm, "%H:%M:%S");
                break;
            case TimeFormat::DateTime:
                ss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
                break;
            case TimeFormat::FileCompatible:
                ss << std::put_time(&now_tm, "%Y-%m-%d_%H-%M-%S");
                break;
        }
        return ss.str();
    }

    inline bool additionalInfo = false;
    inline LogLevel logLevel = LogLevel::INFO;
    inline std::mutex logMutex;
    inline std::string logTimestamp = getTimestamp(TimeFormat::FileCompatible);
    inline std::string logFilename = "mayak_log_" + logTimestamp + ".log";
    inline bool fileLogging = true;
    inline bool consoleLogging = true;
    #ifdef _WIN32
    inline bool colorLogging = enableVirtualTerminal();
    #else
    inline bool colorLogging = true;
    #endif

    /**
     * Sets the filename of the log file.
     * The filename will be changed to <filename>_<timestamp>.<extension>.
     * @param filename The new filename.
     * @param extension The new file extension.
     */
    inline void setFilename(std::string_view filename, std::string_view extension) {
        logFilename = std::string(filename) + "_" + getTimestamp(TimeFormat::FileCompatible) + "." + std::string(extension);
    }

    /**
     * Sets the current log level.
     * Messages below the selected level will be ignored.
     * @param level The new log level.
     */
    void setLogLevel(const LogLevel& level) {
        logLevel = level;
    }

    /**
     * Sets whether the logger will output file and line information.
     * When set to false, the logger will only output the message.
     * When set to true, the logger will output the message, followed by the file and line number.
     * @param value whether to include file and line information.
     */
    void setAdditionalInfo(bool value) {
        additionalInfo = value;
    }

    /**
     * Sets whether the logger will log to a file.
     * @param value whether to log to a file.
     */
    void setFileLogging(bool value) {
        fileLogging = value;
    }

    /**
     * Sets whether the logger will log to the console.
     * @param value whether to log to the console.
     */
    void setConsoleLogging(bool value) {
        consoleLogging = value;
    }

    /**
     * Sets whether the logger will use colors.
     * @param value whether to use colors.
     */
    void setColorLogging(bool value) {
        colorLogging = value;
    }

    inline std::ofstream& getLogFile() {
        static std::ofstream logFile(logFilename, std::ios_base::app);
        if (!logFile.is_open()) {
            throw std::runtime_error("Cannot open log file for writing");
        }
        return logFile;
    }

    // RAII color guard, that resets the console color after the scope ends.
    class Color {
    public:
        Color(std::string_view colorCode) {
            std::cout << "\033[" << colorCode << "m";
        }
        ~Color() {
            std::cout << "\033[0m";
        }
    };

    /**
     * @internal
     * You can use it, but there is probably a better way to do it, read README.md
     * @param level Log level of the message.
     * @param levelStr String label of the level.
     * @param color ANSI color code.
     * @param msg The message to log.
     * @param file The file from which the log was called.
     * @param line The line from which the log was called.
     */
    inline void _log(LogLevel level, std::string_view levelStr, std::string_view color, std::string_view msg, const char* file, int line) {
        std::lock_guard<std::mutex> lock(logMutex);
        std::string timestamp = getTimestamp(TimeFormat::DateTime);
        if (colorLogging) {
            Color colorGuard(color);
            std::cout << "[" << timestamp << "] [" << levelStr << "] " << msg;
        } else {
            std::cout << "[" << timestamp << "] [" << levelStr << "] " << msg;
        }
        if (additionalInfo)
            std::cout << " at " << file << ":" << line;
        std::cout << "\n";
    }

    /**
     * @internal
     * You can use it, but there is probably a better way to do it, read README.md
     * @param level Log level of the message.
     * @param levelStr String label of the level.
     * @param msg The message to log.
     * @param file The file from which the log was called.
     * @param line The line from which the log was called.
     */
    inline void _logToFile(LogLevel level, std::string_view levelStr, std::string_view msg, const char* file, int line) {
        std::lock_guard<std::mutex> lock(logMutex);
        getLogFile() << "[" << levelStr << "] " << msg;
        if (additionalInfo)
            getLogFile() << " at " << file << ":" << line;
        getLogFile() << "\n";
    }
};

// Public macros

/**
 * @def MAYAK_LOG
 * @brief Macro for logging messages.
 * @param level The log level.
 * @param colorCode ANSI color code.
 * @param msg The message to log. Every std::string-compatible type is supported.
 * 
 * Messages logged with this macro will be printed to the console if consoleLogging is true.
 * Messages logged with this macro will be appended to the log file if fileLogging is true.
 * 
 * @see mayak::logger::setLogLevel
 * @see mayak::logger::setAdditionalInfo
 * @see mayak::logger::setFileLogging
 * @see mayak::logger::setConsoleLogging
 * @see mayak::logger::setColorLogging
 */
#define MAYAK_LOG(level, colorCode, msg) \
    do { \
        if (mayak::logger::logLevel <= level){ \
            if (mayak::logger::consoleLogging) mayak::logger::_log(level, #level, colorCode, msg, __FILE__, __LINE__); \
            if (mayak::logger::fileLogging) mayak::logger::_logToFile(level, #level, msg, __FILE__, __LINE__); \
        } \
    } while (0)

/**
 * @def MAYAK_LOG_TRACE
 * @brief Macro for logging trace messages.
 * @param msg The message to log. Every std::string-compatible type is supported.
 * 
 * Messages logged with this macro will be printed to the console if consoleLogging is true.
 * Messages logged with this macro will be appended to the log file if fileLogging is true.
 * 
 * @see mayak::logger::setLogLevel
 * @see mayak::logger::setAdditionalInfo
 * @see mayak::logger::setFileLogging
 * @see mayak::logger::setConsoleLogging
 * @see mayak::logger::setColorLogging
 */
#define MAYAK_LOG_TRACE(msg) MAYAK_LOG(mayak::logger::LogLevel::TRACE, "34", msg)

/**
 * @def MAYAK_LOG_DEBUG
 * @brief Macro for logging debug messages.
 * @param msg The message to log. Every std::string-compatible type is supported.
 * 
 * Messages logged with this macro will be printed to the console if consoleLogging is true.
 * Messages logged with this macro will be appended to the log file if fileLogging is true.
 * 
 * @see mayak::logger::setLogLevel
 * @see mayak::logger::setAdditionalInfo
 * @see mayak::logger::setFileLogging
 * @see mayak::logger::setConsoleLogging
 * @see mayak::logger::setColorLogging
 */
#define MAYAK_LOG_DEBUG(msg) MAYAK_LOG(mayak::logger::LogLevel::DEBUG, "36", msg)

/**
 * @def MAYAK_LOG_INFO
 * @brief Macro for logging info messages.
 * @param msg The message to log. Every std::string-compatible type is supported.
 * 
 * Messages logged with this macro will be printed to the console if consoleLogging is true.
 * Messages logged with this macro will be appended to the log file if fileLogging is true.
 * 
 * @see mayak::logger::setLogLevel
 * @see mayak::logger::setAdditionalInfo
 * @see mayak::logger::setFileLogging
 * @see mayak::logger::setConsoleLogging
 * @see mayak::logger::setColorLogging
 */
#define MAYAK_LOG_INFO(msg) MAYAK_LOG(mayak::logger::LogLevel::INFO, "37", msg)

/**
 * @def MAYAK_LOG_WARN
 * @brief Macro for logging warning messages.
 * @param msg The message to log. Every std::string-compatible type is supported.
 * 
 * Messages logged with this macro will be printed to the console if consoleLogging is true.
 * Messages logged with this macro will be appended to the log file if fileLogging is true.
 * 
 * @see mayak::logger::setLogLevel
 * @see mayak::logger::setAdditionalInfo
 * @see mayak::logger::setFileLogging
 * @see mayak::logger::setConsoleLogging
 * @see mayak::logger::setColorLogging
 */
    #define MAYAK_LOG_WARN(msg) MAYAK_LOG(mayak::logger::LogLevel::WARN, "33", msg)

/**
 * @def MAYAK_LOG_ERROR
 * @brief Macro for logging error messages.
 * @param msg The message to log. Every std::string-compatible type is supported.
 * 
 * Messages logged with this macro will be printed to the console if consoleLogging is true.
 * Messages logged with this macro will be appended to the log file if fileLogging is true.
 * 
 * @see mayak::logger::setLogLevel
 * @see mayak::logger::setAdditionalInfo
 * @see mayak::logger::setFileLogging
 * @see mayak::logger::setConsoleLogging
 * @see mayak::logger::setColorLogging
 */
    #define MAYAK_LOG_ERROR(msg) MAYAK_LOG(mayak::logger::LogLevel::ERR, "31", msg)

/**
 * @def MAYAK_LOG_FATAL
 * @brief Macro for logging fatal messages.
 * @param msg The message to log. Every std::string-compatible type is supported.
 * 
 * Messages logged with this macro will be printed to the console if consoleLogging is true.
 * Messages logged with this macro will be appended to the log file if fileLogging is true.
 * 
 * @see mayak::logger::setLogLevel
 * @see mayak::logger::setAdditionalInfo
 * @see mayak::logger::setFileLogging
 * @see mayak::logger::setConsoleLogging
 * @see mayak::logger::setColorLogging
 */
#define MAYAK_LOG_FATAL(msg) MAYAK_LOG(mayak::logger::LogLevel::FATAL, "41;97", msg)

// TODO: Add operator <<
// TODO: Add better formatting
// TODO: Use std::clog / std::cerr instead of std::cout
// TODO: Add custom exceptions