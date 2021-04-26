// mhPolicy.cpp : Implementation of CmhPolicy

#include "pch.h"
#include "mhPolicy.h"
#include "MdmWmi.h"

// CmhPolicy

/*
Example from a virtual machine, in powershell:
==============================================

$namespaceName = "root\cimv2\mdm\dmmap"

$namespaceName = "root\cimv2\mdm\dmmap"
$className = "MDM_Policy_Config01_Camera02"
New-CimInstance -Namespace $namespaceName -ClassName $className -Property @{ParentID="./Vendor/MSFT/Policy/Config";InstanceID="Camera";AllowCamera=0}

AllowCamera InstanceID ParentID                    PSComputerName
----------- ---------- --------                    --------------
          0 Camera     ./Vendor/MSFT/Policy/Config

Get-CimInstance -Namespace $namespaceName -ClassName "MDM_Policy_Result01_Camera02"

AllowCamera InstanceID ParentID                    PSComputerName
----------- ---------- --------                    --------------
          0 Camera     ./Vendor/MSFT/Policy/Result


https://docs.microsoft.com/en-us/windows/win32/dmwmibridgeprov/mdm-policy-config01-devicelock02
DevicePasswordEnabled should not be set to Enabled (0) when WMI is used to set the EAS DeviceLock
policies given that it is Enabled by default in Policy CSP for back compat with Windows 8.x.
If DevicePasswordEnabled is set to Enabled(0) then Policy CSP will return an error stating that
DevicePasswordEnabled already exists. Windows 8.x did not support DevicePassword policy.
When disabling DevicePasswordEnabled (1) then this should be the only policy set from the
DeviceLock group of policies below. The policies are listed below: > - DevicePasswordEnabled is
the parent policy of the following:
	DevicePasswordEnabled is the parent policy of the following:
		AllowSimpleDevicePassword
		MinDevicePasswordLength
		AlphanumericDevicePasswordRequired is the parent policy of:
			MinDevicePasswordComplexCharacters
		MaxDevicePasswordFailedAttempts
		MaxInactivityTimeDeviceLock
If AlphanumericDevicePasswordRequired is set to 1 or 2,
	then MinDevicePasswordLength = 0 and MinDevicePasswordComplexCharacters = 1.
If AlphanumericDevicePasswordRequired is set to 0,
	then MinDevicePasswordLength = 4 and MinDevicePasswordComplexCharacters = 2.


Get-CimInstance -Namespace $namespaceName -ClassName "MDM_Policy_Result01_DeviceLock02"

AllowScreenTimeoutWhileLockedUserConfig : 0
AllowSimpleDevicePassword               : 1
AlphanumericDevicePasswordRequired      : 2
DevicePasswordEnabled                   : 1
DevicePasswordExpiration                : 0
DevicePasswordHistory                   : 0
EnforceLockScreenAndLogonImage          :
EnforceLockScreenProvider               :
InstanceID                              : DeviceLock
MaxDevicePasswordFailedAttempts         : 0
MaxInactivityTimeDeviceLock             : 0
MinDevicePasswordComplexCharacters      : 1
MinDevicePasswordLength                 : 4
MinimumPasswordAge                      : 0
ParentID                                : ./Vendor/MSFT/Policy/Result
PreventEnablingLockScreenCamera         : <NotConfigured/>
PreventLockScreenSlideShow              : <NotConfigured/>
ScreenTimeoutWhileLocked                : 10
PSComputerName                          :


https://docs.microsoft.com/en-us/windows/client-management/mdm/policy-csp-devicelock

*/



STDMETHODIMP CmhPolicy::ClearCameraPolicy()
{
	HRESULT hr;

	CComPtr<IWbemServices> pSvc;
	hr = mdmWmi::GetMdmWmiObject(pSvc);
	if (FAILED(hr))
		return hr;

	hr = pSvc->DeleteInstance(
		CComBSTR(L"MDM_Policy_Config01_Camera02.InstanceID=\"Camera\",ParentID=\"./Vendor/MSFT/Policy/Config\""),
		0, NULL, NULL);
	if (FAILED(hr))
	{
		// already missing? Should be ok.
		return S_FALSE;
		//Log.LogEvent(_T("DeleteInstance failed."));
		//return hr;
	}

	return S_OK;
}


STDMETHODIMP CmhPolicy::SetCameraPolicy(LONG lAllowCamera)
{
	HRESULT hr;

	CComPtr<IWbemServices> pSvc;
	hr = mdmWmi::GetMdmWmiObject(pSvc);
	if (FAILED(hr))
		return hr;

	CComPtr<IWbemClassObject> pclsObj;
	hr = mdmWmi::GetOrCreateObject(pSvc,
		L"MDM_Policy_Config01_Camera02",
		L"./Vendor/MSFT/Policy/Config",
		L"Camera", pclsObj);
	if (FAILED(hr))
		return hr;

	CComVariant vtProp(lAllowCamera, VT_I4);
	hr = pclsObj->Put(L"AllowCamera", 0, &vtProp, 0);
	if (FAILED(hr))
	{
		Log.LogEvent(_T("Put failed."));
		return hr;
	}
	hr = pSvc->PutInstance(pclsObj, WBEM_FLAG_CREATE_OR_UPDATE, NULL, NULL);
	if (FAILED(hr))
	{
		Log.LogEvent(_T("PutInstance failed."));
		return hr;
	}

	return S_OK;
}


