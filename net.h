#pragma once

#include <string>
#include <vector>
#include <optional>

struct NIInfo
{
    bool up;
    std::string name;
    std::wstring friendly_name;
    std::vector<std::vector<uint8_t>> ip4addr;
    std::vector<std::vector<uint8_t>> ip6addr;
    uint8_t macaddr[6];
    int metric, metric_v6;
};

typedef std::vector<NIInfo> NIInfoList;

std::optional<NIInfoList> GetNIInfoList(void);

// template <class T> const T *ifnull(const T *p, const T *q)
// {
// 	return p ? p : q;
// }

namespace datail {

template <class T, class U, class V = void> struct ifnulltmpl;

template <class T, class U> struct ifnulltmpl<T, U, std::enable_if<
    sizeof (decltype((T)std::declval<U>())) != 0
    >::type> 
{
    static T op(T t, U u) 
    {
        return (T)u;
    }
};

} // namespace datail

template <class T, class U> T ifnull(T t, U u)
{
    if ((void*)t == (void*)0) {
    return datail::ifnulltmpl<T, U>::op(t, u);
    }
    return t;
}


