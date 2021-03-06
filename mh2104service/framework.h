#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_FREE_THREADED

#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit


#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <atlstr.h>
#include <string>
#include <Wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")

class Logger
{
public:
	void LogEvent(LPCTSTR psz);
private:
	//ATL::CComCriticalSection m_cs;
};

extern Logger Log;
