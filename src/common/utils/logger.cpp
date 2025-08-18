#include "logger.h"

#include <iostream>

namespace common {
namespace utils {

void Logger::Init() {}

void Logger::Log(LogLevel level, const std::string& message) {
  switch (level) {
    case LogLevel::kInfo:
      std::cout << "INFO: ";
      break;

    case LogLevel::kWarning:
      std::clog << "WARNING: ";
      break;

    case LogLevel::kError:
      std::cerr << "ERROR: ";
      break;
  }

  std::cout << message << "\n";
}

void Logger::Info(const std::string& message) { Log(LogLevel::kInfo, message); }

void Logger::Warning(const std::string& message) {
  Log(LogLevel::kWarning, message);
}

void Logger::Error(const std::string& message) {
  Log(LogLevel::kError, message);
}

}  // namespace utils
}  // namespace common