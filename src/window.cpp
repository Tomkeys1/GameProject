
// EXTERNAL INCLUDES
// INTERNAL INCLUDES
#include "resource.h"
#include "rendering/window.h"

//WndProc
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//Handle the messages in the window.
	switch (msg)
	{
	//If the message is destroy, destroy the window.
	case WM_DESTROY:
		DestroyWindow(hwnd);
		break;
	//If the message is close, stop proccessing messages.
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		//Go on.
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

//MonitorEnumProc
BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
	//Initialize variables.
	MONITORINFO info;
	info.cbSize = sizeof(info);

	//Get the monitor info of the inputed monitor.
	if (GetMonitorInfo(hMonitor, &info))
	{
		//Save the Monitor information into the struct display.
		Display currentMonitor;

		currentMonitor.width = abs(info.rcMonitor.left - info.rcMonitor.right);
		currentMonitor.height = abs(info.rcMonitor.top - info.rcMonitor.bottom);

		currentMonitor.posX = info.rcMonitor.left;
		currentMonitor.posY = info.rcMonitor.top;

		//Add the display into windows displays list.
		Window::GetInstance().AddDisplay(currentMonitor);
	}

	return TRUE;
}

//Declare Window as a Singleton
DECLARE_SINGLETON(Window)

//Void Instantiate
void Window::Instantiate(char* title, ui32 width, ui32 height, ui32 displayID)
{
	//Initialize variable
	ui32 style = 0;

	//Enumerate through the monitors and return if return if it wasnt succesful
	if (!EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, 0))
		return;

	//Create a struct to hold window data and fill that struct with data.
	WNDCLASSEXA wndex = { 0 };
	wndex.cbSize = sizeof(WNDCLASSEX);
	wndex.lpfnWndProc = WndProc;
	wndex.hInstance = GetModuleHandle(NULL);
	wndex.hIcon = LoadIcon(wndex.hInstance, MAKEINTRESOURCE(IDI_APPICON));
	wndex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndex.lpszClassName = title;

	//Register a window and if that fails crash the program.
	if (!RegisterClassExA(&wndex))
		throw;

	//Set the window style.
	style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

	//Get the selected display.
	Display* selectedDisplay = GetDisplay(displayID);

	//Get the center position of the display.
	ui32 posX = ((selectedDisplay->width - width) / 2) + selectedDisplay->posX;
	ui32 posY = ((selectedDisplay->height - height) / 2) + selectedDisplay->posY;

	//Fill the RECT struct with data.
	RECT adjustedRect = RECT
	{
		static_cast<LONG>(posX),
		static_cast<LONG>(posY),
		static_cast<LONG>(width),
		static_cast<LONG>(height)
	};

	//Adjust the Window. If that fails crash the program.
	if (!AdjustWindowRectEx(&adjustedRect, style, FALSE, NULL))
		throw;

	//Create a handle onto a newly created window.
	this->handle = CreateWindowExA
	(
		NULL,
		title,
		title,
		style,
		adjustedRect.left,
		adjustedRect.top,
		adjustedRect.right,
		adjustedRect.bottom,
		NULL,
		NULL,
		GetModuleHandle(NULL), NULL
	);
	
	//If that fails crash the program.
	if (this->handle == NULL)
	{
		throw;
	}

	//Show and update the window.
	ShowWindow(this->handle, SW_SHOW);
	UpdateWindow(this->handle);
}

//Void DispatchMessages
void Window::DispatchMessages(void)
{
	//If messages exist, handle those messages.
	MSG msg;
	while (PeekMessageA(&msg, this->handle, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

//Void AddDisplay
void Window::AddDisplay(const Display& display)
{
	//Add the inputed display into this windows displays list.
	this->displays.push_back(display);
}

//GetDisplay
Display* Window::GetDisplay(ui32 id) const
{
	//Return a display pojnter onto this windows displays list at the inputed index.
	return const_cast<Display*>(&this->displays[id]);
}
