#include <windows.h>; // підключення бібліотеки з функціями API
#include "Resource.h"
#include "strsafe.h"
// Глобальні змінні:
HINSTANCE hInst; //Дескриптор програми
LPCTSTR szWindowClass = L"Shafaruk,Bezsonov,Paladuk";
LPCTSTR szTitle = L"Шафарук,Безсонов,Паладюк";
// Попередній опис функцій
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

#define MYWM_NOTIFYICON (WM_USER + 1)


void MyMenu(HWND hWnd) {
	HMENU hMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();
	HMENU hSubMenu1 = CreateMenu();
	HMENU hSubMenu2 = CreateMenu();
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu, L"File");
	AppendMenu(hSubMenu, MF_STRING, NULL, L"1");
	AppendMenu(hSubMenu, MF_STRING, NULL, L"2");
	AppendMenu(hSubMenu, MF_STRING, NULL, L"3");


	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu1, L"NewMenuItem1");
	AppendMenu(hSubMenu1, MF_STRING, NULL, L"3");
	AppendMenu(hSubMenu1, MF_STRING, NULL, L"2");
	AppendMenu(hSubMenu1, MF_STRING, NULL, L"1");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hSubMenu2, L"NewMenuItem2");
	AppendMenu(hSubMenu2, MF_STRING, NULL, L"КІУКІ-21-6");
	AppendMenu(hSubMenu2, MF_STRING, NULL, L"Студенти");
	SetMenu(hWnd, hMenu);
}

// Основна програма
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg;
	// Реєстрація класу вікна
	MyRegisterClass(hInstance);
	// Створення вікна програми
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл обробки повідомлень
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_DROPSHADOW ; //стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; //віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; //дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); //визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); //визначення курсору
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);; //установка фону
	wcex.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1); //визначення меню
	wcex.lpszClassName = szWindowClass; //ім’я класу
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex); //реєстрація класу вікна
}
// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst

	hWnd = CreateWindow(szWindowClass, // ім’я класу вікна
		szTitle, // назва програми
		WS_OVERLAPPEDWINDOW | WS_ICONIC | WS_CAPTION | WS_BORDER | WS_HSCROLL | WS_SYSMENU , // стиль вікна
		10, // положення по Х
		30, // положення по Y
		300, // розмір по Х
		400, // розмір по Y
		NULL, // дескриптор батьківського вікна
		NULL, // дескриптор меню вікна
		hInstance, // дескриптор програми
		NULL); // параметри створення.
	if (!hWnd) //Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow); //Показати вікно
	UpdateWindow(hWnd); //Оновити вікно
	return TRUE;
}



HWND hWnd; // указатель на окно 
HICON hIcon = LoadIcon(NULL, IDI_APPLICATION); // указатель на иконку 
char* szText; // указатель на текст для подсказки 
BOOL TrayMessage(HWND hDlg, DWORD dwMessage, UINT uID, HICON hIcon, PSTR pszTip)
// systray icon 
{
	BOOL res;

	NOTIFYICONDATA tnd;

	tnd.cbSize = sizeof(NOTIFYICONDATA);
	tnd.hWnd = hDlg;
	tnd.uID = uID;

	tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	tnd.uCallbackMessage = MYWM_NOTIFYICON; // Сообщение, которое пошлется при всяких там кликах на иконке... 
	tnd.hIcon = hIcon;

	if (pszTip)
	{
		lstrcpyn(tnd.szTip, (LPWSTR)pszTip, sizeof(tnd.szTip));
	}
	else
	{
		tnd.szTip[0] = '\0';
	}

	res = Shell_NotifyIcon(dwMessage, &tnd);

	return res;
}



LRESULT CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:  // ініціалізація функціоналу керування діалоговим вікном
		return TRUE;

		// цикл обробки натискання елементів на формі діалогового вікна
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));  // знищення модального діалогового вікна
			return TRUE;
		}
		break;
	}
	return FALSE;
}

LRESULT CALLBACK DlgProc3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:  // ініціалізація функціоналу керування діалоговим вікном
		return TRUE;

		// цикл обробки натискання елементів на формі діалогового вікна
	case WM_COMMAND:
		
		
		switch (LOWORD(wParam)) {
		case IDCANCEL: {
			EndDialog(hDlg, LOWORD(wParam));  // знищення модального діалогового вікна
			MessageBoxA(hDlg, "Вы закрыли окно", "КІУКІ-21-6", MB_OK);
			return TRUE;
		}
		case INTOREAD: {
			HWND hEdit1 = GetDlgItem(hDlg, IDC_EDIT1);
			CHAR s_text_1[1024];
			GetWindowTextA(hEdit1, (LPSTR)s_text_1, 1024);

			MessageBoxA(hDlg, (LPCSTR)s_text_1, "КІУКІ-21-6", MB_OK);
			break;
		}
		default:
			break;
		}
	

	}
	return FALSE;
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	SCROLLINFO si; 
	TEXTMETRIC tm;
	// These variables are required to display text. 
	static int xClient;     // width of client area 
	static int yClient;     // height of client area 
	static int xClientMax;  // maximum width of client area 

	static int xChar;       // horizontal scrolling unit 
	static int yChar;       // vertical scrolling unit 
	static int xUpper;      // average width of uppercase letters 

	static int xPos;        // current horizontal scrolling position 
	static int yPos;        // current vertical scrolling position 

	int x, y;               // horizontal and vertical coordinates
	HRESULT hr;
	size_t strLength;        // length of an abc[] item 


