#include "stdafx.h"
#include "CNVPrikolTokenTranslator.h"
#include "CNVPrikolManager.h"

bool CNVPrikolTokenTranslator::TranslateToken(const char16_t* pToken, eastl::string16& dst)
{
	switch (id(pToken))
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

		PropertyListPtr prop;
		if (PropManager.GetPropertyList(captainKey.instanceID, 0x4062e500, prop))
			App::Property::GetString16(prop.get(), id("editorModelNameOverride"), dst);
		else {
			cAssetMetadataPtr metadata;
			Pollinator::GetMetadata(captainKey.instanceID, captainKey.groupID, metadata);
			dst = metadata->GetName();
		}
	}
	return true;
	default:
		return false;
	};
}