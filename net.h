#pragma once

#include <string>
#include <vector>
#include <optional>


struct NIInfo
{
    typedef uint8_t ip4addr_t[4];
    typedef uint8_t ip6addr_t[64];

	std::string name;
    std::wstring friendly_name;
	std::vector<ip4addr_t> ip4addr;
	std::vector<ip6addr_t> ip6addr;
    uint8_t macaddr[6];
    int metric, metric_v6;
};

typedef std::vector<NIInfo> NIInfoList;


std::optional<NIInfoList> GetNIInfoList(void);

