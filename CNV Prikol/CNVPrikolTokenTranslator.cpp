#include "stdafx.h"
#include "CNVPrikolTokenTranslator.h"
#include "CNVPrikolManager.h"

bool CNVPrikolTokenTranslator::TranslateToken(const char16_t* pToken, eastl::string16& dst)
{
	uint32_t tokenID = id(pToken);
	if (id(u"social_credit") == tokenID/*SOCIAL_CREDIT_TOKEN.compare(pToken) == 0*/) {
		if (!Simulator::IsSpaceGame())
			dst = u"你是白痴？？？ 這不是「太空」舞台！";
		else {
			uint32_t politicalID = Simulator::GetActivePlanet()->GetEmpire()->GetEmpireID();
			dst.sprintf(u"%d", PrikolManager.GetSocialCredit(politicalID));
		}

		return true;
	}
	if (id(u"social_credit_addend") == tokenID) {
		auto addend = PrikolManager.GetSocialCreditAddend();
		dst.sprintf(addend >= 0 ? u"+%d" : u"%d", addend);
		return true;
	}

	return false;
}