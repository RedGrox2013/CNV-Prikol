#pragma once
#include <Spore/App/ITokenTranslator.h>

class CNVPrikolTokenTranslator : public App::ITokenTranslator
{
private:
	const string16 SOCIAL_CREDIT_TOKEN = u"social_credit";

public:
	bool TranslateToken(const char16_t* pToken, eastl::string16& dst) override;
};

