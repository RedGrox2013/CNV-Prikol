#pragma once
#include "stdafx.h"
#include "SocialCredit.h"

#define PrikolManager (*CNVPrikolManager::Get())

class CNVPrikolManager
{
private:
	static CNVPrikolManager _instance;

	vector<SocialCredit> _socialCredit;

	CNVPrikolManager();

	static inline const string16 GetSavePath();

public:
	static CNVPrikolManager* Get();

	int32_t GetSocialCredit(uint32_t politicalID);
	void AddSocialCredit(SocialCredit credit);

	void SaveSpaceData();
	void LoadSpaceData();
};

