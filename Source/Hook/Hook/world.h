#pragma once
#include <Windows.h>
#include <iostream>

struct world
{
	DWORD GameModule = (DWORD)GetModuleHandle("client.dll");
};

struct entety
{
	int health;
	int flags;

	DWORD EntetyPointer;

	void ForceJump(DWORD GameModule)
	{
		*(int*)(GameModule + 0x524BE84) = 2;
	}
};

struct Offsets
{
public:
	DWORD dwLocalPlayer = 0xD8A2BC;
	DWORD m_iHealth = 0x100;
	DWORD m_fFlags = 0x104;
	DWORD dwForceJump = 0x524BE84;
};