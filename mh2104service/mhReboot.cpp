// mhReboot.cpp : Implementation of CmhReboot

#include "pch.h"
#include "mhReboot.h"
#include "MdmWmi.h"

// CmhReboot


STDMETHODIMP CmhReboot::DoReboot()
{
	HRESULT hr;

	CComPtr<IWbemServices> pSvc;
	hr = mdmWmi::GetMdmWmiObject(pSvc);
	if (FAILED(hr))
		return hr;

	CComPtr<IWbemClassObject> pOutParams;
	hr = pSvc->ExecMethod(CComBSTR(L"MDM_Reboot.InstanceID=\"Reboot\",ParentID=\"./Vendor/MSFT\""), CComBSTR(L"RebootNowMethod"), 0, NULL, NULL, &pOutParams, NULL);
	if (FAILED(hr))
	{
		Log.LogEvent(_T("Failed calling ExecMethod"));
		return hr;
	}
	return S_OK;
}
