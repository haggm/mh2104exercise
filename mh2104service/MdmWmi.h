#pragma once

using namespace ATL;

namespace mdmWmi
{
	HRESULT GetMdmWmiObject(CComPtr<IWbemServices>& pSvc);
	HRESULT CreateObject(IWbemServices* pSvc, const wchar_t* szClass, const wchar_t* szParentID, const wchar_t* szInstanceID, CComPtr<IWbemClassObject>& pclsObj);
	HRESULT GetOrCreateObject(IWbemServices* pSvc, const wchar_t* szClass, const wchar_t* szParentID, const wchar_t* szInstanceID, CComPtr<IWbemClassObject>& pclsObj);
}
