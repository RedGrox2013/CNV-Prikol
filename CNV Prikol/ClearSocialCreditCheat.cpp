#include "stdafx.h"
#include "ClearSocialCreditCheat.h"
#include "CNVPrikolManager.h"

ClearSocialCreditCheat::ClearSocialCreditCheat()
{
}


ClearSocialCreditCheat::~ClearSocialCreditCheat()
{
}


void ClearSocialCreditCheat::ParseLine(const ArgScript::Line& line)
{
	auto planet = Simulator::GetActivePlanet();
	if (!planet) {
		App::ConsolePrintF("No active planet");
		return;
	}

	auto empire = planet->GetEmpire();
	if (!empire) {
		App::ConsolePrintF("%ls has no empire", planet->mpPlanetRecord->mName);
		return;
	}

	PrikolManager.ClearSocialCredit(empire->GetEmpireID());
	App::ConsolePrintF("Social credit has been successfully cleared!");
}

const char* ClearSocialCreditCheat::GetDescription(ArgScript::DescriptionMode mode) const
{
	if (mode == ArgScript::DescriptionMode::Basic) {
		return "This cheat clears the social credit from the CNV Prikol mod.";
	}
	else {
		return "This cheat clears the social credit from the CNV Prikol mod.\n"
			"To clear the social credit, you must fly to a planet that has an empire and use this cheat.";
	}
}
