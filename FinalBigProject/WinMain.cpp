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
#include <sstream>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

vector<Shape*> g_DrawedShapes;					// Mang cac hinh da ve
BOOLEAN g_IsDrawed;								// Da duoc ve chua?
Point g_LeftTop;								// Toa do cua diem dau tien khi con chuot click den
Point g_RightBottom;							// Toa do cua diem sau do khi con chuot click den

// Ky thuat Creational.
ShapePrototype g_ShapeModel;
Shape* g_PreviewShape;
LOGBRUSH gLogBrush;
const COLORREF RED = RGB(255, 0, 0);
const COLORREF BLUE = RGB(0, 0, 255);
const COLORREF GREEN = RGB(0, 255, 0);
bool gControlDown = false;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HBRUSH hOldBrush, hNewBrush;
HFONT hFont, hOldFont;

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
	int x, y; // Lay toa do hien tai cua con chuot
	static int count = 0; //Dem so luong hinh ma duong thang di qua
	HMENU hMenu = GetMenu(hWnd); //Lay cua so menu
	switch (message)
	{
	case WM_CREATE: //Khi bat dau chuong trinh
		// Chuong trinh mac dinh o che do ve duong thang.
		CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_CHECKED);

		// Cap nhat su thay doi che do ve (trong th nay la ve duong thang)
		g_ShapeModel.setCurShapeType(SHAPE_LINE);

		// Tao cac khuon mau hinh de su dung sau
		g_ShapeModel.addModel(ShapeFactory::GetObjectType(TypeShape::LINE));
		g_ShapeModel.addModel(ShapeFactory::GetObjectType(TypeShape::RECTANGLE));
		g_ShapeModel.addModel(ShapeFactory::GetObjectType(TypeShape::ELLIPSE));
		g_ShapeModel.addModel(ShapeFactory::GetObjectType(TypeShape::SEMI_CIRCLE));
		g_ShapeModel.addModel(ShapeFactory::GetObjectType(TypeShape::TRIANGLE));
		g_ShapeModel.addModel(ShapeFactory::GetObjectType(TypeShape::PENTAGON));
		g_ShapeModel.addModel(ShapeFactory::GetObjectType(TypeShape::HEXAGON));


		// Cap nhat trang thai: chua ve
		g_IsDrawed = FALSE;
		g_PreviewShape = NULL;

		break;
	case WM_LBUTTONDOWN: // Nhan chuot trai
	{
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
		// Neu trang thai la chua ve -> Tao mot doi tuong de ve
		if (!g_IsDrawed) {
			g_PreviewShape = g_ShapeModel.createNewObject();
			if (g_PreviewShape == NULL) break;
		}
		g_IsDrawed = TRUE; // Cap nhat trang thai: bat dau ve
		// Luu vi tri dau tien cua con tro chuot
		g_LeftTop.x = x;
		g_LeftTop.y = y;
		g_RightBottom = g_LeftTop;
	}
	break;

	case WM_MOUSEMOVE: //Di chuot
	{
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
		if (g_IsDrawed)
		{
			g_RightBottom.x = x;
			g_RightBottom.y = y;
			int curShapeType = g_ShapeModel.getCurShapeType();
			/*
				Nhan giu phim SHIFT lan luot cho cac hinh Elip, hinh chu nhat
				se tao ra tuong ung la hinh tron, hinh vuong

				Doi voi ngu giac va luc giac, 
				hinh ve ra la ngu giac deu va luc giac deu
			*/
			if (((wParam & MK_SHIFT) &&
				(curShapeType == SHAPE_ELLIPSE ||
					curShapeType == SHAPE_RECTANGLE)) ||
				curShapeType == SHAPE_PENTAGON ||
				curShapeType == SHAPE_HEXAGON) {
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
	case WM_LBUTTONUP: { // Tha chuot
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
		if (!g_IsDrawed) { // Neu chua ve
			break;
		}
		g_DrawedShapes.push_back(g_PreviewShape);
		g_PreviewShape = NULL;

		for (auto shape_1 : g_DrawedShapes)
		{
			if (shape_1->getClassName().compare("CLine") == 0) {
				//Tao mot Line co thong tin y chang CLine do de kiem tra
				Line l;
				l.setToaDo(shape_1->GetFirstPoint(), shape_1->GetSecondPoint());
				for (auto shape_2 : g_DrawedShapes) {
					if (shape_2->isIntersect(l)) {
						gLogBrush.lbColor = RED;
						//Neu hinh do chua duoc kiem tra lan nao -> tang len 1
						if (!shape_2->isIntersected)
							++count;
						//Luc nay hinh da duoc kiem tra la di qua roi
						shape_2->isIntersected = true;
						shape_2->flag = 1;
					}
					else {
						gLogBrush.lbColor = GREEN;
						shape_2->flag = 0;
					}
					//Doi mau
					shape_2->setColor(gLogBrush);
				}
			}
		}
		//Cap nhat lai trang thai bat dau ve
		g_IsDrawed = FALSE;
		InvalidateRect(hWnd, NULL, TRUE);
	}
	break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_CONTROL:
		{
			gControlDown = true;
			break;
		}
		case 0x5A: //Ctrl + Z Button -> Tuong tu nhu Undo
		{
			if (gControlDown && g_DrawedShapes.size() != 0)
			{
				Shape* shape = g_DrawedShapes[g_DrawedShapes.size() - 1];
				g_DrawedShapes.pop_back();
				if (shape->getClassName().compare("CLine") != 0 && count > 0 && shape->flag != 0)
					--count;
				delete shape;
				InvalidateRect(hWnd, 0, TRUE);
			}
			if (!g_DrawedShapes.size()) count = 0;
			break;
		}
		case VK_DELETE: //Ctrl + Delete button -> Xoa toan bo cac hinh da ve
		{
			while (g_DrawedShapes.size() > 0)
			{
				Shape* bufShape = g_DrawedShapes[g_DrawedShapes.size() - 1];
				g_DrawedShapes.pop_back();
				delete bufShape;
			}
			count = 0;
			InvalidateRect(hWnd, 0, TRUE);
			break;
		}
		case 0x53: //Ctrl + S button -> Luu thong tin cac hinh da ve vao file
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
			break;
		}
		case 0x4C: //Ctrl + L button -> Load va ve lai cac hinh co thong tin duoc luu trong file
		{
			int i_Shape = 0;
			while (g_DrawedShapes.size() > 0) {
				Shape* bufShape = g_DrawedShapes[g_DrawedShapes.size() - 1];
				g_DrawedShapes.pop_back();
				delete bufShape;
			}

			bool f_Load = loadShape("data.db", g_DrawedShapes);
			WCHAR bufferInform[100];
			if (f_Load) {
				wsprintf(bufferInform, L"Load file thành công");
			}
			else {
				wsprintf(bufferInform, L"Load file thất bại");
			}
			count = 0;
			for (auto shape_1 : g_DrawedShapes)
			{
				if (shape_1->getClassName().compare("CLine") == 0) {
					Line l;
					l.setToaDo(shape_1->GetFirstPoint(), shape_1->GetSecondPoint());
					for (auto shape_2 : g_DrawedShapes) {
						if (shape_2->isIntersect(l)) {
							gLogBrush.lbColor = RED;
							if (!shape_2->isIntersected)
								++count;
							shape_2->isIntersected = true;
							shape_2->flag = 1;
						}
						else {
							gLogBrush.lbColor = GREEN;
							shape_2->flag = 0;
						}
						shape_2->setColor(gLogBrush);
					}
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);

			MessageBox(hWnd, bufferInform, L"Load file", MB_OK);
			break;
		}
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_CONTROL:
		{
			gControlDown = false;
			break;
		}
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
				wsprintf(bufferInform, L"Save file: Successed");
			}
			else {
				wsprintf(bufferInform, L"Save file: Failed");
			}
			MessageBox(hWnd, bufferInform, L"Save file", MB_OK);

		}
		break;
		case ID_FILE_LOAD:
		{
			bool f_Load = loadShape("data.db", g_DrawedShapes);
			WCHAR bufferInform[100];
			if (f_Load) {
				wsprintf(bufferInform, L"Load file: Successed");
			}
			else {
				wsprintf(bufferInform, L"Load file: Failed");
			}
			count = 0;
			for (auto shape_1 : g_DrawedShapes)
			{
				if (shape_1->getClassName().compare("CLine") == 0) {
					Line l;
					l.setToaDo(shape_1->GetFirstPoint(), shape_1->GetSecondPoint());
					for (auto shape_2 : g_DrawedShapes) {
						if (shape_2->isIntersect(l)) {
							gLogBrush.lbColor = RED;
							if (!shape_2->isIntersected)
								++count;
							shape_2->isIntersected = true;
							shape_2->flag = 1;
						}
						else {
							gLogBrush.lbColor = GREEN;
							shape_2->flag = 0;
						}
						shape_2->setColor(gLogBrush);
					}
				}
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
			CheckMenuItem(hMenu, ID_SHAPE_PENTAGON, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_HEXAGON, MF_UNCHECKED);

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
			CheckMenuItem(hMenu, ID_SHAPE_PENTAGON, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_HEXAGON, MF_UNCHECKED);
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
			CheckMenuItem(hMenu, ID_SHAPE_PENTAGON, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_HEXAGON, MF_UNCHECKED);
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
			CheckMenuItem(hMenu, ID_SHAPE_PENTAGON, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_HEXAGON, MF_UNCHECKED);
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
			CheckMenuItem(hMenu, ID_SHAPE_PENTAGON, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_HEXAGON, MF_UNCHECKED);
			g_ShapeModel.setCurShapeType(SHAPE_TRIANGLE);
			break;
		}
		case ID_SHAPE_PENTAGON:
		{
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_SEMI, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_TRIANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_PENTAGON, MF_CHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_HEXAGON, MF_UNCHECKED);
			g_ShapeModel.setCurShapeType(SHAPE_PENTAGON);
			break;
		}
		case ID_SHAPE_HEXAGON:
		{
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_SEMI, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_TRIANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_PENTAGON, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_HEXAGON, MF_CHECKED);
			g_ShapeModel.setCurShapeType(SHAPE_HEXAGON);
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
		RECT r;
		GetClientRect(hWnd, &r);
		for (int i = 0; i < g_DrawedShapes.size(); i++) {
			g_DrawedShapes[i]->ReDraw(hdcMem);
		}

		if (g_PreviewShape) {
			g_PreviewShape->ReDraw(hdcMem);
		}

		// Transfer the off-screen DC to the screen
		BitBlt(hdc, rcClient.left, rcClient.top, rcClient.right - rcClient.left,
			rcClient.bottom - rcClient.top, hdcMem, rcClient.left, rcClient.top, SRCCOPY);

		WCHAR bufferInform_count[100];
		wsprintf(bufferInform_count, L"The number of shapes that the line pass through is: %d", count);
		DrawText(hdc, bufferInform_count, lstrlen(bufferInform_count), &r, DT_CENTER);

		// Free-up the off-screen DC
		SelectObject(hdcMem, hOld);
		DeleteObject(hbmMem);
		DeleteDC(hdcMem);
		//DeleteObject(hOldFont);
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
			int flag = arrShape[i]->flag;
			myFile.write((const char*)&typeShape, sizeof(int));
			myFile.write((const char*)&FirstPoint, sizeof(Point));
			myFile.write((const char*)&SecondPoint, sizeof(Point));
			myFile.write((const char*)&flag, sizeof(int));
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
			int flag = -1;
			myFile.read((char*)&typeShape, sizeof(int));
			myFile.read((char*)&FirstPoint, sizeof(Point));
			myFile.read((char*)&SecondPoint, sizeof(Point));
			myFile.read((char*)&flag, sizeof(int));
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
			else if (typeShape == 6) {
				newShape = ShapeFactory::GetObjectType(TypeShape::PENTAGON);
			}
			else if (typeShape == 7) {
				newShape = ShapeFactory::GetObjectType(TypeShape::HEXAGON);
			}
			newShape->setToaDo(FirstPoint, SecondPoint);
			(flag == 1) ? gLogBrush.lbColor = RED : gLogBrush.lbColor = GREEN;
			newShape->setColor(gLogBrush);
			arrShape.push_back(newShape);
		}
		myFile.close();
		return true;
	}
	myFile.close();
	return false;
}