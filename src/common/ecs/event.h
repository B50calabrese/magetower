#ifndef MAGETOWER_SRC_COMMON_ECS_EVENT_H_
#define MAGETOWER_SRC_COMMON_ECS_EVENT_H_

#include <string>

namespace common {
namespace ecs {

// Used to signal that something happened in the framework, typically to do
// 'system to world' level notifcations.
class Event {
 public:
  virtual ~Event() = default;

  virtual std::string name() const { return "Event"; }

  // Used to indicate whether or not an event should be purged on the first pass
  // if an event listerner doesn't consume it.
  virtual bool ShouldConsumeOnFirstPass() { return false; }
};

}  // namespace ecs
}  // namespace common

#endif  // MAGETOWER_SRC_COMMON_ECS_EVENT_H_