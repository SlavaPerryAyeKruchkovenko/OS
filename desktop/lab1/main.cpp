#include <windows.h> HINSTANCE hInst;

const char g_szClassName[] = "bonafideideasWindowClass";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MSG Msg;
    HWND hwnd;
    WNDCLASSEX wc;
    wc.lpszMenuName = NULL;
    wc.hInstance = hInstance;
    wc.lpszClassName = g_szClassName;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.cbClsExtra = wc.cbWndExtra = 0;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wc.lpfnWndProc = [](HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT {
        HDC hdc;
        RECT rect;
        TEXTMETRIC tm;
        PAINTSTRUCT ps;
        switch (msg) {
            case WM_CLOSE:
                if (MessageBox(NULL, "Are you sure you want to quit?", "Confirmation", MB_ICONQUESTION | MB_YESNO) ==
                    IDYES)
                    DestroyWindow(hwnd);
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            case WM_PAINT:
                hdc = BeginPaint(hwnd, &ps);
                GetClientRect(hwnd, &rect);
                DrawText(hdc, TEXT ("Native Windows Development with CygWin and CLion."), -1, &rect,
                         DT_SINGLELINE | DT_CENTER | DT_VCENTER);
                EndPaint(hwnd, &ps);
                return 0;
            default:
                return DefWindowProc(hwnd, msg, wParam, lParam);
        }
        return 0;
    };
    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, g_szClassName, "Simplest Windows Native App built with CLion",
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 250, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}


