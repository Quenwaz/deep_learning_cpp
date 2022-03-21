/**
 * @file functors_as_ordinary_functions.hpp
 * @author Quenwaz (404937333@qq.com)
 * @brief 仿函数作为普通函数使用。 通常用于C方式的函数指针
 * @version 0.1
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022 Quenwaz
 * 
 */
#ifndef _h_functors_as_ordinary_functions_included__
#define _h_functors_as_ordinary_functions_included__
#include <type_traits>
#include <functional>

namespace tpl_utils{
template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)> {
    template <typename... Args>
    static Ret Function(Args... args) {
        assert(fn_agent_ != nullptr);
        if constexpr (std::is_same_v<Ret, void>) {
            fn_agent_(args...);
            fn_agent_ = nullptr;
        }
        else {
            auto&& result = fn_agent_(args...);
            fn_agent_ = nullptr;
            return result;
        }
    }

    static std::function<Ret(Params...)> fn_agent_;
};

// Initialize the static member.
template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::fn_agent_;

}

#endif // _h_functors_as_ordinary_functions_included__