#pragma once
#include "stdafx.h"
#include "Spore/Simulator/SubSystem/CommManager.h"

member_detour(HandleSpaceCommAction__detour, Simulator::cCommManager, void(const Simulator::CnvAction&, uint32_t, Simulator::PlanetID, void*))
{
	void detoured(const Simulator::CnvAction & action, uint32_t source, Simulator::PlanetID planetKey, void* pMission);
};

member_detour(HandleCivCommAction__detour, Simulator::cCommManager, void(const Simulator::CnvAction&, void*, Simulator::cCity*, Simulator::cCity*))
{
	void detoured(const Simulator::CnvAction & action, void* pSourceCiv, Simulator::cCity * pSourceCity, Simulator::cCity * pTargetCity);
};