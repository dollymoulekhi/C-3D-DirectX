#include "Window.h"
#include <sstream>

Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept :
    hInst(GetModuleHandle(nullptr))
{
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(wc);
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = HandleMsgSetup;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetInstance();
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = static_cast<LPCSTR>(GetName());

    //c.lpszClassName = GetName();
    wc.hIconSm = nullptr;
    RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
    UnregisterClass(wndClassName, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept
{
    return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
    return wndClass.hInst;
}

Window::Window(int width, int height, const char* name) noexcept :
    width(width), height(height)
{
    RECT wr;
    wr.left = 100;
    wr.right = width + wr.left;
    wr.top = 100;
    wr.bottom = height + wr.top;
    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
    hWnd = CreateWindow(
        WindowClass::GetName(), name,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
        nullptr, nullptr, WindowClass::GetInstance(), this
    );

    ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
    DestroyWindow(hWnd);
}

LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
































//
//
//
//
//
//#include "Window.h"
//#include <sstream>
//
//Window::WindowClass Window::WindowClass::wndClass;
//
//Window::WindowClass::WindowClass() noexcept :
//    hInst(GetModuleHandle(nullptr))
//{
//    WNDCLASSEX wc = { 0 };
//    wc.cbSize = sizeof(wc);
//    wc.style = CS_OWNDC;
//    wc.lpfnWndProc = HandleMsgSetup;
//    wc.cbClsExtra = 0;
//    wc.cbWndExtra = 0;
//    wc.hInstance = GetInstance();
//    wc.hIcon = nullptr;
//    wc.hCursor = nullptr;
//    wc.hbrBackground = nullptr;
//    wc.lpszMenuName = nullptr;
//    wc.lpszClassName = GetName();
//    wc.hIconSm = nullptr;
//    RegisterClassEx(&wc);
//}
////
////Window::WindowClass::~WindowClass()
////{
////    UnregisterClass(wndClassName, GetInstance());
////}
//
//
//Window::WindowClass::~WindowClass()
//{
//    UnregisterClass(Window::WindowClass::wndClassName, GetInstance());
//}
//
//
//const char* Window::WindowClass::GetInstance() noexcept
//{
//    return wndClassName;
//}
//
//const wchar_t* Window::WindowClass::GetName() noexcept
//
//{
//    static wchar_t wideName[256];
//    // Convert narrow-character string to wide-character string
//    mbstowcs(wideName, wndClassName, sizeof(wideName) / sizeof(wideName[0]));
//    return wideName;
//}
//
//
//
//HINSTANCE Window::WindowClass::GetInstance() noexcept
//{
//    return wndClass.hInst;
//}
//
//Window::Window(int width, int height, const char* name) noexcept
//{
//    // Convert narrow-character string to wide-character string
//    std::wstring wideName = std::wstring(name, name + strlen(name));
//
//    RECT wr;
//    wr.left = 100;
//    wr.right = width + wr.left;
//    wr.top = 100;
//    wr.bottom = height + wr.top;
//    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
//    hWnd = CreateWindow(
//        WindowClass::GetName(),                 // LPCWSTR lpClassName
//        wideName.c_str(),                      // LPCWSTR lpWindowName
//        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
//        CW_USEDEFAULT, CW_USEDEFAULT,
//        wr.right - wr.left, wr.bottom - wr.top,
//        nullptr, nullptr, WindowClass::GetInstance(), this
//    );
//
//    ShowWindow(hWnd, SW_SHOWDEFAULT);
//}
//
//Window::~Window()
//{
//    DestroyWindow(hWnd);
//}
//
//LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
//{
//    if (msg == WM_NCCREATE)
//    {
//        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
//        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
//        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
//        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
//        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
//    }
//
//    return DefWindowProc(hWnd, msg, wParam, lParam);
//}
//
//LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
//{
//    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
//    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
//}
//
//LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
//{
//    switch (msg)
//    {
//    case WM_CLOSE:
//        PostQuitMessage(0);
//        return 0;
//    }
//
//    return DefWindowProc(hWnd, msg, wParam, lParam);
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//


















































//
//
//
//#include "Window.h"
//#include <sstream>
//
//Window::WindowClass Window::WindowClass::wndClass;
//
//Window::WindowClass::WindowClass() noexcept :
//    hInst(GetModuleHandle(nullptr))
//{
//    WNDCLASSEX wc = { 0 };
//    wc.cbSize = sizeof(wc);
//    wc.style = CS_OWNDC;
//    wc.lpfnWndProc = HandleMsgSetup;
//    wc.cbClsExtra = 0;
//    wc.cbWndExtra = 0;
//    wc.hInstance = GetInstance();
//    wc.hIcon = nullptr;
//    wc.hCursor = nullptr;
//    wc.hbrBackground = nullptr;
//    wc.lpszMenuName = nullptr;
//    wc.lpszClassName = GetName();
//    wc.hIconSm = nullptr;
//    RegisterClassEx(&wc);
//}
//
//Window::WindowClass::~WindowClass()
//{
//    UnregisterClass(wndClassName, GetInstance());
//}
//
//const char* Window::WindowClass::GetName() noexcept
//{
//    return wndClassName;
//}
//
//HINSTANCE Window::WindowClass::GetInstance() noexcept
//{
//    return wndClass.hInst;
//}
//
//Window::Window(int width, int height, const char* name) noexcept
//{
//    // Convert narrow-character string to wide-character string
//    std::wstring wideName = std::wstring(name, name + strlen(name));
//
//    RECT wr;
//    wr.left = 100;
//    wr.right = width + wr.left;
//    wr.top = 100;
//    wr.bottom = height + wr.top;
//    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
//    hWnd = CreateWindow(
//        WindowClass::GetName(),                 // LPCWSTR lpClassName
//        wideName.c_str(),                      // LPCWSTR lpWindowName
//        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
//        CW_USEDEFAULT, CW_USEDEFAULT,
//        wr.right - wr.left, wr.bottom - wr.top,
//        nullptr, nullptr, WindowClass::GetInstance(), this
//    );
//
//    ShowWindow(hWnd, SW_SHOWDEFAULT);
//}
//
//Window::~Window()
//{
//    DestroyWindow(hWnd);
//}
//
//LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
//{
//    if (msg == WM_NCCREATE)
//    {
//        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
//        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
//        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
//        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
//        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
//    }
//
//    return DefWindowProc(hWnd, msg, wParam, lParam);
//}
//
//LRESULT CALLBACK Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
//{
//    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
//    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
//}
//
//LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
//{
//    switch (msg)
//    {
//    case WM_CLOSE:
//        PostQuitMessage(0);
//        return 0;
//    }
//
//    return DefWindowProc(hWnd, msg, wParam, lParam);
//}
//


//
//#include "Window.h"
//#include <sstream>
//
//
//Window::WindowClass Window::WindowClass::wndClass;
//
//Window::WindowClass::WindowClass() noexcept :
//	hInst(GetModuleHandle(nullptr))
//{
//	WNDCLASSEX wc = { 0 };
//	wc.cbSize = sizeof(wc);
//	wc.style = CS_OWNDC;
//	wc.lpfnWndProc = HandleMsgSetup;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hInstance = GetInstance();
//	wc.hIcon = nullptr;
//	wc.hCursor = nullptr;
//	wc.hbrBackground = nullptr;
//	wc.lpszMenuName = nullptr;
//	wc.lpszClassName = GetName();
//	wc.hIconSm = nullptr;
//	RegisterClassEx(&wc);
//}
//
//Window::WindowClass::~WindowClass()
//{
//	UnregisterClass(wndClassName, GetInstance());
//}
//
//const char* Window::WindowClass::GetInstance() noexcept
//{
//	return wndClassName;
//}
//
//
//HINSTANCE Window::WindowClass::GetInstance() noexcept
//{
//	return wndClass.hInst;
//}
//
//
//Window::Window(int width, int height, const char* name) noexcept
//
//{
//	RECT wr;
//	wr.left = 100;
//	wr.right = width + wr.left;
//	wr.top = 100;
//	wr.bottom = heoght + wr.top;
//	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
//	hWnd = CreateWindow(
//		WindowClass::GetName(), name,
//		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
//		CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top,
//		nullptr, nullptr, WindowClass::GetInstance(), this
//	);
//
//	ShowWindow(hWnd, SW_SHOWDEFAULT);
//}
//
//
//Window::~Window()
//{
//	DestroyWindow(hWnd);
//}
//
//
//
//LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
//{
//	if (msg == WM_NCCREATE)
//	{
//		const CREATETRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
//		Window* const pWnd = static_cast<Window*>(pCtare->lpCreateParams);
//		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
//		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(&Window::HandleMshThunk));
//		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
//	}
//
//	return DefFrameProc(hWnd, msg, wParam, lParam);
//}
//
//
//
//LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
//
//{
//	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
//	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
//}
//
//LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
//
//{
//	switch (msg)
//	{
//	CASE WM_CLOSE :
//		PostQuitMessage(0);
//		return 0;
//
//	}
//
//	return DefFrameProc(hWnd, msg, wParam, lParam);
//
//	}
//}
//
//
//
//
//
//
//