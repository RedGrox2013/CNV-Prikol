#include "stdafx.h"
#include "ConversationsDetours.h"
#include "CustomAction.h"

void HandleSpaceCommAction__detour::detoured(const Simulator::CnvAction& action, uint32_t source, Simulator::PlanetID planetKey, void* pMission)
{
	CustomAction act(action);
	while (act.IsCustom()) {
		act.HandleSpaceCommAction(source, planetKey, pMission);
		act = act.GetNextAction();
	}

	original_function(this, act.GetAction(), source, planetKey, pMission);
}

void HandleCivCommAction__detour::detoured(const Simulator::CnvAction& action, void* pSourceCiv, Simulator::cCity* pSourceCity, Simulator::cCity* pTargetCity)
{
	CustomAction act(action);
	while (act.IsCustom()) {
		act.HandleCivCommAction(pSourceCiv, pSourceCity, pTargetCity);
		act = act.GetNextAction();
	}

	original_function(this, act.GetAction(), pSourceCiv, pSourceCity, pTargetCity);
}