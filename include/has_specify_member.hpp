/**
 * @file has_specify_member.hpp
 * @author Quenwaz (404937333@qq.com)
 * @brief 判断某类是否存在指定成员
 * @version 0.1
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022 Quenwaz
 * 
 */

#ifndef _h_has_specify_member_included__
#define _h_has_specify_member_included__
#include <type_traits>


namespace tpl_utils{


/**
 * @brief 检查指定类是否存在成员方法size以及push
 * 
 * @tparam T 类类型
 */
template<typename T>
struct HasSpecifyMember
{
private:
    template<typename U> static auto Check(int) -> decltype(std::declval<U>().size(), std::declval<U>().push(std::declval<typename U::value_type>()), std::true_type());
    template<typename U> static auto Check(...) -> decltype(std::false_type());
public:
    static const bool value = std::is_same<decltype(Check<T>(0)), std::true_type>::value;
};

template<typename T>
const bool HasSpecifyMember<T>::value;

/**
 * @brief 线程函数转发， 
 *        需求源自pthread_create时需要传入线程执行函数的函数指针
 * 
 * @tparam ClassType 类类型
 * @tparam void(ClassType::*)(void*) 限定类中必须存在指定格式的成员函数
 * @param param 任意类型形参
 * @return 确保模板参数类有成员方法run
 */
template <typename ClassType, void(ClassType::*)(void*)>
std::enable_if_t<std::is_same_v<decltype(std::declval<ClassType>().run(std::declval<void*>()), std::true_type()), std::true_type>, void*>
thread_rounter(void* param)
{
    ClassType* p = (ClassType*)param;
    p->run(param);
    return NULL;
}
}


#endif // _h_has_specify_member_included__