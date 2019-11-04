
#include <windows.h>
#include <vector>
#include <iostream>

#include "Constants.h"
#include "include/scene/scene3d.h"
#include "include/entities/algebra/matrix.h"
#include "include/algorithms/brdf.h"


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
    affine_transform R = affine_transform_factory::to_point({0, 0, 0}, {0, 20, 7});
    affine_transform R2 = affine_transform_factory::rotateX(90, point3f{0, 0, 0});
    affine_transform R3 = affine_transform_factory::rotateY(180, point3f{0, 0, 0});
    if (!register_window(hInstance, CLASS_NAME, &WndProc)) {
        return 1;
    }
    HWND hWnd = create_window(hInstance, CLASS_NAME, WINDOW_NAME);

    scene.ambient_light = 0.2f;
    scene.camera_exposure = 0.5;

    auto spheres = std::vector<sphere>();
    material material1({219/255.0f,112/255.0f,147/255.0f}, vec3f{1, 0.97, 0.5}, 0.96);
    material material2({219/255.0f,112/255.0f,147/255.0f}, vec3f(0.97), 0.8);
    material material3({219/255.0f,112/255.0f,147/255.0f}, vec3f(0.97), 0.7);
    material material4({219/255.0f,112/255.0f,147/255.0f}, vec3f(0.97), 0.6);
    material material5({219/255.0f,112/255.0f,147/255.0f}, vec3f(0.97), 0.5);
    material material6({219/255.0f,112/255.0f,147/255.0f}, vec3f(0.97), 0.4);
    material material7({219/255.0f,112/255.0f,147/255.0f}, vec3f(0.97), 0.3);
    material material8({219/255.0f,112/255.0f,147/255.0f}, vec3f(0.97), 0.2);
    material material9({219/255.0f,112/255.0f,147/255.0f}, vec3f(0.97), 0.1);

    spheres.push_back({
                              1.4,
                              {-15, 0, 0},
                              material1
                      });
    spheres.push_back({
                              1.4,
                              {-12, 0, 0},
                              material2
                      });
    spheres.push_back({
                              1.4,
                              {-9, 0, 0},
                              material3
                      });
    spheres.push_back({
                              1.4,
                              {-6, 0, 0},
                              material4
                      });
    spheres.push_back({
                              1.4,
                              {-3, 0, 0},
                              material5
                      });
    spheres.push_back({
                              1.4,
                              {0, 0, 0},
                              material6
                      });
    spheres.push_back({
                              1.4,
                              {3, 0, 0},
                              material7
                      });
    spheres.push_back({
                              1.4,
                              {6, 0, 0},
                              material8
                      });
    spheres.push_back({
                              1.4,
                              {9, 0, 0},
                              material9
                      });
    scene.model.spheres = spheres;

    auto lights = ARRAY_LIST<i_light_source *>();
//    lights.push_back(new point_light_source{6, {1, 1, 1}, {0, 2, 5}});
//    lights.push_back(new point_light_source{7, {1, 1, 1}, {-2, 5, 1}});
    lights.push_back(new point_light_source{5, {1, 1, 1}, {-3, 10, -40}});
//    lights.push_back(new vector_light_source{0.4f, {5, -1, 0.03}});
    scene.model.lights = lights;
    affine_transform at = {
            1, 0, 0, -3,
            0, 1, 0, -5,
            0, 0, 1, -40,
            0, 0, 0, 1
    };
    scene.viewport.apply(at);
//    scene.viewport.apply(R3);
//    scene.viewport.apply(R2);
//    scene.viewport.apply(R);
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
            scene.recompute_size(H, W);
            draw_scene(hWnd, H, W);
            delete rect;
            rect = new tagRECT{0, 0, H, W};
            InvalidateRect(hWnd, rect, true);
            break;
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
    scene.draw_scene(memDC);
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