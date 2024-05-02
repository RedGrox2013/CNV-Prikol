#pragma once
#include "stdafx.h"

#define PrikolRecordPtr intrusive_ptr<PrikolRecord>

struct PrikolRecord
	: public DefaultRefCounted
{
public:
	PrikolRecord() : PrikolRecord(0) { }
	PrikolRecord(uint32_t politicalID, int32_t socialCredit = 0)
		: politicalID(politicalID), socialCredit(socialCredit), storyStarted(false) { }

	static const int32_t VERSION = 2;

	uint32_t politicalID;
	int32_t socialCredit;
	bool storyStarted;

	int AddRef() override { return DefaultRefCounted::AddRef(); }
	int Release() override { return DefaultRefCounted::Release(); }
};