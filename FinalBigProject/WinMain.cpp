#define _CRT_SECURE_NO_WARNINGS
// MyPaint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "FinalBigProject.h"
#include <windows.h>
#include <windowsx.h>
#include <cmath>
#include <fstream>
#include "ShapePrototype.h"
#include "ShapeFactory.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

vector<Shape*> g_DrawedShapes;					// Mảng các hình đã vẽ
BOOLEAN g_IsDrawed;								// Đã bắt đầu vẽ hay chưa
Point g_LeftTop;								// Lưu tọa độ ban đầu chuột click
Point g_RightBottom;							// Lưu tọa độ chuột lúc sau

// Áp dục kỹ thuật Creational.
ShapePrototype g_ShapeModel;
Shape* g_PreviewShape;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

bool saveShape(string filename, const vector<Shape*>& arrShape);
bool loadShape(string filename, vector<Shape*>& arrShape);

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
	LoadStringW(hInstance, IDC_FINALBIGPROJECT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FINALBIGPROJECT));

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
	for (auto shape : g_DrawedShapes)
	{
		delete shape;
	}
	return (int)msg.wParam;
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

	

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FINALBIGPROJECT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FINALBIGPROJECT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int x, y; // Lấy tọa độ hiện tại của con chuột
	HMENU hMenu = GetMenu(hWnd);
	switch (message)
	{
	case WM_CREATE:
		// Khởi tạo vẽ đường thẳng
		CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_CHECKED);

		// Cập nhật lại thuộc tính curShapeType ở lớp mẫu 
		g_ShapeModel.setCurShapeType(SHAPE_LINE);

		// Tạo các mẫu để sử dụng
		g_ShapeModel.addModel(ShapeFactory::GetObjectType(TypeShape::LINE));
		g_ShapeModel.addModel(ShapeFactory::GetObjectType(TypeShape::RECTANGLE));
		g_ShapeModel.addModel(ShapeFactory::GetObjectType(TypeShape::ELLIPSE));
		g_ShapeModel.addModel(ShapeFactory::GetObjectType(TypeShape::SEMI_CIRCLE));
		g_ShapeModel.addModel(ShapeFactory::GetObjectType(TypeShape::TRIANGLE));


		// Khởi tạo giá trị false lúc chưa vẽ
		g_IsDrawed = FALSE;

		g_PreviewShape = NULL;



		break;
	case WM_LBUTTONDOWN: // giữ chuột
	{

		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
		// Nếu chưa vẽ thì tạo một đối tượng
		if (!g_IsDrawed) {
			g_PreviewShape = g_ShapeModel.createNewObject();
			if (g_PreviewShape == NULL) break;
		}
		g_IsDrawed = TRUE; // Bắt đầu vẽ
		// Lưu lại điểm đầu nhấp chuột
		g_LeftTop.x = x;
		g_LeftTop.y = y;
		g_RightBottom = g_LeftTop;
	}
	break;

	case WM_MOUSEMOVE:
	{

		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
		if (g_IsDrawed)
		{

			g_RightBottom.x = x;
			g_RightBottom.y = y;
			int curShapeType = g_ShapeModel.getCurShapeType();

			if (((wParam & MK_SHIFT) && (curShapeType == SHAPE_ELLIPSE || curShapeType == SHAPE_RECTANGLE) || curShapeType == SHAPE_SEMI_CIRCLE)) {
				int d_Ox = abs(g_RightBottom.x - g_LeftTop.x);
				int d_Oy = abs(g_RightBottom.y - g_LeftTop.y);
				int d_a = min(d_Ox, d_Oy);
				int posRect2Point = g_LeftTop.getPosRectBetwTwoPoint(g_RightBottom);
				if (posRect2Point == 1) {
					g_RightBottom.x = g_LeftTop.x + d_a;
					g_RightBottom.y = g_LeftTop.y - d_a;
				}
				else if (posRect2Point == 2) {
					g_RightBottom.x = g_LeftTop.x + d_a;
					g_RightBottom.y = g_LeftTop.y + d_a;
				}
				else if (posRect2Point == 3) {
					g_RightBottom.x = g_LeftTop.x - d_a;
					g_RightBottom.y = g_LeftTop.y + d_a;
				}
				else {
					g_RightBottom.x = g_LeftTop.x - d_a;
					g_RightBottom.y = g_LeftTop.y - d_a;
				}
			}
			g_PreviewShape->setToaDo(g_LeftTop, g_RightBottom);

		}
		InvalidateRect(hWnd, NULL, FALSE);
	}
	break;
	case WM_LBUTTONUP: { // thả chuột
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
		if (!g_IsDrawed) { // Chưa được vẽ
			break;
		}

		g_DrawedShapes.push_back(g_PreviewShape);
		g_PreviewShape = NULL;

		g_IsDrawed = FALSE;
		InvalidateRect(hWnd, NULL, TRUE);
	}
					 break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case ID_FILE_SAVE:
		{
			bool f_Save = saveShape("data.db", g_DrawedShapes);
			WCHAR bufferInform[100];
			if (f_Save) {
				wsprintf(bufferInform, L"Lưu file thành công");
			}
			else {
				wsprintf(bufferInform, L"Lưu file thất bại");
			}
			MessageBox(hWnd, bufferInform, L"Lưu file", MB_OK);

		}
		break;
		case ID_FILE_LOAD:
		{
			int i_Shape = 0;
			while (g_DrawedShapes.size() > 0) {
				Shape* bufShape = g_DrawedShapes[g_DrawedShapes.size() - 1];
				delete bufShape;
				g_DrawedShapes.pop_back();
			}

			bool f_Load = loadShape("data.db", g_DrawedShapes);
			WCHAR bufferInform[100];
			if (f_Load) {
				wsprintf(bufferInform, L"Load file thành công");
			}
			else {
				wsprintf(bufferInform, L"Load file thất bại");
			}

			InvalidateRect(hWnd, NULL, TRUE);

			MessageBox(hWnd, bufferInform, L"Load file", MB_OK);
		}
		break;
		case ID_SHAPE_LINE:
		{
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_SEMI, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_TRIANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_POLYGON, MF_UNCHECKED);

			g_ShapeModel.setCurShapeType(SHAPE_LINE);
			break;
		}
		break;
		case ID_SHAPE_RECTANGLE:
		{
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_SEMI, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_TRIANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_POLYGON, MF_UNCHECKED);

			g_ShapeModel.setCurShapeType(SHAPE_RECTANGLE);
			break;
		}
		break;
		case ID_SHAPE_ELLIPSE:
		{
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_SEMI, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_TRIANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_POLYGON, MF_UNCHECKED);

			g_ShapeModel.setCurShapeType(SHAPE_ELLIPSE);
			break;
		}
		case ID_SHAPE_SEMI:
		{
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_SEMI, MF_CHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_TRIANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_POLYGON, MF_UNCHECKED);

			g_ShapeModel.setCurShapeType(SHAPE_SEMI_CIRCLE);
			break;
		}
		case ID_SHAPE_TRIANGLE:
		{
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_SEMI, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_TRIANGLE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_POLYGON, MF_UNCHECKED);

			g_ShapeModel.setCurShapeType(SHAPE_TRIANGLE);
			break;
		}
		case ID_SHAPE_POLYGON:
		{
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_SEMI, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_TRIANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_POLYGON, MF_CHECKED);

			g_ShapeModel.setCurShapeType(SHAPE_POLYGON);
			break;
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

		HDC hdcMem;
		HBITMAP hbmMem;
		HANDLE hOld;
		RECT rcClient;
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...

		// Create an off-screen DC for double-buffering
		GetClientRect(hWnd, &rcClient);
		hdcMem = CreateCompatibleDC(hdc);
		hbmMem = CreateCompatibleBitmap(hdc, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);

		hOld = SelectObject(hdcMem, hbmMem);

		// Draw into hdcMem here
		FillRect(hdcMem, &rcClient, HBRUSH(RGB(255, 255, 255)));

		for (int i = 0; i < g_DrawedShapes.size(); i++) {
			g_DrawedShapes[i]->ReDraw(hdcMem);
		}

		if (g_PreviewShape) {
			g_PreviewShape->ReDraw(hdcMem);
		}

		// Transfer the off-screen DC to the screen
		BitBlt(hdc, rcClient.left, rcClient.top, rcClient.right - rcClient.left,
			rcClient.bottom - rcClient.top, hdcMem, rcClient.left, rcClient.top, SRCCOPY);

		// Free-up the off-screen DC
		SelectObject(hdcMem, hOld);
		DeleteObject(hbmMem);
		DeleteDC(hdcMem);

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

