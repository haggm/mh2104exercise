// mhComputerInfo.h : Declaration of the CmhComputerInfo

#pragma once
#include "resource.h"       // main symbols
#include <vector>

#include "mh2104service_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CmhComputerInfo

class ATL_NO_VTABLE CmhComputerInfo :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CmhComputerInfo, &CLSID_mhComputerInfo>,
	public IDispatchImpl<ImhComputerInfo, &IID_ImhComputerInfo, &LIBID_mh2104serviceLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CmhComputerInfo()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(110)

	BEGIN_COM_MAP(CmhComputerInfo)
		COM_INTERFACE_ENTRY(ImhComputerInfo)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:
	STDMETHOD(GetInfo)(BSTR* str);

private:
	// adds one line of text per property 
	HRESULT GetSomeProperties(IWbemServices* pSvc, const wchar_t* szWQL, std::vector<const wchar_t*> const& props, CStringW& strResult) const;
};

OBJECT_ENTRY_AUTO(__uuidof(mhComputerInfo), CmhComputerInfo)
