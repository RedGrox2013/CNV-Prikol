#include "stdafx.h"
#include "CustomAction.h"
#include <shellapi.h>
#include <Spore/Properties.h>

using namespace Simulator;

vector<uint32_t> CustomAction::_tributeEmpires;

CustomAction::CustomAction(const CnvAction& action)
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
	case CommActions::kCollectTribute:
		return true;
	default:
		return false;
	}
}

CnvAction CustomAction::GetAction() const { return _action; }
CnvAction CustomAction::GetNextAction() const { return _nextAction; }

void CustomAction::OpenUrl()
{
	char* url;
	if (!App::Property::GetCString8(_prop.get(), id("url"), url))
		url = "https://www.youtube.com/watch?v=dQw4w9WgXcQ";

	ShellExecuteA(NULL, "open", url, NULL, NULL, SW_SHOW);
}

void CustomAction::HandleCivCommAction(void* pSourceCiv, cCity* pSourceCity, cCity* pTargetCity)
{
	switch (_action.actionID)
	{
	case CommActions::kOpenUrl:
		OpenUrl();
		break;
	}
}

void CustomAction::HandleSpaceCommAction(uint32_t source, PlanetID planetKey, void* pMission)
{
	switch (_action.actionID)
	{
	case CommActions::kOpenUrl:
		OpenUrl();
		break;
	case CommActions::kCollectTribute:
		for (uint32_t i : _tributeEmpires)
			if (i == source) {
#ifdef _DEBUG
				App::ConsolePrintF("This empire has already paid tribute");
#endif
				return;
			}

		_tributeEmpires.push_back(source);
		RelationshipManager.ApplyRelationship(source, GetPlayerEmpireID(), kRelationshipEventInsult, 2);
		cEmpire* empire = StarManager.GetEmpire(source);
		if (empire->mEmpireMoney >= 10000)
			empire->mEmpireMoney -= 10000;
		
		break;
	}
}