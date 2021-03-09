

#include "net.h"

//#include <windows.h>
#include <winsock2.h>
#include <iphlpapi.h>

#include <iostream>
#include <memory>


template <class T> const T* ifnull(const T* p, const T* q)
{
	return p ? p : q;
}


std::optional<NIInfoList> GetNIInfoList(void)
{
	std::optional<NIInfoList> ret;

	int num = 15 * 1024 / sizeof(IP_ADAPTER_ADDRESSES_LH);
	std::unique_ptr<IP_ADAPTER_ADDRESSES_LH[]> buf(new IP_ADAPTER_ADDRESSES_LH[num]);
	ULONG r;

	while (1)
	{
		ULONG size = num * sizeof(IP_ADAPTER_ADDRESSES_LH);
		r = ::GetAdaptersAddresses(AF_UNSPEC, 0, NULL, buf.get(), &size);
		if (r == ERROR_BUFFER_OVERFLOW && num < 999)
		{
			num *= 2;
			buf.reset(new IP_ADAPTER_ADDRESSES_LH[num]);
			continue;
		}
		else if (r == NO_ERROR)
		{
			num = size / sizeof(IP_ADAPTER_ADDRESSES_LH);
			break;
		}
		return ret;
	}

	std::cout << num << std::endl;
	IP_ADAPTER_ADDRESSES_LH *p = &buf[0];

	IP_ADAPTER_ADDRESSES_LH *ptr = buf.get();
	NIInfoList lst;
	while (ptr) {
		NIInfo nii = {};
		nii.name = ifnull(ptr->AdapterName, "");
		nii.friendly_name = ifnull(ptr->FriendlyName, L"");
		nii.metric = (int)ptr->Ipv4Metric;
		nii.metric_v6 = (int)ptr->Ipv6Metric;
		memcpy(nii.macaddr, ptr->PhysicalAddress, 6);
		


		lst.push_back(std::move(nii));
		ptr = ptr->Next;
	}


	return std::move(lst);
}
