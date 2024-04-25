#pragma once
#include <Spore/App/ITokenTranslator.h>

class CNVPrikolTokenTranslator : public App::ITokenTranslator
{
private:
	string16 GetCaptainName(ResourceKey captainKey);

public:
	bool TranslateToken(const char16_t* pToken, eastl::string16& dst) override;
};

