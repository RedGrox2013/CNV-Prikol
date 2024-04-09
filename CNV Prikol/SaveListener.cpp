#include "stdafx.h"
#include "SaveListener.h"
#include "CNVPrikolManager.h"

SaveListener::SaveListener()
{
}


SaveListener::~SaveListener()
{
}

// For internal use, do not modify.
int SaveListener::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int SaveListener::Release()
{
	return DefaultRefCounted::Release();
}


// The method that receives the message. The first thing you should do is checking what ID sent this message...
bool SaveListener::HandleMessage(uint32_t messageID, void* message)
{
	if (messageID == Simulator::kMsgSaveGame) {
		PrikolManager.SaveSpaceData();
		return true;
	}
	if (messageID == App::kMsgOnModeEnter) {
		PrikolManager.LoadSpaceData();
		return true;
	}
	
	return false;
}
