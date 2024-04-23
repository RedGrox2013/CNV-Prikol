#pragma once
#include "stdafx.h"
#include <Spore\Simulator\ConversationResource.h>

enum CommActions : uint32_t
{
	kCnvCommDefault = 0xCAFF0F72,
	kCnvCloseComm = 0x01994745,
	kCnvCommEvent = 0x02D5DCEC,
	kCnvCityBuyAccepted = 0x8650BD5B,
	kCnvEndTradeRoute = 0x8A43C6D9,
	kCnvPeaceOffer1 = 0x9320DBBF,
	kCnvPeaceOffer2 = 0x9320DBBC,
	kCnvPeaceOffer3 = 0x9320DBBD,
	kCnvPeaceOffer4 = 0x9320DBBA,
	kCnvPeaceOffer5 = 0x9320DBBB,
	kCnvRelationshipWitholdTribute = 0x1A771205,
	kCnvRelationshipCommunicatedMean = 0x2125A82A,
	kCnvRelationshipAcceptGift = 0x52B8A79F,
	kCnvCityBuyAcceptedHigh = 0x6668560E,
	kCnvMission = 0x7B1F7D82,

	// Custom
	kCustonAction = id("kCustonAction"),
	kOpenUrl = id("kOpenUrl"),
	kCollectTribute = id("kCollectTribute"),
	kAddSocialCredit = id("kAddSocialCredit"),
	kSocialCreditEnd = id("kSocialCreditEnd")
};

class CustomAction
{
private:
	Simulator::CnvAction _action, _nextAction;
	PropertyListPtr _prop;
	static vector<uint32_t> _tributeEmpires;
	static uint32_t* _defaultCnvActions;
	static size_t _defaultCnvActionsCount;

	void OpenUrl();
public:
	CustomAction(const Simulator::CnvAction& action);

	bool IsCustom() const;
	Simulator::CnvAction GetAction() const;
	Simulator::CnvAction GetNextAction() const;

	void HandleCivCommAction(void* pSourceCiv, Simulator::cCity* pSourceCity, Simulator::cCity* pTargetCity);
	void HandleSpaceCommAction(uint32_t source, Simulator::PlanetID planetKey, void* pMission);
};

