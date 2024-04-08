#include "stdafx.h"
#include "CustomAction.h"
#include <shellapi.h>
#include <Spore/Properties.h>

CustomAction::CustomAction(const Simulator::CnvAction& action)
	: _action(action)
{
	if (!IsCustom())
		return;

	if (!PropManager.GetPropertyList(action.key.instanceID, action.key.groupID, _prop))
		PropManager.GetPropertyList(id("CustomActionTemplate"), id("CustomCnvActions"), _prop);

	App::Property::GetUInt32(_prop.get(), id("nextAction"), _nextAction.actionID);
	App::Property::GetKey(_prop.get(), id("actionKey"), _nextAction.key);
}

bool CustomAction::IsCustom() const
{
	switch (_action.actionID)
	{
	case CommActions::kCustonAction:
	case CommActions::kOpenUrl:
		return true;
	default:
		return false;
	}
}

Simulator::CnvAction CustomAction::GetAction() const { return _action; }
Simulator::CnvAction CustomAction::GetNextAction() const { return _nextAction; }

void CustomAction::OpenUrl()
{
	char* url;
	if (!App::Property::GetCString8(_prop.get(), id("url"), url))
		url = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";

	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOW);
}

void CustomAction::HandleCivCommAction(void* pSourceCiv, Simulator::cCity* pSourceCity, Simulator::cCity* pTargetCity)
{
	switch (_action.actionID)
	{
	case CommActions::kOpenUrl:
		OpenUrl();
		break;
	}
}

void CustomAction::HandleSpaceCommAction(uint32_t source, Simulator::PlanetID planetKey, void* pMission)
{
	switch (_action.actionID)
	{
	case CommActions::kOpenUrl:
		OpenUrl();
		break;
	}
}