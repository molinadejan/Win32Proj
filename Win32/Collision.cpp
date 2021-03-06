// Win32.cpp : 애플리케이션에 대한 진입점을 정의합니다.
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


// 전역 변수:
HINSTANCE hInst;                                    // 현재 인스턴스입니다.
WCHAR     szTitle[MAX_LOADSTRING];            // 제목 표시줄 텍스트입니다.
WCHAR     szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32));

	MSG msg;

	// 기본 메시지 루프입니다:
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
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
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
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

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
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
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
		// 메뉴 선택을 구문 분석합니다:
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
		// 윈도우 창 크기 저장
		GetClientRect(hWnd, &rect);

		// 오브젝트 위치 갱신을 위한 타이머
		SetTimer(hWnd, 1, 16, NULL);

		// 프레임 갱신을 위한 타이머
		SetTimer(hWnd, 2, 32, NULL);

		mode = 0;
	}
	break;
	case WM_SIZE:
	{
		// 윈도우 창 크기 저장
		GetClientRect(hWnd, &rect);

		// 화면 갱신
		InvalidateRect(hWnd, NULL, true);
	}
	break;
	case WM_TIMER:
	{
		switch (wParam)
		{
			// 오브젝트위치 갱신 타이머
			case 1:

				// 도형들의 위치 업데이트
				for (Shape2D* &shape : shapes)
					shape->Update();

				// 도형 - 윈도우 창 경계 충돌 체크
				for (Shape2D* &shape : shapes)
					shape->Collision(rect);

				// 도형 - 도형 충돌 체크
				for (int i = 0; i < shapes.size(); ++i)
					for (int j = i + 1; j < shapes.size(); ++j)
						shapes[i]->Collision(shapes[j]);

				// 도형 - 도형 Overlap
				for (int i = 0; i < shapes.size(); ++i)
					for (int j = 0; j < shapes.size(); ++j)
						if (shapes[i] != shapes[j])
							shapes[i]->Overlap(shapes[j]);

				break;

			// 프레임 갱신 타이머
			case 2:

				// 화면 갱신
				InvalidateRect(hWnd, NULL, true);
				break;
		}
	}
	break;
	case WM_KEYDOWN:
	{
		// 숫자 1, 2, 3
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
				Rectangle2D *newRec = new Rectangle2D(LOWORD(lParam), HIWORD(lParam), (double)(100));

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

		// 도형 그리기
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

// 정보 대화 상자의 메시지 처리기입니다.
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