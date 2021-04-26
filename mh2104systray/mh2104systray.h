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
	static BOOL         DeleteNotificationIcon();
	static BOOL         RestoreTooltip();

	HINSTANCE hInst;                                // current instance
	WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

	static constexpr UINT WMAPP_NOTIFYCALLBACK = WM_APP + 1;

	// Use a guid to uniquely identify our icon
#ifdef DEBUG
	class __declspec(uuid("23E65334-8D70-4EF1-8018-CBC7AD62D584")) SystrayIcon;
#else
	class __declspec(uuid("A587FA44-7B68-4094-A222-D51C06108C4A")) SystrayIcon;
#endif
};

extern CSysTrayApp g_theSysTrayApp;
