#include "world.h"

int WINAPI MainThread(HMODULE hModule)
{
    world GameWorld;
    entety LocalPlayer;
    Offsets GameInfo;

    while (!GetAsyncKeyState(VK_END))
    {

        if (GetAsyncKeyState(VK_SPACE))
        {
            LocalPlayer.EntetyPointer = *(DWORD*)(GameWorld.GameModule + GameInfo.dwLocalPlayer);

            if (LocalPlayer.EntetyPointer != NULL)
            {
                LocalPlayer.health = *(int*)(LocalPlayer.EntetyPointer + GameInfo.m_iHealth);
                LocalPlayer.flags = *(int*)(LocalPlayer.EntetyPointer + GameInfo.m_fFlags);

                if (LocalPlayer.health > 0 && LocalPlayer.flags == 257)
                {
                    LocalPlayer.ForceJump(GameWorld.GameModule);
                }
            }
        }
    }

    FreeLibraryAndExitThread(hModule, NULL);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL);
    }
    return TRUE;
}
