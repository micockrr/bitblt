//everything is pasted!!!!!!!

#include <cstdio>
#include <Windows.h>

//from memz

HCRYPTPROV prov;


int random() {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);

	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
	return out & 0x7fffffff; 
}


void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	// Get a handle to the desktop window
	const HWND hDesktop = GetDesktopWindow();
	// Get the size of screen to the variable desktop
	GetWindowRect(hDesktop, &desktop);
	// The top left corner will have coordinates (0,0)
	// and the bottom right corner will have coordinates
	// (horizontal, vertical)
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

int main()
{
	while (true)
	{
		HWND hwnd = GetDesktopWindow();
		HDC hdc = GetWindowDC(hwnd);
		RECT rekt;
		GetWindowRect(hwnd, &rekt);
		if (GetAsyncKeyState(VK_ESCAPE))
			return 0;
		//shit
		int x = GetSystemMetrics(0), y = GetSystemMetrics(1);
		int a1 = GetSystemMetrics(0), b1 = GetSystemMetrics(1);
		int sw = GetSystemMetrics(0), sh = GetSystemMetrics(1);
		int ry = GetSystemMetrics(0), rx = GetSystemMetrics(1);
		int i = 1;
		while (i <= 1) {
			hdc = GetDC(0);
			int x = rand() % y;
			int y = rand() % x;
			for (int i = 0; i < 1; i++) {
				if (GetAsyncKeyState(VK_ESCAPE))
					return 1;;
				int x1 = random() % (rekt.right - 100);
				int y1 = random() % (rekt.bottom - 100);
				int x2 = random() % (rekt.right - 100);
				int y2 = random() % (rekt.bottom - 100);
				int width, height;
				GetDesktopResolution(width, height);
				POINT Point;

				int v5 = width - 5;
				int v6 = width - 20;
				BitBlt(hdc, -1, -1, width, height, hdc, 0, 0, SRCINVERT);
				BitBlt(hdc, 0, 0, rekt.right - rekt.left, rekt.bottom - rekt.top, hdc, 1, 1, NOTSRCCOPY);
				Sleep(20);
				BitBlt(hdc, 0, 0, rekt.right - rekt.left, rekt.bottom - rekt.top, hdc, -10, -5, SRCINVERT | SRCERASE | SRCINVERT);
				Sleep(100);
				StretchBlt(hdc, 50, 50, rekt.right - 100, rekt.bottom - 100, hdc, 0, 0, rekt.right, rekt.bottom, SRCINVERT);
				Sleep(20);
				StretchBlt(hdc, -5, -5, v6, v5, hdc, 0, 0, width, height, NOTSRCERASE);
				StretchBlt(hdc, 5, 5, v6, v5, hdc, 0, 0, width, height, NOTSRCERASE);
				StretchBlt(hdc, -5, -5, v6, width - 5, hdc, 0, 0, height, width, SRCINVERT);
				StretchBlt(hdc, 5, 5, v6, width - 5, hdc, 0, 0, height, width, SRCINVERT);

				GetCursorPos(&Point);
				DrawIcon(hdc, Point.x, Point.y, LoadIconW(0, IDI_HAND));
				PatBlt(hdc, 0, 0, x, y, PATINVERT);
				BitBlt(hdc, rand() % 222, rand() % 222, width, height, hdc, rand() % 222, rand() % 222, NOTSRCERASE);
				hdc = GetDC(0);
				x = rand() % width;
				BitBlt(hdc, x, 1, 10, height, hdc, x, 0, SRCCOPY);
				BitBlt(hdc, 0, 0, width, height, hdc, 0, 0, NOTSRCCOPY);//blink
				BitBlt(hdc, x1, y1, width, height, hdc, x2, y2, SRCCOPY); //puzzle 
				StretchBlt(hdc, 50, 50, width - 100, height - 100, hdc, 0, 0, rekt.right, rekt.bottom, SRCCOPY); // tunnel
				BitBlt(hdc, -1, 1, width, height, hdc, 2, 2, 0x999999);
				//melting
				BitBlt(hdc, 11, 3, b1, b1, hdc, a1, 0, SRCCOPY);
				BitBlt(hdc, x, -2, -y, x, hdc, x, 0, SRCCOPY);
				BitBlt(hdc, 3, b1, b1, a1, hdc, 0, a1, SRCCOPY);
				BitBlt(hdc, -6, x, -y, x, hdc, 0, y, SRCCOPY);
				BitBlt(hdc, a1, 3, b1, b1, hdc, a1, 0, SRCCOPY);
				BitBlt(hdc, x, -2, -y, x, hdc, x, 0, SRCCOPY);
				BitBlt(hdc, 3, b1, b1, a1, hdc, 0, a1, SRCCOPY);
				BitBlt(hdc, -6, x, -y, x, hdc, 0, y, SRCCOPY);
				BitBlt(hdc, rx, 1, sw, sh, hdc, rx, 0, SRCCOPY);
				BitBlt(hdc, rx, -1, -sw, sh, hdc, rx, 0, SRCCOPY);
				BitBlt(hdc, 1, ry, sw, sh, hdc, 0, ry, SRCCOPY);
				BitBlt(hdc, -1, ry, -sw, sh, hdc, 0, ry, SRCCOPY); i++;
			}
		}
		ReleaseDC(hwnd, hdc);
		
	}

	return 1;
}