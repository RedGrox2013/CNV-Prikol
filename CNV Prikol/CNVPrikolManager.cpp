#include "stdafx.h"
#include "CNVPrikolManager.h"
#include <Shlobj.h>

CNVPrikolManager CNVPrikolManager::_instance;

CNVPrikolManager::CNVPrikolManager() { }

CNVPrikolManager* CNVPrikolManager::Get() { return &_instance; }

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
	size_t size = _socialCredit.size();
	if (size == 0 || !Simulator::IsSpaceGame())
		return;

	auto path = GetSavePath();
	FileStreamPtr stream = new IO::FileStream(path.c_str());
	stream->Open(IO::AccessFlags::Write, IO::CD::CreateAlways);
	IO::WriteUInt32(stream.get(), &size);
	for (auto sc : _socialCredit) {
		IO::WriteInt32(stream.get(), &sc.point);
		IO::WriteUInt32(stream.get(), &sc.politicalID);
	}

	stream->Close();
}

void CNVPrikolManager::LoadSpaceData()
{
	if (!Simulator::IsSpaceGame())
		return;

#ifdef _DEBUG
	App::ConsolePrintF("Load CNV Prikol save...\nSocial credit:");
#endif // _DEBUG


	_socialCredit.clear();
	auto path = GetSavePath();
	FileStreamPtr stream = new IO::FileStream(path.c_str());
	if (!stream->Open(IO::AccessFlags::Read, IO::CD::OpenExisting))
		return;

	size_t size;
	IO::ReadUInt32(stream.get(), &size);
	for (size_t i = 0; i < size; ++i) {
		SocialCredit credit{};
		IO::ReadInt32(stream.get(), &credit.point);
		IO::ReadUInt32(stream.get(), &credit.politicalID);
		_socialCredit.push_back(credit);

#ifdef _DEBUG
		App::ConsolePrintF("Political ID: %d; social credit: %d",
			credit.politicalID, credit.point);
#endif // _DEBUG
	}

	stream->Close();
}