#pragma once
#include <Windows.h>
#include <gdiplus.h>
class GDIManager
{
public:
	GDIManager();
	~GDIManager();
private:
	static ULONG_PTR token;
	static int refCount;
};

