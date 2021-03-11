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
