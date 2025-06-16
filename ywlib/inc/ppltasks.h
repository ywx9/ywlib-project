#pragma once
#include <std/functional>

extern "C++" {
namespace Concurrency {
template<typename T> class task;
class task_options;
namespace details {
struct _BadArgType {};
template<typename T> _BadArgType _FilterValidTaskType(T Param, ...);
template<typename T> struct _TaskTypeFromParam {
  using type = decltype(_FilterValidTaskType(declval<T>(), 0));
};
}
template<typename T> __declspec(noinline) task<typename details::_TaskTypeFromParam<T>::type> create_task(T Param, task_options Options = task_options());
} // namespace Concurrency
}
