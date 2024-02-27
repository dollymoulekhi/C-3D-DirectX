#include <Windows.h>
#include <sstream>

// Forward declaration of the window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int CALLBACK WinMain(
    _In_ HINSTANCE hInstance,
    _In_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow)
{
    const auto pClassName = L"hw3dbutts"; // prepend L to make it wide-character string

    // register windows class
    WNDCLASSEXW wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc; // Using custom window procedure
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = pClassName;
    wc.hIconSm = nullptr;
    RegisterClassExW(&wc);

    HWND hwnd = CreateWindowExW(
        0,
        pClassName,
        L"Happy Hard Window",
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        200, 200, 640, 480,
        nullptr, nullptr, hInstance, nullptr);

    if (hwnd == nullptr)
    {
        // Handle window creation failure
        MessageBox(nullptr, L"Window creation failed!", L"Error", MB_OK | MB_ICONERROR);
        return -1;
    }

    // Show the window
    ShowWindow(hwnd, SW_SHOW);

    // Message pump 
    MSG msg;
    BOOL gResult;

    while ((gResult=GetMessage(&msg, nullptr, 0, 0)) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (gResult == -1)

    {
        return -1;
    }


    else {
        return msg.wParam;
    }
}

// Custom window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(69);
        // DestroyWindow(hwnd);
        break;

    case WM_KEYDOWN:
        if (wParam == 'W')
        {
            SetWindowText(hwnd, L"Forward Movement");
        }


        else if (wParam == 'S')
        {
            SetWindowText(hwnd, L"Backward Movement");
        }
        
        else if (wParam == 'A')
        {
            SetWindowText(hwnd, L"Left movement");
        }
         
        else if (wParam == 'D')
        {
            SetWindowText(hwnd, L"Right movement");
        }
        break;



    //case WM_CHAR:
    //{
    //    static std::string title;
    //    title.push_back(static_cast<char>(wParam));
    //    SetWindowText(hwnd, title.c_str());
    //}
    //break;


    case WM_CHAR:
    {
        static std::wstring title; // Use wstring for wide-character strings
        title.push_back(static_cast<wchar_t>(wParam)); // Push a wide-character
        SetWindowTextW(hwnd, title.c_str()); // Use SetWindowTextW for wide-character strings
    }
    break;



    //case WM_CHAR:
    //{
    //    static std::string title;
    //    title.push_back((char)wParam ;
    //    SetWindowText(hwnd, title.c_str());
    //}

    //break;


    case WM_LBUTTONDOWN:
    {
        POINTS pt = MAKEPOINTS(lParam);
        std::ostringstream oss;
        oss << '(' << pt.x << ',' << pt.y << ')';
        std::string narrowStr = oss.str(); // Convert to narrow-character string
        int length = MultiByteToWideChar(CP_UTF8, 0, narrowStr.c_str(), -1, NULL, 0);
        wchar_t* wideStr = new wchar_t[length];
        MultiByteToWideChar(CP_UTF8, 0, narrowStr.c_str(), -1, wideStr, length);

        SetWindowTextW(hwnd, wideStr);
    }
    break;


    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
