// mh2104systray.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "mh2104systray.h"

// we need commctrl v6 for LoadIconMetric()
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "comctl32.lib")

#include "../mh2104service/mh2104service_i.h"
typedef _com_ptr_t<_com_IIID<ImhReboot, &__uuidof(ImhReboot)> > ImhRebootPtr;
typedef _com_ptr_t<_com_IIID<ImhPolicy, &__uuidof(ImhPolicy)> > ImhPolicyPtr;
typedef _com_ptr_t<_com_IIID<ImhComputerInfo, &__uuidof(ImhComputerInfo)> > ImhComputerInfoPtr;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!g_theSysTrayApp.InitInstance(hInstance, nCmdShow))
        return FALSE;

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MH2104SYSTRAY));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


ATOM CSysTrayApp::RegisterWindowClass(HINSTANCE hInstance, PCWSTR pszClassName, PCWSTR pszMenuName, WNDPROC lpfnWndProc)
{
    WNDCLASSEX wcex = { sizeof(wcex) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = lpfnWndProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MH2104SYSTRAY));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = pszMenuName;
    wcex.lpszClassName = pszClassName;
    return RegisterClassEx(&wcex);
}


// Initialize our global instance
BOOL CSysTrayApp::InitInstance(_In_ HINSTANCE hInstance, _In_ int nCmdShow)
{
    hInst = hInstance; // Store instance handle

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MH2104SYSTRAY, szWindowClass, MAX_LOADSTRING);
    RegisterWindowClass(hInstance, szWindowClass, MAKEINTRESOURCEW(IDC_MH2104SYSTRAY), WndProc);

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
        return FALSE;

    ShowWindow(hWnd, SW_HIDE);   // invisible main window
    //UpdateWindow(hWnd);

    return TRUE;
}


