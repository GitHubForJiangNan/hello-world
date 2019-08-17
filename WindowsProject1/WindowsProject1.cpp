// WindowsProject1.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

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

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR szInput[] =
		TEXT("输入（文件路径）：");
	static TCHAR szResult[] = 
		TEXT("结果：");
	static HWND hwndButton = NULL;
	static HWND hwndEdit = NULL;
	static HWND hwndInput = NULL;
	static HBRUSH hBrush;
	static HFONT hFont;
	RECT rect;
	PAINTSTRUCT ps;
	HDC hdc;
	TEXTMETRIC tm;
	static int cxChar, cyChar;    //系统字体的平均宽度、高度

    switch (message)
    {

	case WM_CREATE:
		hdc = GetDC(hWnd);                //获取设备环境句柄
		GetTextMetrics(hdc, &tm);         //获取系统字体信息
		ReleaseDC(hWnd, hdc);             //设备环境句柄使用完毕, 释放

		cxChar = tm.tmAveCharWidth;                     //得到字体平均宽度
		cyChar = tm.tmHeight + tm.tmExternalLeading;    //字体高度, 总高度tmHeight + 两行文字之间的建议间距大小tmExternalLeading



		hwndButton = CreateWindowW(
			TEXT("BUTTON"),
			TEXT("MD5"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			0,0,0,0,
			hWnd, (HMENU)BUTTON_ID, hInst, NULL);

		hwndInput = CreateWindowW(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE ,
			0, 0, 0, 0,
			hWnd, (HMENU)INPUT_ID, hInst, NULL);

		hwndEdit = CreateWindowW(TEXT("edit"), NULL,
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_READONLY,
			0, 0, 0, 0,
			hWnd, (HMENU)EDIT_ID, hInst, NULL);


		hBrush = CreateSolidBrush(RGB(0x41, 0x96, 0x4F));

		hFont = CreateFont(-20/*高*/, -10/*宽*/, 0, 0, 100 /*700表示粗体*/,
			FALSE/*斜体?*/, FALSE/*下划线?*/, FALSE/*删除线?*/, DEFAULT_CHARSET,
			OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
			FF_DONTCARE, TEXT("宋体")
		);
		SendMessage(hwndEdit, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hwndInput, WM_SETFONT, (WPARAM)hFont, NULL);
		break;

	case WM_SETFOCUS:
		SetFocus(hwndInput);
		return 0;

	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		MoveWindow(hwndButton, rect.right / 2 - 40, rect.bottom - 60, 80, 40, TRUE);
		MoveWindow(hwndInput, 10,30, rect.right - 20, rect.bottom / 2 - 20 - 20, TRUE);
		MoveWindow(hwndEdit, 10, rect.bottom / 2 + 20, rect.right - 20, rect.bottom / 2 - 20 - 80 , TRUE);
		break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
			case BUTTON_ID:
				
				break;

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
			GetClientRect(hWnd, &rect);
            hdc = BeginPaint(hWnd, &ps);
			SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
			TextOut(hdc, 10, 10, szInput, lstrlen(szInput));
			TextOut(hdc, 10, rect.bottom / 2, szResult, lstrlen(szResult));
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


