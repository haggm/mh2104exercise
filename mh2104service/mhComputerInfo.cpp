// mhComputerInfo.cpp : Implementation of CmhComputerInfo

#include "pch.h"
#include "mhComputerInfo.h"
#include "MdmWmi.h"

// CmhComputerInfo

//#ifdef DEBUG
// useful even when not debugging
#define SHOWPOLICYINFOTOO
//#endif

/*
Example from a virtual machine, in powershell:
==============================================

$namespaceName = "root\cimv2\mdm\dmmap"

Get-CimInstance -Namespace $namespaceName -ClassName "MDM_DevDetail"

DevTyp         : Standard PC (i440FX + PIIX, 1996)
FwV            : 1.13.0-1ubuntu1.1
HwV            : 1.13.0-1ubuntu1.1
InstanceID     : DevDetail
LrgObj         : False
OEM            : QEMU
ParentID       : .
SwV            : 10.0.19042.928
PSComputerName :

Get-CimInstance -Namespace $namespaceName -ClassName "MDM_DevDetail_Ext01"

DeviceHardwareData : ...
InstanceID         : Ext
ParentID           : ./DevDetail
WLANMACAddress     : 00-00-00-00-00-00
PSComputerName     :

Get-CimInstance -Namespace $namespaceName -ClassName "MDM_DevDetail_Microsoft02"

CommercializationOperator : Not Present
DeviceName                : M9
InstanceID                : Microsoft
LocalTime                 : 2021-04-22T19:27:56.0000636+02:00
MobileID                  : Not Present
OSPlatform                : Windows 10 Pro
ParentID                  : ./DevDetail/Ext
ProcessorArchitecture     : 9
ProcessorType             : 8664
RadioSwV                  : Not Present
Resolution                : 1024x768
PSComputerName            :

*/

// returns a multi line string with useful computer information
STDMETHODIMP CmhComputerInfo::GetInfo(BSTR* str)
{
	HRESULT hr;

	CComPtr<IWbemServices> pSvc;
	hr = mdmWmi::GetMdmWmiObject(pSvc);
	if (FAILED(hr))
		return hr;

	CStringW strResult;

	hr = GetSomeProperties(pSvc, L"SELECT * FROM MDM_DevDetail", std::vector<const wchar_t*>(
		{ L"DevTyp",
		L"SwV" }), strResult);
	if (FAILED(hr))
		return hr;

	hr = GetSomeProperties(pSvc, L"SELECT * FROM MDM_DevDetail_Microsoft02", std::vector<const wchar_t*>(
		{ L"DeviceName",
		L"OSPlatform",
		L"ProcessorArchitecture",
		L"ProcessorType" }), strResult);
	if (FAILED(hr))
		return hr;
	
	hr = GetSomeProperties(pSvc, L"SELECT * FROM MDM_DevDetail_Ext01", std::vector<const wchar_t*>(
		{ L"WLANMACAddress" }), strResult);
	if (FAILED(hr))
		return hr;

#ifdef SHOWPOLICYINFOTOO
	strResult += L"\nPolicy Config:\n";

	hr = GetSomeProperties(pSvc, L"SELECT * FROM MDM_Policy_Config01_Camera02 WHERE ParentID = './Vendor/MSFT/Policy/Config' and InstanceID = 'Camera' ", std::vector<const wchar_t*>(
		{ L"AllowCamera" }), strResult);
	if (FAILED(hr))
		return hr;

	hr = GetSomeProperties(pSvc, L"SELECT * FROM MDM_Policy_Config01_DeviceLock02 WHERE ParentID = './Vendor/MSFT/Policy/Config' and InstanceID = 'DeviceLock' ", std::vector<const wchar_t*>(
		{ L"AllowSimpleDevicePassword",
		L"AlphanumericDevicePasswordRequired",
		L"DevicePasswordEnabled",
		L"MinDevicePasswordComplexCharacters",
		L"MinDevicePasswordLength" }), strResult);
	if (FAILED(hr))
		return hr;

	strResult += L"\nPolicy Result:\n";

	hr = GetSomeProperties(pSvc, L"SELECT * FROM MDM_Policy_Result01_Camera02 WHERE ParentID = './Vendor/MSFT/Policy/Result' and InstanceID = 'Camera' ", std::vector<const wchar_t*>(
		{ L"AllowCamera" }), strResult);
	if (FAILED(hr))
		return hr;

	hr = GetSomeProperties(pSvc, L"SELECT * FROM MDM_Policy_Result01_DeviceLock02 WHERE ParentID = './Vendor/MSFT/Policy/Result' and InstanceID = 'DeviceLock' ", std::vector<const wchar_t*>(
		{ L"AllowSimpleDevicePassword",
		L"AlphanumericDevicePasswordRequired",
		L"DevicePasswordEnabled",
		L"MinDevicePasswordComplexCharacters",
		L"MinDevicePasswordLength" }), strResult);
	if (FAILED(hr))
		return hr;
#endif

	CComBSTR bstrResult(strResult);

	*str = bstrResult.Detach();
	return S_OK;
}


// adds one line of text per property 
HRESULT CmhComputerInfo::GetSomeProperties(IWbemServices* pSvc, const wchar_t* szWQL, std::vector<const wchar_t*> const& props, CStringW& strResult) const
{
	HRESULT hr;
	CComPtr<IEnumWbemClassObject> pEnumerator;
	hr = pSvc->ExecQuery(
		CComBSTR(L"WQL"),
		CComBSTR(szWQL),
		WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
		NULL,
		&pEnumerator);
	if (FAILED(hr))
	{
		Log.LogEvent(_T("mhComputerInfo: Query failed."));
		return hr;
	}

	while (pEnumerator)
	{
		CComPtr<IWbemClassObject> pclsObj;
		ULONG uReturn = 0;
		hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (0 == uReturn)
			break;

		for (auto i = 0; i < props.size(); ++i)
		{
			CComVariant vtProp;
			hr = pclsObj->Get(props[i], 0, &vtProp, 0, 0);
			if (SUCCEEDED(hr))
			{
				strResult += props[i];
				strResult += L" : ";
				if (vtProp.vt == VT_BSTR)
					strResult += CStringW(vtProp.bstrVal);
				else if (vtProp.vt == VT_I4)
					strResult += std::to_wstring(vtProp.lVal).c_str();
				strResult += L"\n";
			}
		}
	}
	return S_OK;
}

