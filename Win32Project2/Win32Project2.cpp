// Win32Project2.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Win32Project2.h"

#define MAX_LOADSTRING 100
#define ID_10 55555
#define ID_11 55556
#define ID_12 55557

// ȫ�ֱ���: 
HINSTANCE hInst;                                // ��ǰʵ��
WCHAR szTitle[MAX_LOADSTRING];                  // �������ı�
WCHAR szWindowClass[MAX_LOADSTRING];            // ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int GetMax(int n1, int n2, int n3)
{
	return n1 > n2 ? (n1 > n3 ? n1 : (n2 > n3 ? n2 : n3)) : (n2 > n3 ? n2 : (n1 > n3 ? n1 : n3));
}
int GetMin(int n1, int n2, int n3)
{
	return n1 < n2 ? (n1 < n3 ? n1 : (n2 < n3 ? n2 : n3)) : (n2 < n3 ? n2 : (n1 < n3 ? n1 : n3));
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: �ڴ˷��ô��롣

    // ��ʼ��ȫ���ַ���
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32PROJECT2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
	

    // ִ��Ӧ�ó����ʼ��: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT2));

    MSG msg;

    // ����Ϣѭ��: 
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32PROJECT2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND  - ����Ӧ�ó���˵�
//  WM_PAINT    - ����������
//  WM_DESTROY  - �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static POINT pt0,pt1;//�°��ĵ���pt0,tpt����
	static POINT tpt[3];
	static RECT rect,rect1,rect2;
	static int state = -1;//123,crt
	static COLORREF col;//rgb
	static int sx = -1;//12,sx
	static HPEN Pen;
	static int count,count0 = 0;
	static int px = 4;
	
    switch (message)
    {
	case WM_CREATE:
	{
	HMENU hMenu,subMenu;
	hMenu = GetMenu(hWnd);
	subMenu = GetSubMenu(hMenu,1);
	HBITMAP hBitmap1, hBitmap2, hBitmap3;
	hBitmap1 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
	hBitmap2 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP2));
	hBitmap3 = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	AppendMenu(subMenu, MFT_BITMAP, ID_10,(LPCWSTR) hBitmap1);
	AppendMenu(subMenu, MFT_BITMAP, ID_11, (LPCWSTR)hBitmap2);
	AppendMenu(subMenu, MFT_BITMAP, ID_12, (LPCWSTR)hBitmap3);

	}
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // �����˵�ѡ��: 
            switch (wmId)
            {
			case ID_Cir:
				state = 0;
				//pt0.x = 0; pt0.y = 0; pt1.x = 0; pt1.y = 0;
				break;
			case ID_Rect:
				state = 1;
                break;
			case ID_Tri:
				state = 2;
				break;
			case ID_Line:
				state = 3;
				break;
			/*case ID_Red:
				col = RGB(255,0,0);
				break;
			case ID_Green:
				col = RGB(0, 255, 0);
				break;
			case ID_Blue:
				col = RGB(0, 0, 255);
				break;*/
			case ID_10:
				col = RGB(255, 0, 0);
				break;
			case ID_11:
				col = RGB(0, 255, 0);
				break;
			case ID_12:
				col = RGB(0, 0, 255);
				break;
			case ID_SX:
				sx = PS_SOLID;
				break;
			case ID_XX:
				sx = PS_DASH;
				break;
			case ID_CLR:
				state = -2;
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
			//InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			if (sx == PS_DASH)
				px = 1;//����ֻ��1����
			else
				px = 4;
			Pen = CreatePen( sx , px , col);
			SelectObject(hdc, Pen);
			if (state == 0)
			{
				Ellipse(hdc, rect.left - 5, rect.top - 5, rect.right + 5, rect.bottom + 5);
			}else if (state == 1)
			{
				Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
			}else if (state == 2)
			{
				Polygon(hdc, tpt, 3);
			}
			else if (state == 3)
			{
				MoveToEx(hdc,pt1.x,pt1.y,NULL);
				LineTo(hdc, pt0.x, pt0.y);
			}
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
		{
		pt1 = pt0;
		pt0.x = LOWORD(lParam);
		pt0.y = HIWORD(lParam);
		count++;	
		if (count % 2 == 0 && (state == 0 || state == 1 || state == 3))
		{
			rect.left = pt0.x;
			rect.top = pt0.y;
			rect.right = pt1.x;
			rect.bottom = pt1.y;
			InvalidateRect(hWnd, &rect, TRUE);
		}
		if (count % 2 == 0&& state == -2)
		{
			rect1.left = pt0.x;
			rect1.top = pt0.y;
			rect1.right = pt1.x;
			rect1.bottom = pt1.y;
			InvalidateRect(hWnd, &rect1, TRUE);
		}
		if (state == 2)
		{
			tpt[0].x = tpt[1].x;
			tpt[0].y = tpt[1].y;
			tpt[1].x = tpt[2].x;
			tpt[1].y = tpt[2].y;
			tpt[2].x = LOWORD(lParam);
			tpt[2].y = HIWORD(lParam);
			count0++;
			if (count0 % 3 == 0&& count0!=0)
			{
				rect2.bottom = GetMin(tpt[0].y, tpt[1].y, tpt[2].y);
				rect2.left = GetMin(tpt[0].x, tpt[1].x, tpt[2].x);
				rect2.right = GetMax(tpt[0].x, tpt[1].x, tpt[2].x);
				rect2.top = GetMax(tpt[0].y, tpt[1].y, tpt[2].y);
				InvalidateRect(hWnd, &rect2, TRUE);
			}
			pt0.x = 0; pt0.y = 0; pt1.x = 0; pt1.y = 0; count = 0;
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

