#include "SDKIncludes.h"

Interface::InterfaceTools* newInterface = new Interface::InterfaceTools;

CVMTHookManager* paintTraverseVMT;
CVMTHookManager* clientModeVMT;
CVMTHookManager* baseClientDLLVMT;
CVMTHookManager* overrideViewVMT;

HANDLE thread = 0;

Hooks::oPaintTraverse paintTraverseHook;
Hooks::oCreateMove createMoveHook;
Hooks::oOverrideView  overrideViewHook;

char* clientModeInterface = (char*)newInterface->GetInterface("client.dll", "VClient018");

CSGO::Engine* eng;
CSGO::ClientMode* clientMode;
CSGO::BaseClientDLL* baseClientDLL;
CSGO::ClientModeShared* clientModeShared;
CSGO::Panel* panel = (CSGO::Panel*)newInterface->GetInterface("vgui2.dll", "VGUI_Panel009");
CSGO::ClientEntityList* entList = (CSGO::ClientEntityList*)newInterface->GetInterface("client.dll", "VClientEntityList003");
CSGO::CVar* cVar = (CSGO::CVar*)newInterface->GetInterface("materialsystem.dll", "VEngineCvar007");
CSGO::ConVar* name = cVar->FindVar("name");
CSGO::Surface* surf = (CSGO::Surface*)newInterface->GetInterface("vguimatsurface.dll", "VGUI_Surface031");

/*
	PaintTraverse
*/
void __stdcall PaintTraverse(int vguiID, bool force, bool allowForcing)
{
	paintTraverseHook(panel, vguiID, force, allowForcing);
}

/*
	CreateMove
*/
void __stdcall CreateMove(float sampleTime, CSGO::UserCmd* cmd)
{
	CSGO::BaseEntity* baseEntity = (CSGO::BaseEntity*)entList->GetClientEntity(eng->GetLocalPlayer());

	createMoveHook(clientMode, sampleTime, cmd);
}

/*
	OverrideView
*/
void __stdcall OverrideView(CSGO::ViewSetup* setup)
{
	CSGO::BaseEntity* baseEntity = (CSGO::BaseEntity*)entList->GetClientEntity(eng->GetLocalPlayer());
	
	setup->fov = 135.0;

	overrideViewHook(clientMode, setup);
}

/*
	Main init, inits everything
*/
void Init()
{
	AllocConsole();

	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	//freopen("CONOUT$", "w", stderr);

	SetConsoleTitle("FLI_Hook");

	std::cout << "Welcome to FLI" << std::endl;
	std::cout << "FLI is now getting interfaces..." << std::endl;

	eng = (CSGO::Engine*)newInterface->GetInterface("engine.dll", "VEngineClient014");

	baseClientDLL = (CSGO::BaseClientDLL*)newInterface->GetInterface("client.dll", "VClient018");
	baseClientDLLVMT = new CVMTHookManager((DWORD**)baseClientDLL);

	clientMode = **(CSGO::ClientMode***)((*(uintptr_t**)(clientModeInterface))[10] + 0x5); // thanks for the help tharix
	
	clientModeVMT = new CVMTHookManager((DWORD**)clientMode);
	createMoveHook = (Hooks::oCreateMove)clientModeVMT->HookMethod((DWORD)CreateMove, 24);

	overrideViewVMT = new CVMTHookManager((DWORD**)clientMode);
	overrideViewHook = (Hooks::oOverrideView)overrideViewVMT->HookMethod((DWORD)OverrideView, 18);

	paintTraverseVMT = new CVMTHookManager((DWORD**)panel);
	paintTraverseHook = (Hooks::oPaintTraverse)paintTraverseVMT->HookMethod((DWORD)PaintTraverse, 41);
	
	// also got this from TGF
	*(int*)((DWORD)&name->fnChangeCallback + 0xC) = NULL;
	name->SetValue("Verideth is gawd");
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD fdwReason, LPVOID lpVoid)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Init, 0, 0, 0);

		break;
	case DLL_PROCESS_DETACH:
		FreeLibraryAndExitThread((HMODULE)thread, 0x1);
		clientModeVMT->UnHook();
		overrideViewVMT->UnHook();
		baseClientDLLVMT->UnHook();

		delete clientModeVMT;
		delete overrideViewVMT;
		delete baseClientDLLVMT;
		break;
	}

	return TRUE;
}
