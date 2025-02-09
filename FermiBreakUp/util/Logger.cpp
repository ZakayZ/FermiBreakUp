#include "Logger.h"

using namespace fbu;

namespace {
  static const std::array<std::string, static_cast<int>(LogLevel::NONE)> LOG_LEVEL_NAMES = {
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
  };
} // namespace

void StreamLogger::Log(
  const std::string_view fileName,
  const int line,
  const std::string_view funcName,
  const LogLevel level,
  const std::string_view msg)
{
  stream_ << fileName << ':' << line << " in function \"" << funcName << "\"\n"
          << LOG_LEVEL_NAMES[static_cast<int>(level)] << ": " << msg << std::endl;
}