STDMETHODIMP CmhPolicy::ClearPasswordPolicy()
{
	HRESULT hr;

	CComPtr<IWbemServices> pSvc;
	hr = mdmWmi::GetMdmWmiObject(pSvc);
	if (FAILED(hr))
		return hr;

	hr = pSvc->DeleteInstance(
		CComBSTR(L"MDM_Policy_Config01_DeviceLock02.InstanceID=\"DeviceLock\",ParentID=\"./Vendor/MSFT/Policy/Config\""),
		0, NULL, NULL);
	if (FAILED(hr))
	{
		// already missing? Should be ok.
		return S_FALSE;
		//Log.LogEvent(_T("DeleteInstance failed."));
		//return hr;
	}

	return S_OK;
}


STDMETHODIMP CmhPolicy::SetPasswordPolicy(LONG lAllowSimpleDevicePassword, LONG lAlphanumericDevicePasswordRequired, LONG lDevicePasswordEnabled, LONG lMinDevicePasswordComplexCharacters, LONG lMinDevicePasswordLength)
{
	HRESULT hr;

	CComPtr<IWbemServices> pSvc;
	hr = mdmWmi::GetMdmWmiObject(pSvc);
	if (FAILED(hr))
		return hr;

	CComPtr<IWbemClassObject> pclsObj;
	hr = mdmWmi::GetOrCreateObject(pSvc,
		L"MDM_Policy_Config01_DeviceLock02",
		L"./Vendor/MSFT/Policy/Config",
		L"DeviceLock", pclsObj);
	if (FAILED(hr))
		return hr;

	if (S_FALSE == hr) // newly created
	{
		// set a few properties to 0
		//CComVariant vtProp(0, VT_I4);
		//hr = pclsObj->Put(L"DevicePasswordExpiration", 0, &vtProp, 0);
		//if (SUCCEEDED(hr))
		//	hr = pclsObj->Put(L"DevicePasswordHistory", 0, &vtProp, 0);
		//if (SUCCEEDED(hr))
		//	hr = pclsObj->Put(L"MaxDevicePasswordFailedAttempts", 0, &vtProp, 0);
		//if (SUCCEEDED(hr))
		//	hr = pclsObj->Put(L"MaxInactivityTimeDeviceLock", 0, &vtProp, 0);

		//if (SUCCEEDED(hr))
		//	hr = pclsObj->Put(L"AllowScreenTimeoutWhileLockedUserConfig", 0, &vtProp, 0);
		//if (SUCCEEDED(hr))
		//	hr = pclsObj->Put(L"MinimumPasswordAge", 0, &vtProp, 0);
		//vtProp = CComVariant(10, VT_I4);
		//if (SUCCEEDED(hr))
		//	hr = pclsObj->Put(L"ScreenTimeoutWhileLocked", 0, &vtProp, 0);
		//vtProp = CComVariant(L"");
		//if (SUCCEEDED(hr))
		//	hr = pclsObj->Put(L"EnforceLockScreenAndLogonImage", 0, &vtProp, 0);
		//if (SUCCEEDED(hr))
		//	hr = pclsObj->Put(L"EnforceLockScreenProvider", 0, &vtProp, 0);
		//vtProp = CComVariant(L"<NotConfigured/>");
		//if (SUCCEEDED(hr))
		//	hr = pclsObj->Put(L"PreventEnablingLockScreenCamera", 0, &vtProp, 0);
		//if (SUCCEEDED(hr))
		//	hr = pclsObj->Put(L"PreventLockScreenSlideShow", 0, &vtProp, 0);
	}

	// It seems that the order and grouping (and values) of theses settings are important.
	// Otherwise the call to PutInstance fails. 0x80041019 or 0x80041001
	if (SUCCEEDED(hr))
	{
		CComVariant vtProp(lDevicePasswordEnabled, VT_I4);
		hr = pclsObj->Put(L"DevicePasswordEnabled", 0, &vtProp, 0);
	}

	hr = pSvc->PutInstance(pclsObj, WBEM_FLAG_CREATE_OR_UPDATE, NULL, NULL);
	if (FAILED(hr))
	{
		Log.LogEvent(_T("PutInstance failed."));
		return hr;
	}

	if (SUCCEEDED(hr))
	{
		CComVariant vtProp(lAllowSimpleDevicePassword, VT_I4);
		hr = pclsObj->Put(L"AllowSimpleDevicePassword", 0, &vtProp, 0);
	}
	if (SUCCEEDED(hr))
	{
		CComVariant vtProp(lAlphanumericDevicePasswordRequired, VT_I4);
		hr = pclsObj->Put(L"AlphanumericDevicePasswordRequired", 0, &vtProp, 0);
	}

	hr = pSvc->PutInstance(pclsObj, WBEM_FLAG_CREATE_OR_UPDATE, NULL, NULL);
	if (FAILED(hr))
	{
		Log.LogEvent(_T("PutInstance failed."));
		return hr;
	}

	if (SUCCEEDED(hr))
	{
		CComVariant vtProp(lMinDevicePasswordComplexCharacters, VT_I4);
		hr = pclsObj->Put(L"MinDevicePasswordComplexCharacters", 0, &vtProp, 0);
	}
	if (SUCCEEDED(hr))
	{
		CComVariant vtProp(lMinDevicePasswordLength, VT_I4);
		hr = pclsObj->Put(L"MinDevicePasswordLength", 0, &vtProp, 0);
	}
	if (FAILED(hr))
	{
		Log.LogEvent(_T("Put failed."));
		return hr;
	}
	hr = pSvc->PutInstance(pclsObj, WBEM_FLAG_CREATE_OR_UPDATE, NULL, NULL);
	if (FAILED(hr))
	{
		Log.LogEvent(_T("PutInstance failed."));
		return hr;
	}

	return S_OK;
}
