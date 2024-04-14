#pragma once
#include "stdafx.h"
#include <Spore\Simulator\ConversationResource.h>

enum CommActions : uint32_t
{
	kCnvCommDefault = 0xCAFF0F72,
	kCnvCloseComm = 0x01994745,
	kCnvCommEvent = 0x02D5DCEC,

	// Custom
	kCustonAction = id("kCustonAction"),
	kOpenUrl = id("kOpenUrl"),
	kCollectTribute = id("kCollectTribute"),
	kAddSocialCredit = id("kAddSocialCredit")
};

class CustomAction
{
private:
	Simulator::CnvAction _action, _nextAction;
	PropertyListPtr _prop;
	static vector<uint32_t> _tributeEmpires;

	void OpenUrl();
public:
	CustomAction(const Simulator::CnvAction& action);

	bool IsCustom() const;
	Simulator::CnvAction GetAction() const;
	Simulator::CnvAction GetNextAction() const;

	void HandleCivCommAction(void* pSourceCiv, Simulator::cCity* pSourceCity, Simulator::cCity* pTargetCity);
	void HandleSpaceCommAction(uint32_t source, Simulator::PlanetID planetKey, void* pMission);
};

