#pragma once

#include <iostream>
#include <mutex>

// A simple logging system from MayakUI.
// Made with love by Maya4ok! ❤️
// Use setAdditionalInfo() to enable/disable file and line information.
// Use MAYAK_LOG_TRACE(), MAYAK_LOG_DEBUG(), MAYAK_LOG_INFO(), etc. to log messages.
// Is thread-safe!
namespace mayak::logger {

    // Log levels.
    // If you set the log level to INFO, only INFO and higher will be logged.
    enum LogLevel {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL
    };

    inline bool additionalInfo = false;
    inline LogLevel logLevel = INFO;
    inline std::mutex logMutex;

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
    void setAdditionalInfo(const bool& value) {
        additionalInfo = value;
    }

    // RAII color guard, that resets the console color after the scope ends.
    class Color {
    public:
        Color(const char* color) { std::cout << "\033[" << color << "m"; }
        ~Color() { std::cout << "\033[0m"; }
    };

    /**
     * Internal logging function.
     * Don't use it directly. Use the macros instead.
     * @param level Log level of the message.
     * @param levelStr String label of the level.
     * @param color ANSI color code.
     * @param msg The message to log.
     * @param file The file from which the log was called.
     * @param line The line from which the log was called.
     */
    inline void _log(LogLevel level, const char* levelStr, const char* color, const std::string& msg, const char* file, int line) {
        if (level < logLevel) return;
        std::lock_guard<std::mutex> lock(logMutex);
        Color c(color);
        std::cout << "[" << levelStr << "] " << msg;
        if (additionalInfo)
            std::cout << " at " << file << ":" << line;
        std::cout << "\n";
    }

    /**
     * Logs a trace message to the console.
     * If debugging is enabled, it includes the file name and line number.
     * @warning Is internal use only. Use MAYAK_LOG_TRACE() instead.
     * 
     * @param msg Trace message to log.
     */
    inline void _trace(const std::string& msg, const char* file, int line) {
        _log(TRACE, "TRACE", "90", msg, file, line);
    }

    /**
     * Logs a debug message to the console.
     * If debugging is enabled, it includes the file name and line number.
     * @warning Is internal use only. Use MAYAK_LOG_DEBUG() instead.
     * 
     * @param msg Debug message to log.
     */
    inline void _debug(const std::string& msg, const char* file, int line) {
        _log(DEBUG, "DEBUG", "36", msg, file, line);
    }

    /**
     * Logs an information message to the console.
     * If debugging is enabled, it includes the file name and line number.
     * @warning Is internal use only. Use MAYAK_LOG_INFO() instead.
     * 
     * @param msg Information message to log.
     */
    inline void _info(const std::string& msg, const char* file, int line) {
        _log(INFO, "INFO", "37", msg, file, line);
    }

    /**
     * Logs a warning message to the console.
     * If debugging is enabled, it includes the file name and line number.
     * @warning Is internal use only. Use MAYAK_LOG_WARN() instead.
     * 
     * @param msg Fatal error message to log.
     */
    inline void _warn(const std::string& msg, const char* file, int line) {
        _log(WARN, "WARN", "33", msg, file, line);
    }

    /**
     * Logs an error message to the console.
     * If debugging is enabled, it includes the file name and line number.
     * @warning Is internal use only. Use MAYAK_LOG_ERROR() instead.
     * 
     * @param msg Error message to log.
     */
    inline void _error(const std::string& msg, const char* file, int line) {
        _log(ERROR, "ERROR", "31", msg, file, line);
    }

    /**
     * Logs a fatal error message to the console.
     * If debugging is enabled, it includes the file name and line number.
     * @attention Should be used to exit the program.
     * @warning Is internal use only. Use MAYAK_LOG_FATAL() instead.
     * 
     * @param msg Fatal error message to log.
     */
    inline void _fatal(const std::string& msg, const char* file, int line) {
        _log(FATAL, "FATAL", "41;97", msg, file, line);
    }
}

// Public macros

/**
 * @brief Logs a trace message to the console.
 * @note If debugging is enabled, it includes the file name and line number.
 * 
 * @param msg Trace message to log.
 */
#define MAYAK_LOG_TRACE(msg) mayak::logger::_trace(msg, __FILE__, __LINE__)


/**
 * @brief Logs a debug message to the console.
 * @note If debugging is enabled, it includes the file name and line number.
 * 
 * @param msg Debug message to log.
 */
#define MAYAK_LOG_DEBUG(msg) mayak::logger::_debug(msg, __FILE__, __LINE__)

/**
 * @brief Logs an information message to the console.
 * @note If debugging is enabled, it includes the file name and line number.
 * 
 * @param msg Information message to log.
 */
#define MAYAK_LOG_INFO(msg)  mayak::logger::_info(msg,  __FILE__, __LINE__)

/**
 * @brief Logs a warning message to the console.
 * @note If debugging is enabled, it includes the file name and line number.
 * 
 * @param msg Warning message to log.
 */
#define MAYAK_LOG_WARN(msg)  mayak::logger::_warn(msg,  __FILE__, __LINE__)

/**
 * @brief Logs an error message to the console.
 * @note If debugging is enabled, it includes the file name and line number.
 * 
 * @param msg Error message to log.
 */
#define MAYAK_LOG_ERROR(msg) mayak::logger::_error(msg, __FILE__, __LINE__)

/**
 * @brief Logs a fatal error message to the console.
 * @note If debugging is enabled, it includes the file name and line number.
 * @attention Should be used to exit the program.
 * 
 * @param msg Fatal error message to log.
 */
#define MAYAK_LOG_FATAL(msg) mayak::logger::_fatal(msg, __FILE__, __LINE__)
