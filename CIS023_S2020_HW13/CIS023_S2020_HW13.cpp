// Module:  CIS023_S2020_HW13.cpp
// Author:  Miguel Antonio Logarta
// Date:    March 20, 2020
// Purpose: Load and use data in an array of objects
//          Use a virtual function
//          Review menu operation

#include "CIS023_S2020_HW13.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hWnd_StartDate[3];							// input, HH:MM:SS
HWND hWnd_Offset[3];							// input, HH:MM:SS
HWND hWnd_Result[3];							// output, HH:MM:SS
HWND hWnd_Add;									// add button
HWND hWnd_Subtract;								// subtract button



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
    LoadStringW(hInstance, IDC_CIS023S2020HW13, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CIS023S2020HW13));

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

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CIS023S2020HW13));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+0);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CIS023S2020HW13);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 250, 350, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
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
            case BN_CLICKED:
                if (LOWORD(lParam) == (WORD)hWnd_Add)               // If user clicks on the add button
                {
                    TCHAR szInStartDate[3][TCHAR_SIZE];             // 2 Dimensional array. Three elements of size TCHAR_SIZE  
                    TCHAR szInOffsetDate[3][TCHAR_SIZE];    
              
                    // Capture inputs for start and offset dates
                    for (int i = 0; i < 3; i++)                                                 
                    {
                        GetWindowText(hWnd_StartDate[i], szInStartDate[i], TCHAR_SIZE);           // Hours, minutes, then seconds
                        GetWindowText(hWnd_Offset[i], szInOffsetDate[i], TCHAR_SIZE);
                    }

                    // Create Objects of TimeClass that stores captured inputs
                    TimeClass StartDate(szInStartDate);
                    TimeClass OffsetDate(szInOffsetDate);

                    // Perform the operation, it returns an array
                    StartDate + OffsetDate;
                    
                    // Display the results
                    SetWindowText(hWnd_Result[0], StartDate.szReturn[0]);
                    SetWindowText(hWnd_Result[1], StartDate.szReturn[1]);
                    SetWindowText(hWnd_Result[2], StartDate.szReturn[2]);

                }
                if (LOWORD(lParam) == (WORD)hWnd_Subtract)          // If user clicked on the subtract button
                {
                    TCHAR szInStartDate[3][TCHAR_SIZE];             // 2 Dimensional array. Three elements of size TCHAR_SIZE  
                    TCHAR szInOffsetDate[3][TCHAR_SIZE];

                    // Capture inputs for start and offset dates
                    for (int i = 0; i < 3; i++)
                    {
                        GetWindowText(hWnd_StartDate[i], szInStartDate[i], TCHAR_SIZE);           // Hours, minutes, then seconds
                        GetWindowText(hWnd_Offset[i], szInOffsetDate[i], TCHAR_SIZE);
                    }

                    // Create Objects of TimeClass that stores captured inputs
                    TimeClass StartDate(szInStartDate);
                    TimeClass OffsetDate(szInOffsetDate);

                    // Perform the operation, it returns an array
                    StartDate - OffsetDate;

                    // Display the results
                    SetWindowText(hWnd_Result[0], StartDate.szReturn[0]);
                    SetWindowText(hWnd_Result[1], StartDate.szReturn[1]);
                    SetWindowText(hWnd_Result[2], StartDate.szReturn[2]);
                }
                break;
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_CREATE:

		// labels
		CreateWindow(TEXT("STATIC"),
			TEXT("Start Date:"),
			WS_VISIBLE | WS_CHILD,
			10, 10, 100, 20, hWnd, NULL, NULL, NULL);

		CreateWindow(TEXT("STATIC"),
			TEXT(":         :"),
			WS_VISIBLE | WS_CHILD,
			40, 40, 100, 20, hWnd, NULL, NULL, NULL);

		CreateWindow(TEXT("STATIC"),
			TEXT("Offset:"),
			WS_VISIBLE | WS_CHILD,
			10, 70, 100, 20, hWnd, NULL, NULL, NULL);

		CreateWindow(TEXT("STATIC"),
			TEXT(":         :"),
			WS_VISIBLE | WS_CHILD,
			40, 100, 100, 20, hWnd, NULL, NULL, NULL);

		CreateWindow(TEXT("STATIC"),
			TEXT("Result:"),
			WS_VISIBLE | WS_CHILD,
			10, 130, 100, 20, hWnd, NULL, NULL, NULL);

		CreateWindow(TEXT("STATIC"),
			TEXT(":         :"),
			WS_VISIBLE | WS_CHILD,
			40, 160, 100, 20, hWnd, NULL, NULL, NULL);

		// edit (input) controls
		hWnd_StartDate[0] = CreateWindow(TEXT("EDIT"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD | ES_NUMBER |
			ES_AUTOHSCROLL | WS_BORDER,
			10, 40, 25, 20, hWnd, NULL, NULL, NULL);

		hWnd_StartDate[1] = CreateWindow(TEXT("EDIT"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD | ES_NUMBER |
			ES_AUTOHSCROLL | WS_BORDER,
			50, 40, 25, 20, hWnd, NULL, NULL, NULL);

		hWnd_StartDate[2] = CreateWindow(TEXT("EDIT"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD | ES_NUMBER |
			ES_AUTOHSCROLL | WS_BORDER,
			90, 40, 25, 20, hWnd, NULL, NULL, NULL);

		hWnd_Offset[0] = CreateWindow(TEXT("EDIT"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD | ES_NUMBER |
			ES_AUTOHSCROLL | WS_BORDER,
			10, 100, 25, 20, hWnd, NULL, NULL, NULL);

		hWnd_Offset[1] = CreateWindow(TEXT("EDIT"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD | ES_NUMBER |
			ES_AUTOHSCROLL | WS_BORDER,
			50, 100, 25, 20, hWnd, NULL, NULL, NULL);

		hWnd_Offset[2] = CreateWindow(TEXT("EDIT"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD | ES_NUMBER |
			ES_AUTOHSCROLL | WS_BORDER,
			90, 100, 25, 20, hWnd, NULL, NULL, NULL);

		// output labels
		hWnd_Result[0] = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			10, 160, 25, 20, hWnd, NULL, NULL, NULL);

		hWnd_Result[1] = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			50, 160, 25, 20, hWnd, NULL, NULL, NULL);

		hWnd_Result[2] = CreateWindow(TEXT("STATIC"),
			TEXT(""),
			WS_VISIBLE | WS_CHILD | WS_BORDER,
			90, 160, 25, 20, hWnd, NULL, NULL, NULL);

		// buttons
		hWnd_Add = CreateWindow(TEXT("BUTTON"),
			TEXT("Add"),
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			10, 210, 80, 30, hWnd, NULL, NULL, NULL);

		hWnd_Subtract = CreateWindow(TEXT("BUTTON"),
			TEXT("Subtract"),
			WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
			130, 210, 80, 30, hWnd, NULL, NULL, NULL);

		break;
	case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
