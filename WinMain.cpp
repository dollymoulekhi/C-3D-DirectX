#include <Windows.h>

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

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