#define LINES 28 //

	switch (message)
	{
	case WM_CREATE: //Повідомлення приходить при створенні вікна
		TrayMessage(hWnd, NIM_ADD, 0, hIcon, szText);

		hdc = GetDC(hWnd);

		// Extract font dimensions from the text metrics. 
		GetTextMetrics(hdc, &tm);
		xChar = tm.tmAveCharWidth;
		xUpper = (tm.tmPitchAndFamily & 1 ? 3 : 2) * xChar / 2;
		yChar = tm.tmHeight + tm.tmExternalLeading;

		// Free the device context. 
		ReleaseDC(hWnd, hdc);

		xClientMax = 48 * xChar + 12 * xUpper;
		break;


	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_CHANGE_32771:
			hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));
			TrayMessage(hWnd, NIM_MODIFY, 0, hIcon, szText);
			SetClassLongPtr(hWnd, GCLP_HICON, (LONG)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
			break;
		case ID_CHANGE_32772:
			hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON2));
			TrayMessage(hWnd, NIM_MODIFY, 0, hIcon, szText);
			SetClassLongPtr(hWnd, GCLP_HICON, (LONG)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON2)));
			break;
		case ID_CHANGE_32777:
			hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON3));
			TrayMessage(hWnd, NIM_MODIFY, 0, hIcon, szText);
			SetClassLongPtr(hWnd, GCLP_HICON, (LONG)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON3)));
			break;
		case ID_32782:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);
			break;
		case ID_55555:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hWnd, DlgProc3);
			break;
		case IDMENU:
			MyMenu(hWnd);
			//LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU2));
			break;
		}
		break;

	case WM_CLOSE:
		if ((DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, DlgProc)) == IDOK) {
			TrayMessage(hWnd, NIM_DELETE, 0, 0, 0);
			DestroyWindow(hWnd);
		};



	case WM_SIZE:

		// Retrieve the dimensions of the client area. 
		yClient = HIWORD(lParam);
		xClient = LOWORD(lParam);

		// Set the horizontal scrolling range and page size. 
		si.cbSize = sizeof(si);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = 2 + xClientMax / xChar;
		si.nPage = xClient / xChar;
		SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
		return 0;


	case WM_HSCROLL:
		// Get all the vertial scroll bar information.
		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;

		// Save the position for comparison later on.
		GetScrollInfo(hWnd, SB_HORZ, &si);
		xPos = si.nPos;
		switch (LOWORD(wParam))
		{
			// User clicked the left arrow.
		case SB_LINELEFT:
			si.nPos -= 1;
			break;

			// User clicked the right arrow.
		case SB_LINERIGHT:
			si.nPos += 1;
			break;

			// User clicked the scroll bar shaft left of the scroll box.
		case SB_PAGELEFT:
			si.nPos -= si.nPage;
			break;

			// User clicked the scroll bar shaft right of the scroll box.
		case SB_PAGERIGHT:
			si.nPos += si.nPage;
			break;

			// User dragged the scroll box.
		case SB_THUMBTRACK:
			si.nPos = si.nTrackPos;
			break;

		default:
			break;
		}

		// Set the position and then retrieve it.  Due to adjustments
		// by Windows it may not be the same as the value set.
		si.fMask = SIF_POS;
		SetScrollInfo(hWnd, SB_HORZ, &si, TRUE);
		GetScrollInfo(hWnd, SB_HORZ, &si);

		// If the position has changed, scroll the window.
		if (si.nPos != xPos)
		{
			ScrollWindow(hWnd, xChar * (xPos - si.nPos), 0, NULL, NULL);
		}

		return 0;

	case WM_PAINT: //Перемалювати вікно
	{
		hdc = BeginPaint(hWnd, &ps); //Почати графічний вивід
		// Get vertical scroll bar position.
		si.cbSize = sizeof(si);
		si.fMask = SIF_POS;
		GetScrollInfo(hWnd, SB_VERT, &si);
		yPos = si.nPos;

		// Get horizontal scroll bar position.
		GetScrollInfo(hWnd, SB_HORZ, &si);
		xPos = si.nPos;

		int i = 0;
		x = xChar * (1 - xPos);
		y = yChar * (i - yPos);
		i++;
		LPCWSTR str = L"Hello world";
		hr = StringCchLength(str, STRSAFE_MAX_CCH, &strLength);

		TextOut(hdc, x, y, str, strLength);
	}
		EndPaint(hWnd, &ps); //Закінчити графічний вивід
		break;
	case WM_LBUTTONDBLCLK:
	{
		LPCWSTR s = L"Ви зробили дабл клік";
		LPCWSTR r = L"Double Click";
		MessageBox(hWnd, s, r, MB_OK | MB_ICONEXCLAMATION);
	}
	break;
	case WM_DESTROY: //Завершення роботи
		PostQuitMessage(0);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
