// mhPolicy.h : Declaration of the CmhPolicy

#pragma once
#include "resource.h"       // main symbols

#include "mh2104service_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CmhPolicy

class ATL_NO_VTABLE CmhPolicy :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CmhPolicy, &CLSID_mhPolicy>,
	public IDispatchImpl<ImhPolicy, &IID_ImhPolicy, &LIBID_mh2104serviceLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CmhPolicy()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(109)

	BEGIN_COM_MAP(CmhPolicy)
		COM_INTERFACE_ENTRY(ImhPolicy)
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
	STDMETHOD(ClearCameraPolicy)();
	STDMETHOD(SetCameraPolicy)(LONG lAllowCamera);
	STDMETHOD(ClearPasswordPolicy)();
	STDMETHOD(SetPasswordPolicy)(LONG lAllowSimpleDevicePassword, LONG lAlphanumericDevicePasswordRequired, LONG lDevicePasswordEnabled, LONG lMinDevicePasswordComplexCharacters, LONG lMinDevicePasswordLength);
};

OBJECT_ENTRY_AUTO(__uuidof(mhPolicy), CmhPolicy)
