#include "logger.h"

#include <iostream>

namespace common {
namespace utils {

void Logger::Log(LogLevel level, const std::string& message) {
  switch (level) {
    case LogLevel::INFO:
      std::cout << "INFO: ";
      break;

    case LogLevel::WARNING:
      std::cout << "WARNING: ";
      break;

    case LogLevel::ERROR:
      std::cout << "ERROR: ";
      break;
  }

  std::cout << message << "\n";
}

}  // namespace utils
}  // namespace common