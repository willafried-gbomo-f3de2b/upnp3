

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

std::string make_address_string(uint8_t *u)
{
    std::string res;
    for (int i = 0; i < 4; i++, u++)
    {
        res += std::to_string(*u);
        if (i < 3)
            res += ".";
    }
    return std::move(res);
}

int main(int argc, char *argv[])
{
#pragma region
    std::cout << "main." << std::endl;

    std::string root_xml = std::string(argv[0]).substr(0, std::string(argv[0]).find_last_of("\\")) + "\\root.xml";
    std::string root = std::string(argv[0]).substr(0, std::string(argv[0]).find_last_of("\\"));

    auto niilst = GetNIInfoList();
    if (!niilst)
    {
        std::cout << "error1" << std::endl;
        return 1;
    }

    niilst.value().erase(std::remove_if(std::begin(niilst.value()), std::end(niilst.value()), [](auto &nii) {
                             return !nii.up || !(nii.ip4addr.size() || nii.ip6addr.size());
                         }),
                         std::end(niilst.value()));

    std::sort(std::begin(niilst.value()), std::end(niilst.value()), [](auto &n1, auto &n2) {
        return n1.metric < n2.metric;
    });

#pragma endregion
    NIInfo &nii = niilst.value()[0];
    int e;

    UpnpSetLogFileNames("pupnp.log", "");

    char buf[256] = {};
    ::WideCharToMultiByte(CP_ACP, 0, nii.friendly_name.c_str(), -1, buf, sizeof buf, NULL, NULL);

    if ((e = UpnpInit2(buf, 50123)) != UPNP_E_SUCCESS)
    {
        std::cout << "error. UpnpInit2, " << e << std::endl;
        return 1;
    }

    if ((e = UpnpSetWebServerRootDir(root.c_str())) != UPNP_E_SUCCESS)
    {
        std::cout << "error. UpnpSetWebServerRootDir, " << e << std::endl;
        return 1;
    };

    //const char url[] = "http://192.168.11.12/xml.xml";
    const std::string url = std::string("http://") + make_address_string(nii.ip4addr[0].data()) + ":50123"+ "/root.xml";

    COOKIE cookie = {123};
    UpnpDevice_Handle h;
    if ((e = UpnpRegisterRootDevice(
             url.c_str(), fncb, &cookie, &h)) != UPNP_E_SUCCESS)
    {
        std::cout << "error. UpnpRegisterRootDevice, " << e << std::endl;
        return 1;
    }

    if ((e = UpnpFinish()) != UPNP_E_SUCCESS)
    {
        std::cout << "error. UpnpFinish, " << e << std::endl;
        return 1;
    }
    std::cout << "main.end." << std::endl;
}
