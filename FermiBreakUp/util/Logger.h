//
// Created by Artem Novikov on 08.01.2025.
//

#ifndef FERMIBREAKUP_UTILITIES_LOGGER_H
#define FERMIBREAKUP_UTILITIES_LOGGER_H

#include <string_view>
#include <string>
#include <iostream>
#include <memory>

namespace fermi {

  enum class LogLevel : int {
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    NONE = 5,
  };

  class ILogger {
  public:
    virtual void Log(const std::string_view fileName,
                    const int line,
                    const std::string_view funcName,
                    const LogLevel level,
                    const std::string_view msg) = 0;

    virtual ~ILogger() = default;
  };

  class StreamLogger : public ILogger {
  public:
    StreamLogger(std::ostream& stream)
      : stream_(stream)
    {
    }

    void Log(const std::string_view fileName,
            const int line,
            const std::string_view funcName,
            const LogLevel level,
            const std::string_view msg) override;

  private:
    std::ostream& stream_;
  };

  class Logger {
  public:
    Logger();

    Logger(std::shared_ptr<ILogger>&& impl, const LogLevel level = LogLevel::TRACE)
      : impl_(std::move(impl))
      , level_(level)
    {
    }

    Logger(const std::shared_ptr<ILogger>& impl, const LogLevel level = LogLevel::TRACE)
      : Logger(std::shared_ptr<ILogger>(impl), level)
    {
    }

    Logger(const Logger& other) = default;

    Logger& operator=(const Logger& other) = default;

    bool ShouldLog(const LogLevel level) const {
      return static_cast<int>(level) >= static_cast<int>(level_);
    }

    void Log(const std::string_view fileName,
            const int line,
            const std::string_view funcName,
            const LogLevel level,
            const std::string_view msg) {
      impl_->Log(fileName, line, funcName, level, msg);
    }

    Logger WithLevel(const LogLevel level) const {
      return Logger(impl_, level);
    }

    operator bool() const {
      return impl_ != nullptr;
    }

    static Logger Default() {
      return Logger(GlobalImpl, GlobalLevel);
    }

    static inline std::shared_ptr<ILogger> GlobalImpl = std::make_shared<StreamLogger>(std::cerr);
    static inline LogLevel GlobalLevel = LogLevel::TRACE;

  private:
    static inline std::string LogLevelNames[static_cast<int>(LogLevel::NONE)] = {
      "TRACE",
      "DEBUG",
      "INFO",
      "WARN",
      "ERROR",
    };

    std::shared_ptr<ILogger> impl_;
    LogLevel level_;
  };

  #define LOG_MSG_WITH_LOGGER(logger, level, msg)                         \
    if (logger && logger.ShouldLog(level)) {                              \
      std::ostringstream sstream;                                         \
      sstream << msg;                                                     \
      logger.Log(__FILE__, __LINE__, __FUNCTION__, level, sstream.str()); \
    } 

  #define LOG_MSG_DEFAULT_LOGGER(level, msg) {           \
      LOG_MSG_WITH_LOGGER(Logger::Default(), level, msg) \
    }

  #define SELECT_LOG_FUNC(_1, _2, _3, NAME, ...) NAME

  #define LOG_MSG(...) SELECT_LOG_FUNC(__VA_ARGS__, LOG_MSG_WITH_LOGGER, LOG_MSG_DEFAULT_LOGGER)

  #define LOG_TRACE(logger, msg) LOG_MSG(logger, LogLevel::TRACE, msg)
  #define LOG_TRACE(msg) LOG_MSG(LogLevel::TRACE, msg)

  #define LOG_DEBUG(logger, msg) LOG_MSG(logger, LogLevel::DEBUG, msg)
  #define LOG_DEBUG(msg) LOG_MSG(LogLevel::DEBUG, msg)

  #define LOG_INFO(logger, msg) LOG_MSG(logger, LogLevel::INFO, msg)
  #define LOG_INFO(msg) LOG_MSG(LogLevel::INFO, msg)

  #define LOG_WARN(logger, msg) LOG_MSG(logger, LogLevel::WARN, msg)
  #define LOG_WARN(msg) LOG_MSG(LogLevel::WARN, msg)

  #define LOG_ERROR(logger, msg) LOG_MSG(logger, LogLevel::ERROR, msg)
  #define LOG_ERROR(msg) LOG_MSG(LogLevel::ERROR, msg)

} // namespace fermi

#endif // FERMIBREAKUP_UTILITIES_LOGGER_H
