#include "stdafx.h"
#include "CNVPrikolTokenTranslator.h"
#include "CNVPrikolManager.h"

bool CNVPrikolTokenTranslator::TranslateToken(const char16_t* pToken, eastl::string16& dst)
{
	uint32_t tokenHash = id(pToken);
	switch (tokenHash)
	{
	case id(u"social_credit"):
		if (!Simulator::IsSpaceGame())
			dst = u"你是白痴？？？ 這不是「太空」舞台！";
		else {
			uint32_t politicalID = Simulator::GetActivePlanet()->GetEmpire()->GetEmpireID();
			dst.sprintf(u"%d", PrikolManager.GetSocialCredit(politicalID));
		}

		return true;
	case id(u"social_credit_addend"):
	{
		auto addend = PrikolManager.GetSocialCreditAddend();
		dst.sprintf(addend >= 0 ? u"+%d" : u"%d", addend);
	}
	return true;
	case id(u"cnv_prikol_captain_name"):
	{
		ResourceKey captainKey;
		auto empire = Simulator::GetPlayerEmpire();
		if (Simulator::IsSpaceGame())
			captainKey = empire->mCaptainKey;
		else {
			captainKey = GameNounManager.GetAvatar()->mSpeciesKey;
		}

		dst = GetCaptainName(captainKey);
	}
	return true;
	case id(u"cnv_prikol_mission_planet"):
		dst = Simulator::GetActivePlanet()->mpPlanetRecord->mName;
		return true;
	case id(u"cnv_prikol_posse_member_0"):
	case id(u"cnv_prikol_posse_member_1"):
	case id(u"cnv_prikol_posse_member_2"):
	{
		if (!Simulator::IsScenarioMode()) {
			dst = u"";
			return true;
		}

		auto& scenarioRes = ScenarioMode.GetData()->mpResource;
		if (scenarioRes->mInitialPosseMembers.empty())
			dst = u"";
		else if (tokenHash == id(u"cnv_prikol_posse_member_0"))
			dst = GetCaptainName(scenarioRes->mInitialPosseMembers[0].mAsset.mKey);
		else if (tokenHash == id(u"cnv_prikol_posse_member_1"))
			dst = GetCaptainName(scenarioRes->mInitialPosseMembers[1].mAsset.mKey);
		else if (tokenHash == id(u"cnv_prikol_posse_member_2"))
			dst = GetCaptainName(scenarioRes->mInitialPosseMembers[2].mAsset.mKey);
	}
	return true;
	default:
		return false;
	};
}

string16 CNVPrikolTokenTranslator::GetCaptainName(ResourceKey captainKey)
{
	PropertyListPtr prop;
	if (PropManager.GetPropertyList(captainKey.instanceID, 0x4062e500, prop)) {
		string16 name;
		if (App::Property::GetString16(prop.get(), id("editorModelNameOverride"), name))
			return name;
	}

	cAssetMetadataPtr metadata;
	Pollinator::GetMetadata(captainKey.instanceID, captainKey.groupID, metadata);
	return metadata->GetName();
}