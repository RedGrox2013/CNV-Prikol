#include "stdafx.h"
#include "ConversationsDetours.h"
#include <shellapi.h>
#include <Spore/Properties.h>

enum CommActions : uint32_t
{
	kCnvCommDefault = 0xCAFF0F72,
	kCnvCloseComm = 0x01994745,
	kCnvCommEvent = 0x02D5DCEC,
	kOpenUrl = id("kOpenUrl")
};

static bool HundleAction(Simulator::CnvAction& action, uint32_t source, Simulator::PlanetID planetKey, void* pMission,
	void* pSourceCiv, Simulator::cCity* pSourceCity, Simulator::cCity* pTargetCity)
{
	bool isCustom = false;
	switch (action.actionID)
	{
	case CommActions::kOpenUrl:
	{
		PropertyListPtr prop;
		char* url = nullptr;
		if (PropManager.GetPropertyList(action.key.instanceID, action.key.groupID, prop)) {
			App::Property::GetCString8(prop.get(), id("url"), url);
			App::Property::GetUInt32(prop.get(), id("action"), action.actionID);
			App::Property::GetKey(prop.get(), id("actionKey"), action.key);
			App::Property::GetBool(prop.get(), id("nextActionIsCustom"), isCustom);
		}
		if (!url) {
			url = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";
			action.actionID = kCnvCommDefault;
			isCustom = false;
		}

		ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOW);
	}
	break;
	default:
		break;
	}

	return isCustom;
}


void HandleSpaceCommAction__detour::detoured(const Simulator::CnvAction& action, uint32_t source, Simulator::PlanetID planetKey, void* pMission)
{
	Simulator::CnvAction act = action;
	if (!HundleAction(act, source, planetKey, pMission, nullptr, nullptr, nullptr))
		original_function(this, act, source, planetKey, pMission);
	else
		detoured(act, source, planetKey, pMission);
}

void HandleCivCommAction__detour::detoured(const Simulator::CnvAction& action, void* pSourceCiv, Simulator::cCity* pSourceCity, Simulator::cCity* pTargetCity)
{
	Simulator::CnvAction act = action;
	if (!HundleAction(act, 0, 0, nullptr, pSourceCiv, pSourceCity, pTargetCity))
		original_function(this, act, pSourceCiv, pSourceCity, pTargetCity);
	else
		detoured(act, pSourceCiv, pSourceCity, pTargetCity);
}