#include "logger.h"

using namespace fermi;

void StreamLogger::Log(const std::string_view fileName,
                       const int line,
                       const std::string_view funcName,
                       const LogLevel level,
                       const std::string_view msg)
{
  stream_ << fileName << ':' << line << " in function \"" << funcName
          << LogLevelNames[static_cast<int>(level)] << ": " << msg;
}