// Main window procedure
LRESULT CALLBACK CSysTrayApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        // add the notification icon
        if (!g_theSysTrayApp.AddNotificationIcon(hWnd))
        {
            MessageBox(hWnd, L"Error adding systray icon", L"Error", MB_OK);
            return -1;
        }
        {
            HRESULT hr = ::CoInitialize(NULL);
            assert(SUCCEEDED(hr));
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            long lParam = 0;
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(g_theSysTrayApp.hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case ID_CONFIGUREPOLICY_CLEARCAMERAPOLICY:
            {
                ImhPolicyPtr pPolicy;
                HRESULT hr = pPolicy.CreateInstance(CLSID_mhPolicy, nullptr, CLSCTX_LOCAL_SERVER);
                if (SUCCEEDED(hr))
                    hr = pPolicy->ClearCameraPolicy();
                if (FAILED(hr))
                    MessageBox(hWnd, L"Error modifying policy", L"Error", MB_OK);
            }
            break;
            case ID_CONFIGUREPOLICY_SETALLOWCAMERA_1:
                lParam = 1; // continue here
            case ID_CONFIGUREPOLICY_SETALLOWCAMERA_0:
            {
                ImhPolicyPtr pPolicy;
                HRESULT hr = pPolicy.CreateInstance(CLSID_mhPolicy, nullptr, CLSCTX_LOCAL_SERVER);
                if (SUCCEEDED(hr))
                    hr = pPolicy->SetCameraPolicy(lParam);
                if (FAILED(hr))
                    MessageBox(hWnd, L"Error modifying policy", L"Error", MB_OK);
            }
            break;
            case ID_CONFIGUREPOLICY_CLEARPASSWORDPOLICY:
            {
                ImhPolicyPtr pPolicy;
                HRESULT hr = pPolicy.CreateInstance(CLSID_mhPolicy, nullptr, CLSCTX_LOCAL_SERVER);
                if (SUCCEEDED(hr))
                    hr = pPolicy->ClearPasswordPolicy();
                if (FAILED(hr))
                    MessageBox(hWnd, L"Error modifying policy", L"Error", MB_OK);
            }
            break;
            // SetPasswordPolicy(lAllowSimple, lAlphanumReq, lPwEnable, lMinComplex, lPwLen)
            // default on my machine is (1, 2, 1, 1, 4)
            case ID_CONFIGUREPOLICY_SETPASSWORDPOLICYVARIANT1:
            {
                ImhPolicyPtr pPolicy;
                HRESULT hr = pPolicy.CreateInstance(CLSID_mhPolicy, nullptr, CLSCTX_LOCAL_SERVER);
                if (SUCCEEDED(hr))
                    hr = pPolicy->SetPasswordPolicy(1, 2, 1, 1, 4); // default
                if (FAILED(hr))
                    MessageBox(hWnd, L"Error modifying policy", L"Error", MB_OK);
            }
            break;
            case ID_CONFIGUREPOLICY_SETPASSWORDPOLICYVARIANT2:
            {
                ImhPolicyPtr pPolicy;
                HRESULT hr = pPolicy.CreateInstance(CLSID_mhPolicy, nullptr, CLSCTX_LOCAL_SERVER);
                if (SUCCEEDED(hr))
                    hr = pPolicy->SetPasswordPolicy(1, 2, 0, 1, 6); //
//                hr = pPolicy->SetPasswordPolicy(1, 0, 0, 2, 9); // allow simple, pwd or alphanum PIN, digits and lowercase letters, length 9
//                hr = pPolicy->SetPasswordPolicy(0, 0, 0, 2, 9); // pwd or alphanum PIN, digits and lowercase letters, length 9
                if (FAILED(hr))
                    MessageBox(hWnd, L"Error modifying policy", L"Error", MB_OK);
            }
            break;
            case ID_CONFIGUREPOLICY_SETPASSWORDPOLICYVARIANT3:
            {
                ImhPolicyPtr pPolicy;
                HRESULT hr = pPolicy.CreateInstance(CLSID_mhPolicy, nullptr, CLSCTX_LOCAL_SERVER);
                if (SUCCEEDED(hr))
                    hr = pPolicy->SetPasswordPolicy(1, 1, 0, 1, 7); // allow simple, pwd or num PIN, digits only, length 7
                if (FAILED(hr))
                    MessageBox(hWnd, L"Error modifying policy", L"Error", MB_OK);
            }
            break;
            case IDM_LIST:
                {
                ImhComputerInfoPtr pInfo;
                HRESULT hr = pInfo.CreateInstance(CLSID_mhComputerInfo, nullptr, CLSCTX_LOCAL_SERVER);
                if (FAILED(hr))
                {
                    MessageBox(hWnd, L"Error contacting service for collecting computer info", L"Error", MB_OK);
                }
                else
                {
                    _bstr_t bstr;
                    hr = pInfo->GetInfo(bstr.GetAddress());
                    if (FAILED(hr))
                    {
                        MessageBox(hWnd, L"GetInfo failed", L"Error", MB_OK);
                    }
                    else
                    {
                        MessageBox(hWnd, static_cast<LPCWSTR>(bstr), L"Computer Info", MB_OK);
                    }
                }
                }
                break;
            case IDM_REBOOT:
                if (IDOK == MessageBox(hWnd, L"Reboot computer. Are you sure?", L"Reboot", MB_OKCANCEL | MB_ICONWARNING | MB_DEFBUTTON2))
                {
                    ImhRebootPtr pReboot;
                    HRESULT hr = pReboot.CreateInstance(CLSID_mhReboot, nullptr, CLSCTX_LOCAL_SERVER);
                    if (FAILED(hr))
                    {
                        MessageBox(hWnd, L"Error contacting service for reboot", L"Error", MB_OK);
                    }
                    else
                    {
                        hr = pReboot->DoReboot();
                        if (FAILED(hr))
                        {
                            MessageBox(hWnd, L"Reboot failed", L"Error", MB_OK);
                        }
                    }
                }
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WMAPP_NOTIFYCALLBACK:
        switch (LOWORD(lParam))
        {
        case NIN_BALLOONTIMEOUT:
            RestoreTooltip();
            break;
        case NIN_BALLOONUSERCLICK:
            RestoreTooltip();
            break;
        case WM_CONTEXTMENU:
        {
            POINT const pt = { LOWORD(wParam), HIWORD(wParam) };
            g_theSysTrayApp.ShowContextMenu(hWnd, pt);
        }
        break;
        }
        break;
    case WM_DESTROY:
        DeleteNotificationIcon();
        ::CoUninitialize();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


BOOL CSysTrayApp::RestoreTooltip()
{
    // After the balloon is dismissed, restore the tooltip.
    NOTIFYICONDATA nid = { sizeof(nid) };
    nid.uFlags = NIF_SHOWTIP | NIF_GUID;
    nid.guidItem = __uuidof(SystrayIcon);
    return Shell_NotifyIcon(NIM_MODIFY, &nid);
}


void CSysTrayApp::ShowContextMenu(HWND hwnd, POINT pt)
{
    HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDC_MH2104SYSTRAY));
    if (hMenu)
    {
        HMENU hSubMenu = GetSubMenu(hMenu, 0);
        if (hSubMenu)
        {
            // our window must be foreground before calling TrackPopupMenu or the menu will not disappear when the user clicks away
            SetForegroundWindow(hwnd);

            // respect menu drop alignment
            UINT uFlags = TPM_RIGHTBUTTON;
            if (GetSystemMetrics(SM_MENUDROPALIGNMENT) != 0)
                uFlags |= TPM_RIGHTALIGN;
            else
                uFlags |= TPM_LEFTALIGN;

            TrackPopupMenuEx(hSubMenu, uFlags, pt.x, pt.y, hwnd, NULL);
        }
        DestroyMenu(hMenu);
    }
}


// Message handler for about box.
INT_PTR CALLBACK CSysTrayApp::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


BOOL CSysTrayApp::AddNotificationIcon(HWND hwnd)
{
    NOTIFYICONDATA nid = { sizeof(nid) };
    nid.hWnd = hwnd;
    // add the icon, setting the icon, tooltip, and callback message.
    // the icon will be identified with the GUID
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP | NIF_GUID;
    nid.guidItem = __uuidof(SystrayIcon);
    nid.uCallbackMessage = WMAPP_NOTIFYCALLBACK;
    LoadIconMetric(hInst, MAKEINTRESOURCE(IDI_MH2104SYSTRAY), LIM_SMALL, &nid.hIcon);
    LoadString(hInst, IDS_APP_TITLE, nid.szTip, ARRAYSIZE(nid.szTip));
    Shell_NotifyIcon(NIM_ADD, &nid);

    // NOTIFYICON_VERSION_4 is prefered
    nid.uVersion = NOTIFYICON_VERSION_4;
    return Shell_NotifyIcon(NIM_SETVERSION, &nid);
}


BOOL CSysTrayApp::DeleteNotificationIcon()
{
    NOTIFYICONDATA nid = { sizeof(nid) };
    nid.uFlags = NIF_GUID;
    nid.guidItem = __uuidof(SystrayIcon);
    return Shell_NotifyIcon(NIM_DELETE, &nid);
}


// our global instance
CSysTrayApp g_theSysTrayApp;
