#pragma once
#include "stdafx.h"
#include "SocialCredit.h"

#define PrikolManager (*CNVPrikolManager::Get())

enum PrikolManagerDebugInfo
{
	LoadData,
	LoadFailed
};

class CNVPrikolManager
{
private:
	static CNVPrikolManager _instance;
	PropertyListPtr _config;
	bool _debugMode;
	vector<SocialCredit> _socialCredit;

	CNVPrikolManager();

	static inline const string16 GetSavePath();
	inline void SaveSocialCredit(FileStreamPtr stream);

public:
	static CNVPrikolManager* Get() { return &_instance; }

	int32_t GetSocialCredit(uint32_t politicalID);
	void AddSocialCredit(SocialCredit credit);

	void SaveSpaceData();
	void LoadSpaceData();

	void ShowDebugInfo(PrikolManagerDebugInfo info);
};
