#ifndef COMMON_UTILS_LOGGER_H_
#define COMMON_UTILS_LOGGER_H_

#include <string>

namespace common {
namespace utils {

enum class LogLevel { kInfo, kWarning, kError };

class Logger {
 public:
  Logger() = delete;

  static void Init();
  static void Log(LogLevel level, const std::string& message);
  static void Info(const std::string& message);
  static void Warning(const std::string& message);
  static void Error(const std::string& message);
};
}  // namespace utils
}  // namespace common

#endif  // COMMON_UTILS_LOGGER_H_