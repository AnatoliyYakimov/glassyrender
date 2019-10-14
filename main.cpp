
#include <windows.h>
#include <vector>
#include <iostream>

#include "Constants.h"
#include "Scene3D/scene3d.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

ATOM register_window(HINSTANCE hInstance, LPCSTR className, WNDPROC wndProc);

HWND create_window(HINSTANCE hInstance, LPCSTR className, LPCSTR windowName);

void draw_scene(HWND pHwnd, int, int);

LPCSTR CLASS_NAME = "MineWindow";
LPCSTR WINDOW_NAME = "Glassy Render";
static scene3d scene = scene3d(WIDTH, HEIGHT, 1.4); // NOLINT(cert-err58-cpp)

HDC dc, memDC;
HBITMAP memBitmap;
PAINTSTRUCT ps;
HANDLE hOld;
RECT *rect;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    if (!register_window(hInstance, CLASS_NAME, &WndProc)) {
        return 1;
    }
    HWND hWnd = create_window(hInstance, CLASS_NAME, WINDOW_NAME);
    auto spheres = std::vector<sphere>();
    spheres.push_back({0.8,
                       point3f{-1, 0, 5},
                       color{200, 200, 20}});
    spheres.push_back({0.6,
                       point3f{1, 0, 5},
                       color{50, 10, 255}});
    spheres.push_back({6,
                       point3f{0, -7, 8},
                       color{10, 200, 255}});
    scene.model.setSpheres(spheres);

    auto lights = ARRAY_LIST<i_light_source *>();
    lights.push_back(new ambient_light_source{0.3f});
    lights.push_back(new point_light_source{1, point3f{0, 2, 5}});
    lights.push_back(new vector_light_source{0.0f, vec3f{0, 0, 100}});
    scene.model.setLights(lights);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            dc = GetDC(hWnd);
            GetWindowRect(hWnd, rect);
            BitBlt(dc, 0, 0, rect->right, rect->bottom, memDC, 0, 0, SRCCOPY);
            ReleaseDC(hWnd, dc);
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        case WM_SIZE: {
            auto H = HIWORD(lParam);
            auto W = LOWORD(lParam);
            scene.viewport.recompute_size(H, W);
            draw_scene(hWnd, H, W);
            delete rect;
            rect = new tagRECT{0, 0, H, W};
            InvalidateRect(hWnd, rect, true);
            break;
        }
        case WM_SIZING: {

        }
        case WM_ERASEBKGND:
            return (LRESULT) 1; // Say we handled it.
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return 0;
}

void draw_scene(HWND hWnd, int H, int W) {
    SelectObject(memDC, hOld);
    DeleteObject(memBitmap);
    DeleteDC(memDC);

    dc = GetDC(hWnd);
    memDC = CreateCompatibleDC(dc);
    memBitmap = CreateCompatibleBitmap(dc, W, H);
    hOld = SelectObject(memDC, memBitmap);
    scene.render_scene(memDC);
    ReleaseDC(hWnd, dc);
}

ATOM register_window(HINSTANCE hInstance, LPCSTR className, WNDPROC wndProc) {
    WNDCLASS wc;
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = className;
    return RegisterClass(&wc);
}

HWND create_window(HINSTANCE hInstance, LPCSTR className, LPCSTR windowName) {
    return CreateWindow(
            className, // имя класса
            windowName, // имя окна (то что сверху)
            WS_OVERLAPPEDWINDOW, // режимы отображения окошка
            X_POS, // положение окна по оси х (по умолчанию)
            Y_POS, // позиция окна по оси у (раз дефолт в х, то писать не нужно)
            WIDTH, // ширина окошка (по умолчанию)
            HEIGHT, // высота окна (раз дефолт в ширине, то писать не нужно)
            nullptr, // дескриптор родительского окошка (у нас нет род. окон)
            nullptr, // дескриптор меню (у нас его нет)
            hInstance, // .... экземпляра приложения
            nullptr); // ничего не передаём из WndProc
}