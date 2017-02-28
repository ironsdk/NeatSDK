#include "SDKIncludes.h"

Interface::InterfaceTools* newInterface = new Interface::InterfaceTools;

CVMTHookManager* clientModeVMT;
CVMTHookManager* baseClientDLLVMT;
CVMTHookManager* overrideViewVMT;

Hooks::oCreateMove createMoveHook;
Hooks::oOverrideView  overrideViewHook;

char* clientModeInterface = (char*)newInterface->GetInterface("client.dll", "VClient018");

CSGO::Engine* eng;
CSGO::ClientMode* clientMode;
CSGO::BaseClientDLL* baseClientDLL;
CSGO::ClientModeShared* clientModeShared;
CSGO::ClientEntityList* entList = (CSGO::ClientEntityList*)newInterface->GetInterface("client.dll", "VClientEntityList003");
CSGO::CVar* cVar = (CSGO::CVar*)newInterface->GetInterface("materialsystem.dll", "VEngineCvar007");
CSGO::ConVar* name = cVar->FindVar("name");

/*
	CreateMove
*/
void __stdcall CreateMove(float sampleTime, CSGO::UserCmd* cmd)
{
	createMoveHook(clientMode, sampleTime, cmd);
}

/*
	OverrideView
*/
void __stdcall OverrideView(CSGO::ViewSetup* setup)
{
	/*
		change these to wahtever you like,
		was just palying around too see if
		the hook was working.
	*/
	
	setup->angles.x = setup->width;
	setup->angles.y = setup->height;
	setup->m_nMotionBlurMode = 0;
	setup->m_flFarBlurDepth = 0;
	setup->m_flFarFocusDepth = 0;
	setup->m_flFarBlurRadius = 0;
	setup->origin = CSGO::Vector(setup->angles.x, setup->angles.y, setup->angles.z);

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

	// also got this from TGF
	*(int*)((DWORD)&name->fnChangeCallback + 0xC) = NULL;
	name->SetValue("Verideth is gawd");
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD fdwReason, LPVOID lpVoid)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Init, 0, 0, 0); 
		break;
	}

	return TRUE;
}