bool saveShape(string filename, const vector<Shape*>& arrShape)
{
	fstream myFile;
	myFile.open(filename, ios::out | ios::binary);
	if (myFile) {
		for (int i = 0; i < arrShape.size(); i++) {
			int typeShape = arrShape[i]->getType();
			Point FirstPoint = arrShape[i]->GetFirstPoint();
			Point SecondPoint = arrShape[i]->GetSecondPoint();
			myFile.write((const char*)&typeShape, sizeof(int));
			myFile.write((const char*)&FirstPoint, sizeof(Point));
			myFile.write((const char*)&SecondPoint, sizeof(Point));
		}
		myFile.close();
		return true;
	}
	myFile.close();
	return false;
}

bool loadShape(string filename, vector<Shape*>& arrShape)
{
	fstream myFile;
	myFile.open(filename, ios::in | ios::binary);
	if (myFile) {
		Shape* newShape = NULL;
		while (1) {
			int typeShape = 0;
			Point FirstPoint;
			Point SecondPoint;
			myFile.read((char*)&typeShape, sizeof(int));
			myFile.read((char*)&FirstPoint, sizeof(Point));
			myFile.read((char*)&SecondPoint, sizeof(Point));
			if (typeShape == 0) break;

			if (typeShape == 1) {
				newShape = ShapeFactory::GetObjectType(TypeShape::LINE);
			}
			else if (typeShape == 2) {
				newShape = ShapeFactory::GetObjectType(TypeShape::RECTANGLE);
			}
			else if (typeShape == 3) {
				newShape = ShapeFactory::GetObjectType(TypeShape::ELLIPSE);
			}
			else if (typeShape == 4) {
				newShape = ShapeFactory::GetObjectType(TypeShape::SEMI_CIRCLE);
			}
			else if (typeShape == 5) {
				newShape = ShapeFactory::GetObjectType(TypeShape::TRIANGLE);
			}
			newShape->setToaDo(FirstPoint, SecondPoint);
			arrShape.push_back(newShape);
		}
		myFile.close();
		return true;
	}
	myFile.close();
	return false;
}