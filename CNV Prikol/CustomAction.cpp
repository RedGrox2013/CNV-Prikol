#include "stdafx.h"
#include "CustomAction.h"
#include <shellapi.h>
#include <Spore/Properties.h>
#include "CNVPrikolManager.h"
#include <Spore/App/cAppSystem.h>

using namespace Simulator;

#define Prop App::Property

vector<uint32_t> CustomAction::_tributeEmpires;
uint32_t* CustomAction::_defaultCnvActions;
size_t CustomAction::_defaultCnvActionsCount;

CustomAction::CustomAction(const CnvAction& action)
	: _action(action)
{
	if (!IsCustom())
		return;

	if (!PropManager.GetPropertyList(action.key.instanceID, action.key.groupID, _prop))
		PropManager.GetPropertyList(id("CustomActionTemplate"), id("CustomCnvActions"), _prop);

	Prop::GetUInt32(_prop.get(), id("nextAction"), _nextAction.actionID);
	if (!Prop::GetKey(_prop.get(), id("actionKey"), _nextAction.key))
		_nextAction.actionID = CommActions::kCnvCommDefault;
}

bool CustomAction::IsCustom() const
{
	if (!_defaultCnvActions)
		Prop::GetArrayUInt32(PrikolManager.GetPropertyList(),
			id("defaultCnvActions"), _defaultCnvActionsCount, _defaultCnvActions);

	for (size_t i = 0; i < _defaultCnvActionsCount; i++)
		if (_defaultCnvActions[i] == _action.actionID)
			return false;

	return true;
}

CnvAction CustomAction::GetAction() const { return _action; }
CnvAction CustomAction::GetNextAction() const { return _nextAction; }

void CustomAction::OpenUrl()
{
	char16_t* url;
	if (!App::Property::GetCString16(_prop.get(), id("url"), url))
		url = u"https://www.youtube.com/watch?v=dQw4w9WgXcQ";

	AppSystem.OpenURL(url);
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
	{
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

	}
		break;
	case CommActions::kAddSocialCredit:
	{
		int32_t socialCredit;
		if (!Prop::GetInt32(_prop.get(), id("socialCreditAddend"), socialCredit))
			socialCredit = PrikolManager.GetSocialCreditAddend();
		PrikolManager.AddSocialCredit(source, socialCredit);
	}
		break;
	case CommActions::kSocialCreditEnd:
	{
		ResourceKey key(0, 0x055ADA24, id("Prikol_socialCredit"));
		_nextAction.actionID = CommActions::kCnvCommEvent;
		if (PrikolManager.GetSocialCredit(source) <= 0)
			key.instanceID = id("social_credit_lose");
		else
			key.instanceID = id("social_credit_win");
		_nextAction.key = key;
	}
		break;
	}
}