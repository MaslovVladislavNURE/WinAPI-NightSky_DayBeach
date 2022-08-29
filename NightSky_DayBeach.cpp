// MyExam.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "NightSky_DayBeach.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_NIGHTSKYDAYBEACH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_NIGHTSKYDAYBEACH));

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

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NIGHTSKYDAYBEACH));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

bool Night = true;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Parse the menu selections:
        switch (wmId)
        {
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HPEN InvisiblePen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
        MoveToEx(hdc, 0, ps.rcPaint.bottom / 2, (LPPOINT)NULL);
        LineTo(hdc, ps.rcPaint.right, ps.rcPaint.bottom / 2);
        HBRUSH blue = CreateSolidBrush(RGB(100, 100, 255));
        SelectObject(hdc, blue);
        Rectangle(hdc, ps.rcPaint.left, ps.rcPaint.bottom / 2, ps.rcPaint.right, ps.rcPaint.bottom);
        HBRUSH yellow = CreateSolidBrush(RGB(255, 255, 100));
        SelectObject(hdc, yellow);
        Ellipse(hdc, ps.rcPaint.right / 4, ps.rcPaint.bottom / 2, ps.rcPaint.right + 1000, 1500);

        if (Night)
        {
            HBRUSH darkblue = CreateSolidBrush(RGB(0, 0, 139));
            SelectObject(hdc, darkblue);
            Rectangle(hdc, ps.rcPaint.left, 0, ps.rcPaint.right, ps.rcPaint.bottom / 2);
            HBRUSH Moon = CreateSolidBrush(RGB(255, 255, 175));
            SelectObject(hdc, Moon);
            Ellipse(hdc, ps.rcPaint.left + 25, ps.rcPaint.top + 25, ps.rcPaint.left + 125, ps.rcPaint.top + 125);
            SelectObject(hdc, InvisiblePen);
            SelectObject(hdc, darkblue);
            Ellipse(hdc, ps.rcPaint.left + 60, ps.rcPaint.top + 25, ps.rcPaint.left + 200, ps.rcPaint.top + 125);

        }
        else
        {
            HPEN SunPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 0));
            HBRUSH Sun = CreateSolidBrush(RGB(255, 255, 0));
            SelectObject(hdc, Sun);
            SelectObject(hdc, SunPen);
            Ellipse(hdc, -100, -100, 200, 200);
            MoveToEx(hdc, 150, 150, (LPPOINT)NULL);
            LineTo(hdc, 230, 230);
            MoveToEx(hdc, 150, 80, (LPPOINT)NULL);
            LineTo(hdc, 260, 135);
            MoveToEx(hdc, 150, 50, (LPPOINT)NULL);
            LineTo(hdc, 300, 70);
        }
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        if ((LOWORD(lParam) < 200) && (HIWORD(lParam) < 200))
        {
            Night = !Night;
            InvalidateRect(hWnd, NULL, true);
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
