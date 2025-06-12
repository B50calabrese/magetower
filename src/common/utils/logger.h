#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace common {
namespace utils {

enum class LogLevel { INFO, WARNING, ERROR };

class Logger {
 public:
  static void Init() {}

  static void Log(LogLevel level, const std::string& message);

  static void Info(const std::string& message) { Log(LogLevel::INFO, message); }

  static void Warning(const std::string& message) {
    Log(LogLevel::WARNING, message);
  }

  static void Error(const std::string& message) {
    Log(LogLevel::ERROR, message);
  }
};
}  // namespace utils
}  // namespace common

#endif  // LOGGER_H