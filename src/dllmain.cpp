#include "PCH.h"

void MessageHandler(F4SE::MessagingInterface::Message* a_message)
{
	switch (a_message->type) {
	case F4SE::MessagingInterface::kPostPostLoad:
		{
			HFPF::IDDispatcher::InitializeDriversPost();
		}
		break;
	case F4SE::MessagingInterface::kGameDataReady:
		{
			HFPF::DWindow::SetupForceMinimizeMP();
			HFPF::DRender::Register();
		}
		break;
	case F4SE::MessagingInterface::kNewGame:
		{
			HFPF::DMisc::SetThreadsNG();
		}
		break;
	default:
		break;
	}
}

void InitializeLog()
{
	auto path = logger::log_directory();
	if (!path) {
		stl::report_and_fail("Failed to find standard logging directory"sv);
	}

	*path /= Version::PROJECT;
	*path += ".log"sv;
	auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);

	auto log = std::make_shared<spdlog::logger>("global log"s, std::move(sink));

	log->set_level(spdlog::level::info);
	log->flush_on(spdlog::level::info);

	spdlog::set_default_logger(std::move(log));
	spdlog::set_pattern("[%H:%M:%S:%e][%l] %v"s);

	logger::info(FMT_STRING("{} v{}"), Version::PROJECT, Version::NAME);
}

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Query(const F4SE::QueryInterface* a_f4se, F4SE::PluginInfo* a_info)
{
	a_info->infoVersion = F4SE::PluginInfo::kVersion;
	a_info->name = Version::PROJECT.data();
	a_info->version = Version::MAJOR;

	return true;
}

extern "C" DLLEXPORT bool F4SEAPI F4SEPlugin_Load(const F4SE::LoadInterface* a_f4se)
{
	F4SE::Init(a_f4se);
	F4SE::AllocTrampoline(1 << 12);

	const auto ver = a_f4se->RuntimeVersion();

	logger::info("Game version : {}", ver.string());

	if (ver < F4SE::RUNTIME_1_10_130) {
		logger::critical(FMT_STRING("Unsupported runtime version {}"), ver.string());
		return false;
	}
	const auto messaging = F4SE::GetMessagingInterface();
	messaging->RegisterListener(MessageHandler);
	int result1 = HFPF::IConfig::LoadConfiguration();
	if (result1 != 0) {
		logger::warn("Unable to load HighFPSPhysicsFix.ini file. Line: ({})", result1);
	}

	if (HFPF::IConfig::IsCustomLoaded()) {
		logger::info("Custom configuration loaded");
	}
	if (!HFPF::IEvents::Initialize()) {
		return 1;
	}
	if (!HFPF::IDDispatcher::InitializeDrivers()) {
		return -1;
	}
	HFPF::IConfig::ClearConfiguration();
	return true;
}
