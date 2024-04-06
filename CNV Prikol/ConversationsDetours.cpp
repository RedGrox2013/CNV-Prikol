#include "stdafx.h"
#include "ConversationsDetours.h"
#include "shellapi.h"

enum CommActions : uint32_t
{
	kCnvCommDefault = 0xCAFF0F72,
	kCnvCommEvent = 0x02D5DCEC,
	kOpenUrl = id("kOpenUrl")
};

void HandleSpaceCommAction__detour::detoured(const Simulator::CnvAction& action, uint32_t source, Simulator::PlanetID planetKey, void* pMission)
{
	Simulator::CnvAction newAction = action;
	switch (action.actionID)
	{
	case CommActions::kOpenUrl:
		ShellExecute(NULL, L"open", L"https://www.youtube.com/@RedGrox/", NULL, NULL, SW_SHOW);
		newAction.actionID = CommActions::kCnvCommEvent;
		newAction.key = { id("ModCreator"), 0x055ADA24, id("Prikol_diplomacy") };
		break;
	default:
		break;
	}

	original_function(this, newAction, source, planetKey, pMission);
}