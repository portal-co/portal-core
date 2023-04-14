#include "wasm3_cpp.h"
#include <concepts>
#include <type_traits>
namespace wasm3 {
namespace detail {
template <typename Func, typename Ret, typename... Args>
requires std::invocable<Func, Args...> &&
    std::convertible_to<std::invoke_result<Func(Args...)>, Ret>
static const void *iwrap_fn([[maybe_unused]] IM3Runtime rt,
                            IM3ImportContext _ctx, stack_type _sp,
                            mem_type mem) {
  std::tuple<Args...> args;
  // The order here matters: m3ApiReturnType should go before calling
  // get_args_from_stack, since both modify `_sp`, and the return value on the
  // stack is reserved before the arguments.
  m3ApiReturnType(Ret);
  get_args_from_stack(_sp, mem, args);
  Func *function = reinterpret_cast<Func *>(_ctx->userdata);
  Ret r = std::apply(function, args);
  m3ApiReturn(r);
}
struct imodule {
  std::shared_ptr<M3Environment> m_env;
  std::shared_ptr<M3Module> m_module;
};
template <typename Func> class m3_wrapper_p {
public:
  template <typename Ret, typename... Args>
  static M3Result link_obj(IM3Module io_module, const char *const i_moduleName,
                           const char *const i_functionName, Func *function) {

    return m3_LinkRawFunctionEx(io_module, i_moduleName, i_functionName,
                                m3_signature<Ret, Args...>::value,
                                &iwrap_fn<Func, Ret, Args...>,
                                reinterpret_cast<void *>(function));
  }
};
} // namespace detail
template <typename Func, typename Ret, typename... Args>
void link_obj(module &m, const char *module, const char *function_name,
              Func *function) {
  M3Result ret = detail::m3_wrapper_p<Func>::template link_obj<Ret, Args...>(
      ((detail::imodule *)&m)->m_module.get(), module, function_name, function);
  detail::check_error(ret);
}

template <typename Func, typename Ret, typename... Args>
void link_optional_obj(module &m, const char *module, const char *function_name,
                       Func *function) {
  M3Result ret = detail::m3_wrapper_p<Func>::template link_obj<Ret, Args...>(
      ((detail::imodule *)&m)->m_module.get(), module, function_name, function);
  if (ret == m3Err_functionLookupFailed) {
    return;
  }
  detail::check_error(ret);
}
} // namespace wasm3