#include "Window.h"
#include <sstream>

int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nCmdShow)
{
    Window wnd(800, 300, "Window 1");
    Window wnd2(800, 300, "Window 2");
    Window wnd4(800, 300, "Window 3");
    Window wnd5(800, 300, "Window 4");

    MSG msg;
    BOOL gResult;
    while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    if (gResult == -1)
    {
        return -1;
    }

    return msg.wParam;
}


















