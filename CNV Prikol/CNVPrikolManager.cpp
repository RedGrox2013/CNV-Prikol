#include "stdafx.h"
#include "CNVPrikolManager.h"
#include "SaveListener.h"
#include <Shlobj.h>
#include <Spore/Properties.h>

CNVPrikolManager CNVPrikolManager::_instance;

void CNVPrikolManager::Initialize()
{
	PropManager.GetGlobalPropertyList(id("CNVPrikolConfig"), _config);
	App::Property::GetBool(_config.get(), id("debugMode"), _debugMode);

	SaveListenerPtr saveListener = new SaveListener();
	MessageManager.AddListener(saveListener.get(), Simulator::kMsgSaveGame);
	MessageManager.AddListener(saveListener.get(), App::kMsgOnModeEnter);
}

int32_t CNVPrikolManager::GetSocialCredit(uint32_t politicalID)
{
	for (auto& sc : _data)
		if (sc->politicalID == politicalID)
			return sc->socialCredit;

	return 0;
}

void CNVPrikolManager::AddSocialCredit(const uint32_t& politicalID, const int32_t& socialCredit)
{
	_socialCreditAddend = socialCredit;
	for (auto& sc : _data)
		if (sc->politicalID == politicalID) {
			sc->socialCredit += socialCredit;
			return;
		}

	PrikolRecordPtr record = new PrikolRecord(politicalID, socialCredit);
	_data.push_back(record);
}

inline const string16 CNVPrikolManager::GetSavePath()
{
	PWSTR appdata;
	SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE, NULL, &appdata);
	string16 savePath = (char16_t*)appdata;
	savePath += u"\\Spore\\Games\\Game0\\PrikolSave__" +
		Simulator::GetPlayerEmpire()->GetHomeStarRecord()->mName + u".cnvprikol";

	return savePath;
}

void CNVPrikolManager::SaveSpaceData()
{
	size_t size = _data.size();
	if (!Simulator::IsSpaceGame() || size == 0)
		return;

	auto path = GetSavePath();
	FileStreamPtr stream = new IO::FileStream(path.c_str());
	stream->Open(IO::AccessFlags::Write, IO::CD::CreateAlways);

	IO::WriteInt32(stream.get(), &PrikolRecord::VERSION);
	IO::WriteUInt32(stream.get(), &size);
	for (auto& record : _data) {
		IO::WriteUInt32(stream.get(), &record->politicalID);
		IO::WriteInt32(stream.get(), &record->socialCredit);
		IO::WriteBool8(stream.get(), &record->storyStarted);
	}

	stream->Close();
}

void CNVPrikolManager::LoadSpaceData()
{
	if (!Simulator::IsSpaceGame())
		return;

	_data.clear();
	auto path = GetSavePath();
	FileStreamPtr stream = new IO::FileStream(path.c_str());
	if (!stream->Open(IO::AccessFlags::Read, IO::CD::OpenExisting)) {
		if (_debugMode)
			ShowDebugInfo(PrikolManagerDebugInfo::LoadFailed);
		return;
	}

	int32_t version;
	IO::ReadInt32(stream.get(), &version);
	if (version == 1) {
		stream->Close();
		return;
	}

	size_t size;
	IO::ReadUInt32(stream.get(), &size);
	for (size_t i = 0; i < size; ++i) {
		PrikolRecordPtr record = new PrikolRecord();
		IO::ReadUInt32(stream.get(), &record->politicalID);
		IO::ReadInt32(stream.get(), &record->socialCredit);
		IO::ReadBool8(stream.get(), record->storyStarted);
		_data.push_back(record);
	}

	stream->Close();

	if (_debugMode)
		ShowDebugInfo(PrikolManagerDebugInfo::LoadData);
}

void CNVPrikolManager::ShowDebugInfo(PrikolManagerDebugInfo info)
{
	switch (info)
	{
	case PrikolManagerDebugInfo::LoadData:
		App::ConsolePrintF("Load CNV Prikol save...\nSocial credit:");
		for (auto& credit : _data)
			App::ConsolePrintF("Political ID: %d; social credit: %d",
				credit->politicalID, credit->socialCredit);
		break;
	}
}

void CNVPrikolManager::ClearSocialCredit(uint32_t politicalID)
{
	for (auto& i : _data)
		if (i->politicalID == politicalID)
			i->socialCredit = 0;
}

void CNVPrikolManager::ShowThanksForPlaying() const
{
	bool show = false;
	App::Property::GetBool(_config.get(), id("showThanksForPlaying"), show);
	if (show)
		HintManager.ShowHint(id("CNVPrikolThanksForPlaying"));
}

void CNVPrikolManager::SetStoryStarted(uint32_t politicalID, bool value)
{
	for (auto& record : _data)
		if (record->politicalID == politicalID)
			record->storyStarted = value;

	PrikolRecordPtr record = new PrikolRecord(politicalID);
	record->storyStarted = value;
	_data.push_back(record);
}