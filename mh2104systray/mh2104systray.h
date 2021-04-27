#pragma once

#include "resource.h"

constexpr auto MAX_LOADSTRING = 100;

class CSysTrayApp
{
public:
	BOOL                InitInstance(_In_ HINSTANCE hInstance, _In_ int nCmdShow);

private:
	ATOM                RegisterWindowClass(HINSTANCE hInstance, PCWSTR pszClassName, PCWSTR pszMenuName, WNDPROC lpfnWndProc);
	static LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
	static INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
	void                ShowContextMenu(HWND hwnd, POINT pt);
	BOOL                AddNotificationIcon(HWND hwnd);
	static BOOL         DeleteNotificationIcon(HWND hwnd);
	static BOOL         RestoreTooltip(HWND hwnd);

	HINSTANCE hInst;                                // current instance
	WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

	static constexpr UINT WMAPP_NOTIFYCALLBACK = WM_APP + 1;
	static constexpr UINT SYSTRAYICONID = 1;
};

extern CSysTrayApp g_theSysTrayApp;
