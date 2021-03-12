﻿

// #include "thirdparty/pupnp/upnp/inc/upnp.h"
#include "thirdparty/pupnp/upnp/inc/upnp.h"
#include <upnpdebug.h>

#include "net.h"

#include <windows.h>

#include <iostream>
#include <algorithm>


typedef struct COOKIE
{
    int a;
} COOKIE;

int fncb(Upnp_EventType EventType, const void *Event, void *Cookie)
{
    std::cout << "fncb"
              << ", EventType=" << EventType << ", Event=" << std::hex << Event << ", cookie=" << Cookie << std::endl;

    return 0;
}

int main(int argc, char *argv[])
{
    std::cout << "main." << std::endl;

    auto niilst = GetNIInfoList();
    if (!niilst) {
        std::cout << "error1" << std::endl;
        return 1;
    }
    niilst.value().erase(std::remove_if(std::begin(niilst.value()), std::end(niilst.value()), [](auto& nii) {
        return !nii.up || !(nii.ip4addr.size() || nii.ip6addr.size());
    }), std::end(niilst.value()));

    std::sort(std::begin(niilst.value()), std::end(niilst.value()), [](auto& n1, auto& n2){
        return n1.metric < n2.metric;
    });
    
    int e;

    UpnpSetLogFileNames("pupnp.log", "");
    
    if ((e = UpnpInit2("Wi-Fi 2"/*"{B6E1F4CE-F6F0-4EB3-A144-4BDB80944B1C}"*/, 50123)) != UPNP_E_SUCCESS)
    {
        std::cout << "error. UpnpInit2" << std::endl;
        return 1;
    }

    const char url[] = "http://192.168.11.12/xml.xml";
    COOKIE cookie = {123};
    UpnpDevice_Handle h;
    if ((e = UpnpRegisterRootDevice(
             url, fncb, &cookie, &h)) != UPNP_E_SUCCESS)
    {
        std::cout << "error. UpnpRegisterRootDevice" << std::endl;
    }

    std::cout << "main.end." << std::endl;
}
