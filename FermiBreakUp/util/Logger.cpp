#include "Logger.h"

using namespace fermi;

namespace {
  static const std::string LogLevelNames[static_cast<int>(LogLevel::NONE)] = {
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
          << LogLevelNames[static_cast<int>(level)] << ": " << msg << std::endl;
}
