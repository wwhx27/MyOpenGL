#include <windows.h>
LRESULT CALLBACK GLWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//���촰��
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = NULL;
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = NULL;
	wndclass.hIconSm = NULL;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = GLWindowProc;
	wndclass.lpszClassName = L"GLWindow";
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	//ע�ᴰ��
	ATOM atom = RegisterClassEx(&wndclass);
	if (!atom)
	{
		MessageBox(NULL, L"Notice", L"Error", MB_OK);
		return 0;
	}
	RECT rect;
	rect.left = 0;
	rect.right = 800;
	rect.top = 0;
	rect.bottom = 600;
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, NULL);
	int windowWidth = rect.right - rect.left;
	int windowHeight = rect.bottom - rect.top;
	HWND hwnd = CreateWindowEx(NULL, L"GLWindow", L"OpenGL Window", WS_OVERLAPPEDWINDOW,
		100, 100, windowWidth, windowHeight,
		NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg,NULL,NULL ,NULL,PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}