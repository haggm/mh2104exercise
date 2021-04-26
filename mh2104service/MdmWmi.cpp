#include "pch.h"
#include "MdmWmi.h"

namespace mdmWmi
{

	HRESULT GetMdmWmiObject(CComPtr<IWbemServices>& pSvc)
	{
		HRESULT hr;

		CComPtr<IWbemLocator> pLoc;
		hr = pLoc.CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER);
		if (FAILED(hr))
		{
			Log.LogEvent(_T("Failed to create IWbemLocator object."));
			return hr;
		}

		hr = pLoc->ConnectServer(
			CComBSTR(L"ROOT\\CIMV2\\mdm\\dmmap"), // Object path of WMI namespace
			NULL,					// User name. NULL = current user
			NULL,					// User password. NULL = current
			NULL,					// Locale. NULL indicates current
			0,						// Security flags.
			NULL,					// Authority (for example, Kerberos)
			NULL,					// Context object 
			&pSvc					// pointer to IWbemServices proxy
		);
		if (FAILED(hr))
		{
			Log.LogEvent(_T("Could not connect to Wmi server."));
			return hr;
		}

		hr = CoSetProxyBlanket(
			pSvc,							// Indicates the proxy to set
			RPC_C_AUTHN_WINNT,				// RPC_C_AUTHN_xxx
			RPC_C_AUTHZ_NONE,				// RPC_C_AUTHZ_xxx
			NULL,							// Server principal name 
			RPC_C_AUTHN_LEVEL_CALL,			// RPC_C_AUTHN_LEVEL_xxx 
			RPC_C_IMP_LEVEL_IMPERSONATE,	// RPC_C_IMP_LEVEL_xxx
			NULL,							// client identity
			EOAC_NONE						// proxy capabilities 
		);
		if (FAILED(hr))
		{
			Log.LogEvent(_T("Could not set proxy blanket."));
			return hr;
		}
		return S_OK;
	}


	HRESULT CreateObject(IWbemServices* pSvc, const wchar_t* szClass, const wchar_t* szParentID, const wchar_t* szInstanceID, CComPtr<IWbemClassObject>& pclsObj)
	{
		HRESULT hr;
		CComPtr<IWbemClassObject> pcls;
		hr = pSvc->GetObject(CComBSTR(szClass), 0, NULL, &pcls, NULL);
		if (FAILED(hr))
		{
			Log.LogEvent(_T("GetObject failed."));
			return hr;
		}
		pclsObj = NULL;
		hr = pcls->SpawnInstance(0, &pclsObj);
		if (FAILED(hr))
		{
			Log.LogEvent(_T("SpawnInstance failed."));
			return hr;
		}
		CComVariant vtParentID(szParentID);
		hr = pclsObj->Put(L"ParentID", 0, &vtParentID, 0);
		if (FAILED(hr))
		{
			Log.LogEvent(_T("Put failed."));
			return hr;
		}
		CComVariant vtInstanceID(szInstanceID);
		hr = pclsObj->Put(L"InstanceID", 0, &vtInstanceID, 0);
		if (FAILED(hr))
		{
			Log.LogEvent(_T("Put failed."));
			return hr;
		}
		return S_OK;
	}


	HRESULT GetOrCreateObject(IWbemServices* pSvc, const wchar_t* szClass, const wchar_t* szParentID, const wchar_t* szInstanceID,  CComPtr<IWbemClassObject>& pclsObj)
	{
		std::wstring strWql(L"SELECT * FROM ");
		strWql += szClass;
		strWql += L" WHERE ParentID = '";
		strWql += szParentID;
		strWql += L"' and InstanceID = '";
		strWql += szInstanceID;
		strWql += L"' ";

		HRESULT hr;
		CComPtr<IEnumWbemClassObject> pEnumerator;
		hr = pSvc->ExecQuery(
			CComBSTR(L"WQL"),
			CComBSTR(strWql.c_str()),
			WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
			NULL,
			&pEnumerator);
		if (FAILED(hr))
		{
			Log.LogEvent(_T("Query failed."));
			return hr;
		}

		if (pEnumerator)
		{
			ULONG uReturn = 0;
			hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
			if (0 == uReturn)
			{
				// No policy config - create a new
				hr = CreateObject(pSvc, szClass, szParentID, szInstanceID, pclsObj);
				if (FAILED(hr))
					return hr;

				return S_FALSE; // to indicate a newly created object
			}
			return S_OK;
		}
		return E_FAIL;
	}
}
