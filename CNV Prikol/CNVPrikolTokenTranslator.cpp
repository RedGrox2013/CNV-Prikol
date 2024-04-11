#include "stdafx.h"
#include "CNVPrikolTokenTranslator.h"
#include "CNVPrikolManager.h"

bool CNVPrikolTokenTranslator::TranslateToken(const char16_t* pToken, eastl::string16& dst)
{
	if (SOCIAL_CREDIT_TOKEN.compare(pToken) == 0) {
		if (!Simulator::IsSpaceGame())
			dst = u"你是白痴？？？ 這不是「太空」舞台！";
		else {
			uint32_t politicalID = Simulator::GetActiveStar()->GetPoliticalID();
			dst.sprintf(u"%d", PrikolManager.GetSocialCredit(politicalID));
		}

		return true;
	}

	return false;
}