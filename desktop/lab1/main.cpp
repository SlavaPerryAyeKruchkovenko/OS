#include <windows.h>
#include <conio.h>


typedef struct ButtonData {
    HBRUSH hBrush;
    HPEN hPen;
    bool isClick;
    int x;
    int y;
} ButtonData;

POINT point;

HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK BtnWndProc(HWND, UINT, WPARAM, LPARAM);

void RegisterWindow(HINSTANCE hInstance);

void RegisterBtn(HINSTANCE hInstance);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    GetCursorPos(&point);
    MSG msg;
    HWND hWnd;

    RegisterWindow(hInstance);
    RegisterBtn(hInstance);

    hWnd = CreateWindow(TEXT("Window"), TEXT("Hello world"), WS_ACTIVECAPTION | WS_SYSMENU | WS_TILED,
                        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

void RegisterWindow(HINSTANCE hInstance) {
    WNDCLASSEX wndclassex;
    wndclassex.cbSize = sizeof(WNDCLASSEX);
    wndclassex.style = CS_HREDRAW | CS_VREDRAW;
    wndclassex.lpfnWndProc = WndProc;
    wndclassex.cbClsExtra = 0;
    wndclassex.cbWndExtra = 0;
    wndclassex.hInstance = hInstance;
    wndclassex.hIcon = LoadIcon(hInstance, IDI_WINLOGO);
    wndclassex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndclassex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wndclassex.lpszMenuName = nullptr;
    wndclassex.lpszClassName = TEXT("Window");
    wndclassex.hIconSm = nullptr;

    RegisterClassEx(&wndclassex);
}

void RegisterBtn(HINSTANCE hInstance) {
    WNDCLASSEX wndclassex;
    wndclassex.cbSize = sizeof(WNDCLASSEX);
    wndclassex.style = 0;
    wndclassex.lpfnWndProc = BtnWndProc;
    wndclassex.cbClsExtra = 0;
    wndclassex.cbWndExtra = 0;
    wndclassex.hInstance = hInstance;
    wndclassex.hIcon = nullptr;
    wndclassex.hCursor = nullptr;
    wndclassex.hbrBackground = nullptr;
    wndclassex.lpszMenuName = nullptr;
    wndclassex.lpszClassName = TEXT("GameButton");
    wndclassex.hIconSm = nullptr;

    RegisterClassEx(&wndclassex);
}

LRESULT
CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    HWND hWndBtn;
    RECT Rect;
    int width = 200;
    int height = 200;

    switch (message) {
        case WM_CREATE:
            GetClientRect(hWnd, &Rect);

            hWndBtn = CreateWindow(TEXT("GameButton"), TEXT("SLAVA UKRAINE!"), WS_CHILD | WS_VISIBLE | WS_BORDER,
                                   (Rect.right - Rect.left) / 2 - width / 2,
                                   (Rect.bottom - Rect.top) / 2 - height / 2,
                                   width, height,
                                   hWnd,
                                   nullptr,
                                   hInst,
                                   nullptr);
            InvalidateRect(hWndBtn, nullptr, TRUE);
            break;
        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case 228:
                    MessageBox(hWnd,
                               TEXT("Евреи-хипстеры не делают обрезание. Они подворачивают."),
                               TEXT("Шутка!"),
                               MB_OK);
                    break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return
                    DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


LRESULT CALLBACK BtnWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rect;
    ButtonData *lpData;
    switch (message) {
        case WM_CREATE:
            lpData = (ButtonData *) malloc(sizeof(ButtonData));
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(lpData));
            lpData->hBrush = CreateSolidBrush(RGB(255, 255, 0));
            lpData->hPen = CreatePen(PS_DOT, 2, RGB(0, 0, 255));
            lpData->isClick = false;
            lpData->x = 0;
            lpData->y = 0;
            break;
        case WM_PAINT:
            lpData = (ButtonData *) GetWindowLongPtr(hWnd, GWLP_USERDATA);
            hdc = BeginPaint(hWnd, &ps);
            GetClientRect(hWnd, &rect);
            SelectObject(hdc, lpData->hBrush);
            SelectObject(hdc, lpData->hPen);
            FillRect(hdc, &rect, lpData->hBrush);
            MoveToEx(hdc, rect.left, rect.bottom / 4, nullptr);
            LineTo(hdc, rect.right, rect.bottom / 4);
            LineTo(hdc, rect.right / 2, rect.bottom);
            LineTo(hdc, rect.left, rect.bottom / 4);
            MoveToEx(hdc, (rect.right - rect.left) / 2, rect.top, nullptr);
            LineTo(hdc, rect.right, rect.bottom * 3 / 4);
            LineTo(hdc, rect.left, rect.bottom * 3 / 4);
            LineTo(hdc, (rect.right - rect.left) / 2, rect.top);
            EndPaint(hWnd, &ps);

            break;
        case WM_LBUTTONDOWN:
            lpData = (ButtonData *) GetWindowLongPtr(hWnd, GWLP_USERDATA);
            DeleteObject(lpData->hBrush);
            if (lpData->isClick)
                lpData->hBrush = CreateSolidBrush(RGB(255, 255, 0));
            else
                lpData->hBrush = CreateSolidBrush(RGB(255, 0, 0));
            DeleteObject(lpData->hPen);
            if (lpData->isClick)
                lpData->hPen = CreatePen(PS_DOT, 2, RGB(0, 0, 255));
            else
                lpData->hPen = CreatePen(PS_DOT, 2, RGB(0, 0, 0));
            lpData->x = 0;
            lpData->y = 0;
            MoveWindow(hWnd, lpData->x, lpData->y, 200, 200, TRUE);
            InvalidateRect(hWnd, nullptr, TRUE);
            break;
        case WM_LBUTTONUP:
            lpData = (ButtonData *) GetWindowLongPtr(hWnd, GWLP_USERDATA);
            lpData->isClick = !lpData->isClick;
            SendMessage(GetParent(hWnd), WM_COMMAND, MAKELONG(228, 0), 0);
            break;
        case WM_MOUSEMOVE:
            POINT p;
            GetCursorPos(&p);
            lpData = (ButtonData *) GetWindowLongPtr(hWnd, GWLP_USERDATA);
            if (p.x < point.x)
                lpData->x = lpData->x + 1;
            else
                lpData->x = lpData->x - 1;
            if (p.y < point.y)
                lpData->y = lpData->y - 1;
            else
                lpData->y = lpData->y + 1;
            if (lpData->y % 2 == 0)
                MoveWindow(hWnd, lpData->x, lpData->y, 200, 200, TRUE);
            point = p;

            break;
        case WM_DESTROY:
            lpData = (ButtonData *) GetWindowLongPtr(hWnd, GWLP_USERDATA);
            DeleteObject(lpData->hBrush);
            DeleteObject(lpData->hPen);
            free(lpData);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

