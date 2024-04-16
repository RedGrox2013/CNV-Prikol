#pragma once
#include "stdafx.h"
#include "PrikolRecord.h"

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
	vector<PrikolRecordPtr> _data;
	int32_t _socialCreditAddend;

	CNVPrikolManager() : _debugMode(false), _socialCreditAddend(0) {}

	static inline const string16 GetSavePath();

public:
	static CNVPrikolManager* Get() { return &_instance; }

	void Initialize();

	const bool DebugMode() const { return _debugMode; }

	int32_t GetSocialCredit(uint32_t politicalID);
	void AddSocialCredit(const uint32_t& politicalID, const int32_t& socialCredit);
	int32_t GetSocialCreditAddend() const { return _socialCreditAddend; }

	void SaveSpaceData();
	void LoadSpaceData();

	void ShowDebugInfo(PrikolManagerDebugInfo info);

	void ClearSocialCredit(uint32_t politicalID);
};
