#include "GDIManager.h"

ULONG_PTR GDIManager::token = 0;
int GDIManager::refCount = 0;

GDIManager::GDIManager()
{
	/*if (refCount++ == 0)
	{
		Gdiplus::GdiplusStartupInput input;
		input.GdiplusVersion = 1;
		input.DebugEventCallback = nullptr;
		input.SuppressBackgroundThread = false;
		Gdiplus::GdiplusStartup(&token, &input, nullptr);
	}*/
}

GDIManager::~GDIManager()
{
	/*if (--refCount == 0)
	{
		Gdiplus::GdiplusShutdown(token);
	}*/
}
