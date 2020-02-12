
#include <windows.h>
#include <vector>
#include <iostream>

#include "Constants.h"
#include "include/scene/scene3d.h"
#include "include/utils/obj_file_handler.h"


LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

ATOM register_window(HINSTANCE hInstance, LPCSTR className, WNDPROC wndProc);

HWND create_window(HINSTANCE hInstance, LPCSTR className, LPCSTR windowName);

void draw_scene(HWND pHwnd, int, int);

void initialize_scene(std::vector<i_object *> &spheres);

void initialize_scene2(std::vector<i_object *> &spheres);


void initialize_scene3(vector<i_object *> &scene);

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
//    nanogui::init();
    HWND hWnd = create_window(hInstance, CLASS_NAME, WINDOW_NAME);

    scene.ambient_light = 0.1f;
    scene.camera_exposure = 1.0f;
    scene.gamma = 2.2f;

    auto spheres = std::vector<i_object *>();
    initialize_scene2(spheres);
//    initialize_scene3(spheres);
    scene.model.objects = spheres;

    auto lights = std::vector<i_light_source *>();
    lights.push_back(new vector_light_source{
            2.0f, vec3f{1, 1, 1}, vec3f{5, -5, 5}});
    lights.push_back(new point_light_source{
            10.0f, vec3f{1, 0, 0}, vec3f{1, 1, -1}});
    scene.model.lights = lights;
    affine_transform at = {
            1, 0, 0, 1,
            0, 1, 0, 0.5,
            0, 0, 1, -40,
            0, 0, 0, 1
    };
    scene.viewport.apply(at);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

void initialize_scene3(vector<i_object *> &scene) {
    using namespace std;
//    obj_file_handler obj;
//    std::string path(R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\guitar\Guitar.obj)");
//    scene.emplace(obj.load(path)->begin());
    vector<vec3f> *v = new vector<vec3f>();
    vector<vec3f> *vn = new vector<vec3f>();
    vector<vec2f> *vt = new vector<vec2f>();
    vector<face> *faces = new vector<face>();
    v->emplace_back(
            vec3f{0, 0, 0}
    );
    v->emplace_back(
            vec3f{0, 1, 0}
    );
    v->emplace_back(
            vec3f{1, 1, 0}
    );
    v->emplace_back(
            vec3f{1, 0, 1}
    );
    vt->push_back(
            vec2f{0, 0});
    vt->push_back(
            vec2f{0, 1});
    vt->push_back(
            vec2f{1, 1});
    vt->push_back(
            vec2f{1, 0});
    vn->push_back(
            vec3f{1, 1, 1}.normalized_copy()
    );

    faces->push_back(
            face{
                    vec3i{1, 2, 4},
                    vec3i{1, 2, 4},
                    vec3i{1, 1, 1}
            });
    faces->push_back(
            face{
                    vec3i{3, 2, 4},
                    vec3i{3, 2, 4},
                    vec3i{1, 1, 1}
            });
    std::string path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_col.tga)";
    i_rgb_texture *albedo = new mapped_rgb_texture(path, true, 2.2f);
    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_AO.tga)";
    i_monochrome_texture *ao = new mapped_monochrome_texture(path);

    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_nrm.tga)";
    i_rgb_texture *normal = new mapped_rgb_texture(path);

    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_rgh.tga)";
    i_monochrome_texture *rgh = new mapped_monochrome_texture(path);
    affine_transform at = affine_transform_factory::move(vec3f{0, 0, 0});
    scene.push_back(
            new polygonal_object(
                    albedo,
                    rgh,
                    normal,
                    ao,
                    v,
                    vt,
                    vn,
                    faces)
    );
}

void initialize_scene2(std::vector<i_object *> &spheres) {
    std::string path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_col.tga)";
    i_rgb_texture *albedo = new mapped_rgb_texture(path, true, 2.2f);
    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_AO.tga)";
    i_monochrome_texture *ao = new mapped_monochrome_texture(path);

    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_nrm.tga)";
    i_rgb_texture *normal = new mapped_rgb_texture(path);

    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_rgh.tga)";
    i_monochrome_texture *rgh = new mapped_monochrome_texture(path);
    affine_transform at = affine_transform_factory::move(vec3f{0, 0, 0});

    sphere *s1 = new sphere(12.0f, albedo, rgh, normal, ao);
    s1->apply(at);
    spheres.push_back(s1);
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