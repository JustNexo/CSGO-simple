#define NOMINMAX
#include <Windows.h>

#include "sdk/sdk.hpp"
#include "sdk/utils/utils.hpp"
#include "sdk/utils/input.hpp"

#include "hooks.hpp"
#include "render/menu.hpp"
#include "configurations.hpp"
#include "render/render.hpp"

#include "config.hpp"

DWORD WINAPI OnDllAttach(LPVOID base)
{
	while (!GetModuleHandleA("serverbrowser.dll"))
		Sleep(1000);

    

    Utils::AttachConsole();


    try 
    {
        uint8_t* _colora = 0;

        Utils::ConsolePrint("Initializing...\n");

        CConfig::Get().Setup();

        Interfaces::Initialize();
        Interfaces::Dump();

        NetvarSys::Get().Initialize();
        InputSys::Get().Initialize();
		Render::Get().Initialize();
        Menu::Get().Initialize();
        
        Hooks::Initialize();

       

        InputSys::Get().RegisterHotkey(VK_INSERT, [base]() {
            Menu::Get().Toggle();
        });

        Utils::ConsolePrint("Finished.\n");
		Utils::ConsolePrint("Built on: %s %s\n", __DATE__, __TIME__);

        g_EngineClient->ExecuteClientCmd("clear");

        g_CVar->ConsoleColorPrintf(Color::Red, R"( 
  _   _   _____  __  __   ___      _   _    ___     ___    _  __
 | \ | | | ____| \ \/ /  / _ \    | | | |  / _ \   / _ \  | |/ /
 |  \| | |  _|    \  /  | | | |   | |_| | | | | | | | | | | ' / 
 | |\  | | |___   /  \  | |_| |   |  _  | | |_| | | |_| | | . \ 
 |_| \_| |_____| /_/\_\  \___/    |_| |_|  \___/   \___/  |_|\_\                                                         
	)");

        g_CVar->FindVar("crosshair")->SetValue(true);

      //  FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
       
    } 

    

    catch(const std::exception& ex) 
    {
        Utils::ConsolePrint("An error occured during initialization:\n");
        Utils::ConsolePrint("%s\n", ex.what());
        Utils::ConsolePrint("Press any key to exit.\n");
        Utils::ConsoleReadKey();
        Utils::DetachConsole();


        FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
    }

}

void SetColor(int _r, int _g, int _b, int _a = 0)
{
     //_colora = (unsigned char)_r;
}

BOOL WINAPI OnDllDetach()
{
#ifdef _DEBUG
    Utils::DetachConsole();
#endif

    Hooks::Shutdown();

    Menu::Get().Shutdown();
    return TRUE;
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDll, _In_ DWORD fdwReason, _In_opt_ LPVOID lpvReserved)
{
    switch(fdwReason) 
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hinstDll);
            CreateThread(nullptr, 0, OnDllAttach, hinstDll, 0, nullptr);
            return TRUE;
        case DLL_PROCESS_DETACH:
            if(lpvReserved == nullptr)
                return OnDllDetach();
            return TRUE;
        default:
            return TRUE;
    }
}
