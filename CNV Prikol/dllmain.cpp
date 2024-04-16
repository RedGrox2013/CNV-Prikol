// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "ConversationsDetours.h"
#include "SaveListener.h"
#include "CNVPrikolManager.h"
#include "CNVPrikolTokenTranslator.h"
#include "ClearSocialCreditCheat.h"

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials

	PrikolManager.Initialize();
	if (PrikolManager.DebugMode())
		App::ConsolePrintF("CNV Prikol is initialized");

	SaveListenerPtr saveListener = new SaveListener();
	MessageManager.AddListener(saveListener.get(), Simulator::kMsgSaveGame);
	MessageManager.AddListener(saveListener.get(), App::kMsgOnModeEnter);
	CheatManager.AddCheat("clearSocialCredit", new ClearSocialCreditCheat());

	LocaleManager.GetStringDetokenizer()->AddTranslator(new CNVPrikolTokenTranslator());
}

void Dispose()
{
	// This method is called when the game is closing
}

void AttachDetours()
{
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));

	HandleSpaceCommAction__detour::attach(GetAddress(Simulator::cCommManager, HandleSpaceCommAction));
	HandleCivCommAction__detour::attach(GetAddress(Simulator::cCommManager, HandleCivCommAction));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

