#include "pch.h"

	WCHAR WindowClass[MAX_NAME_STRING];
	WCHAR WindowTitle[MAX_NAME_STRING];
	INT WindowsHeight;
	INT WindowsWidth;
	HICON hIcon;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
{
	wcscpy_s(WindowClass, TEXT("kEngine"));
	wcscpy_s(WindowTitle, TEXT("kEngine Start"));
	WindowsWidth = 1366;
	WindowsHeight = 768;
	hIcon = LoadIcon(HInstance(), MAKEINTRESOURCE(IDI_MAINICON));
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = hIcon;
	wcex.hIconSm = hIcon;

	wcex.lpszClassName = WindowClass;
	wcex.lpszMenuName = nullptr;
	wcex.hInstance = HInstance();
	wcex.lpfnWndProc = WindowProc;
	RegisterClassEx(&wcex);

	HWND hwnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, WindowsWidth, WindowsHeight, nullptr, nullptr, HInstance(), nullptr);
	if (!hwnd) {
		MessageBox(0, L"Failed to create window!", 0, 0);
		return 0;
	}
	ShowWindow(hwnd, SW_SHOW);

	MSG msg = { 0 };
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}