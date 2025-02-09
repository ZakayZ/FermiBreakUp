//
// Created by Artem Novikov on 08.01.2025.
//

#ifndef FERMIBREAKUP_UTILITIES_LOGGER_H
#define FERMIBREAKUP_UTILITIES_LOGGER_H

#include <string_view>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>

namespace fbu {

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
    virtual void Log(
      const std::string_view fileName,
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

    void Log(
      const std::string_view fileName,
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

    void Log(
      const std::string_view fileName,
      const int line,
      const std::string_view funcName,
      const LogLevel level,
      const std::string_view msg)
    {
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
    static inline LogLevel GlobalLevel = LogLevel::ERROR;

  private:
    std::shared_ptr<ILogger> impl_;
    LogLevel level_;
  };

  #define FERMI_LOG_MSG(logger, level, msg)                               \
    if (logger && logger.ShouldLog(level)) {                              \
      std::ostringstream sstream;                                         \
      sstream << msg;                                                     \
      logger.Log(__FILE__, __LINE__, __FUNCTION__, level, sstream.str()); \
    } 

  #define FERMI_LOG_TRACE(msg) FERMI_LOG_MSG(Logger::Default(), LogLevel::TRACE, msg)
  #define FERMI_LOG_DEBUG(msg) FERMI_LOG_MSG(Logger::Default(), LogLevel::DEBUG, msg)
  #define FERMI_LOG_INFO(msg) FERMI_LOG_MSG(Logger::Default(), LogLevel::INFO, msg)
  #define FERMI_LOG_WARN(msg) FERMI_LOG_MSG(Logger::Default(), LogLevel::WARN, msg)
  #define FERMI_LOG_ERROR(msg) FERMI_LOG_MSG(Logger::Default(), LogLevel::ERROR, msg)

#if defined(WIN32) || defined(__MINGW32__)
  #define FERMI_UNLIKELY(x) (x)
  #define FERMI_LIKELY(x)   (x)
#else
  #define FERMI_UNLIKELY(x) __builtin_expect((x), false)
  #define FERMI_LIKELY(x)   __builtin_expect((x), true)
#endif

  #define FERMI_ASSERT_MSG(COND, MSG)                     \
    if (FERMI_UNLIKELY(!(COND))) {                        \
      std::ostringstream sstream;                         \
      sstream << "assertion failed: \"" << #COND << '\"'  \
              << " at " << __FILE__ << ':' << __LINE__    \
              << '\n' << MSG;                             \
      throw std::runtime_error(sstream.str());            \
    }

} // namespace fbu

#endif // FERMIBREAKUP_UTILITIES_LOGGER_H
