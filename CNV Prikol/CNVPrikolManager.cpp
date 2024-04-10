#include "stdafx.h"
#include "CNVPrikolManager.h"
#include <Shlobj.h>
#include <Spore/Properties.h>

CNVPrikolManager CNVPrikolManager::_instance;

CNVPrikolManager::CNVPrikolManager()
{
	PropManager.GetGlobalPropertyList(id("CNVPrikolConfig"), _config);
	App::Property::GetBool(_config.get(), id("debugMode"), _debugMode);
}

int32_t CNVPrikolManager::GetSocialCredit(uint32_t politicalID)
{
	for (auto sc : _socialCredit)
		if (sc.politicalID == politicalID)
			return sc.point;

	return 0;
}

void CNVPrikolManager::AddSocialCredit(SocialCredit credit)
{
	for (auto sc : _socialCredit)
		if (sc.politicalID == credit.politicalID) {
			sc.point += credit.point;
			return;
		}

	_socialCredit.push_back(credit);
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
	if (!Simulator::IsSpaceGame() || _socialCredit.size() == 0)
		return;

	auto path = GetSavePath();
	FileStreamPtr stream = new IO::FileStream(path.c_str());
	stream->Open(IO::AccessFlags::Write, IO::CD::CreateAlways);
	SaveSocialCredit(stream);

	stream->Close();
}

void CNVPrikolManager::LoadSpaceData()
{
	if (!Simulator::IsSpaceGame())
		return;

	_socialCredit.clear();
	auto path = GetSavePath();
	FileStreamPtr stream = new IO::FileStream(path.c_str());
	if (!stream->Open(IO::AccessFlags::Read, IO::CD::OpenExisting)) {
		if (_debugMode)
			ShowDebugInfo(PrikolManagerDebugInfo::LoadFailed);
		return;
	}

	size_t size;
	IO::ReadUInt32(stream.get(), &size);
	for (size_t i = 0; i < size; ++i) {
		SocialCredit credit{};
		IO::ReadInt32(stream.get(), &credit.point);
		IO::ReadUInt32(stream.get(), &credit.politicalID);
		_socialCredit.push_back(credit);
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
		for (auto credit : _socialCredit)
			App::ConsolePrintF("Political ID: %d; social credit: %d",
				credit.politicalID, credit.point);
		break;
	}
}

inline void CNVPrikolManager::SaveSocialCredit(FileStreamPtr stream)
{
	size_t size = _socialCredit.size();
	if (size == 0)
		return;

	IO::WriteUInt32(stream.get(), &size);
	for (auto sc : _socialCredit) {
		IO::WriteInt32(stream.get(), &sc.point);
		IO::WriteUInt32(stream.get(), &sc.politicalID);
	}
}