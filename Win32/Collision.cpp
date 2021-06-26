// Win32.cpp : ���ø����̼ǿ� ���� �������� �����մϴ�.
//
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "Win32.h"

#include "Circle2D.h"
#include "Star2D.h"
#include "Line2D.h"
#include "Rectangle2D.h"

#include <vector>

#define MAX_LOADSTRING 100


// ���� ����:
HINSTANCE hInst;                                    // ���� �ν��Ͻ��Դϴ�.
WCHAR     szTitle[MAX_LOADSTRING];            // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
WCHAR     szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.

// �� �ڵ� ��⿡ ���Ե� �Լ��� ������ �����մϴ�:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPWSTR    lpCmdLine,
	_In_     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: ���⿡ �ڵ带 �Է��մϴ�.

	// ���� ���ڿ��� �ʱ�ȭ�մϴ�.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ���ø����̼� �ʱ�ȭ�� �����մϴ�:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32));

	MSG msg;

	// �⺻ �޽��� �����Դϴ�:
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

//
//  �Լ�: MyRegisterClass()
//
//  �뵵: â Ŭ������ ����մϴ�.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   �Լ�: InitInstance(HINSTANCE, int)
//
//   �뵵: �ν��Ͻ� �ڵ��� �����ϰ� �� â�� ����ϴ�.
//
//   �ּ�:
//
//        �� �Լ��� ���� �ν��Ͻ� �ڵ��� ���� ������ �����ϰ�
//        �� ���α׷� â�� ���� ���� ǥ���մϴ�.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

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
//  �Լ�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �뵵: �� â�� �޽����� ó���մϴ�.
//
//  WM_COMMAND  - ���ø����̼� �޴��� ó���մϴ�.
//  WM_PAINT    - �� â�� �׸��ϴ�.
//  WM_DESTROY  - ���� �޽����� �Խ��ϰ� ��ȯ�մϴ�.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static std::vector<Shape2D*> shapes;
	static const int SHAPE_MAX_CNT = 50;
	static int mode;

	static RECT rect;

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �޴� ������ ���� �м��մϴ�:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_CREATE:
	{
		// ������ â ũ�� ����
		GetClientRect(hWnd, &rect);

		// ������Ʈ ��ġ ������ ���� Ÿ�̸�
		SetTimer(hWnd, 1, 16, NULL);

		// ������ ������ ���� Ÿ�̸�
		SetTimer(hWnd, 2, 32, NULL);

		mode = 0;
	}
	break;
	case WM_SIZE:
	{
		// ������ â ũ�� ����
		GetClientRect(hWnd, &rect);

		// ȭ�� ����
		InvalidateRect(hWnd, NULL, true);
	}
	break;
	case WM_TIMER:
	{
		switch (wParam)
		{
			// ������Ʈ��ġ ���� Ÿ�̸�
			case 1:

				// �������� ��ġ ������Ʈ
				for (Shape2D* &shape : shapes)
					shape->Update();

				// ���� - ������ â ��� �浹 üũ
				for (Shape2D* &shape : shapes)
					shape->Collision(rect);

				// ���� - ���� �浹 üũ
				for (int i = 0; i < shapes.size(); ++i)
					for (int j = i + 1; j < shapes.size(); ++j)
						shapes[i]->Collision(shapes[j]);

				// ���� - ���� Overlap
				for (int i = 0; i < shapes.size(); ++i)
					for (int j = 0; j < shapes.size(); ++j)
						if (shapes[i] != shapes[j])
							shapes[i]->Overlap(shapes[j]);

				break;

			// ������ ���� Ÿ�̸�
			case 2:

				// ȭ�� ����
				InvalidateRect(hWnd, NULL, true);
				break;
		}
	}
	break;
	case WM_KEYDOWN:
	{
		// ���� 1, 2, 3
		if (wParam == 0x31)
			mode = 1;
		else if (wParam == 0x32)
			mode = 2;
		else if (wParam == 0x33)
			mode = 3;
	}
	break;
	case WM_LBUTTONDOWN:
	{
		if (shapes.size() < SHAPE_MAX_CNT)
		{
			if (mode == 1)
			{
				Circle2D *newCircle = new Circle2D(LOWORD(lParam), HIWORD(lParam), (double)(50));

				double speed = 11;
				newCircle->SetDir((rand() % (int)speed) - speed / 2, (rand() % (int)speed) - speed / 2);

				shapes.push_back(newCircle);
			}
			else if (mode == 2)
			{
				Rectangle2D *newRec = new Rectangle2D(LOWORD(lParam), HIWORD(lParam), (double)(300));

				double speed = 11;
				newRec->SetDir((rand() % (int)speed) - speed / 2, (rand() % (int)speed) - speed / 2);
				newRec->SetRotationalSpeedDegree((double)(rand() % 2 + 1));

				shapes.push_back(newRec);
			}
			else if (mode == 3)
			{
				Star2D *newStar = new Star2D(LOWORD(lParam), HIWORD(lParam), (double)(rand() % 50 + 10));

				double speed = 11;
				newStar->SetDir((rand() % (int)speed) - speed / 2, (rand() % (int)speed) - speed / 2);
				newStar->SetRotationalSpeedDegree((double)(rand() % 2 - 1));

				shapes.push_back(newStar);
			}
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		// ���� �׸���
		for (Shape2D* &shape : shapes)
			shape->Draw(hdc);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);

		for (Shape2D *shape : shapes)
			delete shape;

		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);

		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// ���� ��ȭ ������ �޽��� ó�����Դϴ�.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}