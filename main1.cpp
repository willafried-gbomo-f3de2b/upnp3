﻿
#define UPNP_DEBUG_C

#include "upnp/upnp.h"
#include "upnp/UpnpLog.h"
#include "upnp/upnptools.h"
#include "sqlite/sqlite3.h"
#include "matroska/matroska_export.h"
#include "matroska/FileKax.h"
#include "FLAC/all.h"

#include "net.h"

#include <windows.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <locale>
#include <thread>
#include <string>

void build(void)
{
	const char *build_type =
#ifdef CBUILD_TYPE
		BUILD_TYPE;
#else
		"N/A";
#endif
	std::cout << "BuildType: " << build_type << std::endl;
}

typedef struct COOKIE
{
	int a;
} COOKIE;

struct A
{
};

void OnActionRequest(Upnp_EventType EventType, const void *Event, const void *Cookie)
{
	std::cout << "OnActionRequest()" << std::endl;
	UpnpActionRequest *ptr = (UpnpActionRequest *)Event;
	UpnpActionRequest *ev = (UpnpActionRequest *)Event;

	const char *devUDN = UpnpString_get_String(
		UpnpActionRequest_get_DevUDN(ev));
	const char *serviceID = UpnpString_get_String(
		UpnpActionRequest_get_ServiceID(ev));
	const char *actionName = UpnpString_get_String(
		UpnpActionRequest_get_ActionName(ev));
	std::cout << "udn:" << ifnull(devUDN, "")
			  << ", sid:" << ifnull(serviceID, "")
			  << ", act:" << ifnull(actionName, "") << std::endl;

	IXML_Document *xml_req = UpnpActionRequest_get_ActionRequest(ev);
	IXML_Document *xml_res = nullptr;
	int e = UpnpAddToActionResponse(&xml_res, actionName, serviceID, "SearchCaps", "1");
	UpnpActionRequest_set_ActionResult(ev, xml_res);

	// std::cout << ptr->m_ActionName << std::endl;
}

// int fncb(Upnp_EventType EventType, const void *Event, void *Cookie)
int fncb(UpnpLib *p, Upnp_EventType EventType, const void *Event, const void *Cookie)
{
	std::cout << "fncb"
			  << ", EventType=" << EventType << ", Event=" << std::hex << Event
			  << ", cookie=" << Cookie << std::endl;

	switch (EventType)
	{
	case UPNP_CONTROL_ACTION_REQUEST:
		OnActionRequest(EventType, Event, Cookie);
		break;
	}
	return UPNP_E_SUCCESS;
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
	build();
	std::string a(ifnull("", "a"));

	// std::string root_xml = std::string(argv[0]).substr(0,
	// std::string(argv[0]).find_last_of("\\")) + "\\root.xml"; std::string root
	// = std::string(argv[0]).substr(0,
	// std::string(argv[0]).find_last_of("\\"));
	std::string root = ifnull(::getenv("WEB_ROOT_PATH"), "");
	std::cout << root << std::endl;
	int port = 50123;

	auto niilst = GetNIInfoList();
	if (!niilst)
	{
		std::cout << "error1" << std::endl;
		return 1;
	}

	niilst.value().erase(
		std::remove_if(std::begin(niilst.value()), std::end(niilst.value()),
					   [](auto &nii) {
						   return !nii.up || !(nii.ip4addr.size() || nii.ip6addr.size());
					   }),
		std::end(niilst.value()));

	std::sort(std::begin(niilst.value()), std::end(niilst.value()),
			  [](auto &n1, auto &n2) { return n1.metric < n2.metric; });

#pragma endregion
	NIInfo &nii = niilst.value()[0];
	int e;

	// UpnpSetLogFileName("pupnp.log", "");

	setlocale(LC_ALL, ".utf8");
	//setlocale(LC_ALL, "");
	std::cout << ::GetThreadLocale() << std::endl;

	//nii.friendly_name = L"Wi-Fi 第二";
	char buf[256] = {};
	::WideCharToMultiByte(
		CP_UTF8, 0, nii.friendly_name.c_str(), -1, buf, sizeof buf, NULL, NULL);
	std::cout << "nii.friend: " << buf << std::endl;

	UpnpLib *upnp = nullptr;
	UpnpLog* upnp_log = UpnpLog_new();

	UpnpSetLogFileName(upnp_log, "pupnp.log");

	if ((e = UpnpInit2(&upnp, buf, port, "upnplog.txt")) != UPNP_E_SUCCESS)
	{
		std::cout << "error. UpnpInit2, " << e << std::endl;
		return 1;
	}

	//UpnpSetLogFileName(upnp, "pupnp.log");

	if ((e = UpnpSetWebServerRootDir(upnp, root.c_str())) != UPNP_E_SUCCESS)
	{
		std::cout << "error. UpnpSetWebServerRootDir, " << e << std::endl;
		return 1;
	};

	// const char url[] = "http://192.168.11.12/xml.xml";
	const std::string url = std::string("http://") +
							make_address_string(nii.ip4addr[0].data()) + ":" +
							std::to_string(port) + "/root.xml";

	std::wstring ws = L"Bluetooth ネットワーク接続 2";
	char cbuf[100] = {};
	wcstombs(cbuf, ws.c_str(), 100);
	std::cout << cbuf << std::endl;

	COOKIE cookie = {123};
	UpnpDevice_Handle hnd;
	if ((e = UpnpRegisterRootDevice(upnp, url.c_str(), fncb, &cookie, &hnd)) !=
		UPNP_E_SUCCESS)
	{
		std::cout << "error. UpnpRegisterRootDevice, " << e << std::endl;
		return 1;
	}

	if ((e = UpnpSendAdvertisement(upnp, hnd, 0)) != UPNP_E_SUCCESS)
	{
		std::cout << "error. UpnpSendAdvertisement, " << e << std::endl;
		return 1;
	}

	std::this_thread::sleep_for(std::chrono::seconds(60));

	if ((e = UpnpFinish(upnp)) != UPNP_E_SUCCESS)
	{
		std::cout << "error. UpnpFinish, " << e << std::endl;
		return 1;
	}

	matroska_init();
	FLAC__StreamDecoder *decoder = FLAC__stream_decoder_new();
	auto sqlv = sqlite3_libversion();

	std::cout << "main.end." << std::endl;

	return 0;
}
