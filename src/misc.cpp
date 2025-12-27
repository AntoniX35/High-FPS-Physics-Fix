#include "PCH.h"
#include <TlHelp32.h>
namespace HFPF
{
	static constexpr const char* SECTION_MAIN = "Main";
	static constexpr const char* CKEY_DISABLEBLACKLOADING = "DisableBlackLoadingScreens";
	static constexpr const char* CKEY_DISABLELOADING = "DisableAnimationOnLoadingScreens";
	static constexpr const char* CKEY_POSTLOADINGSPEED = "PostloadingMenuSpeed";

	static constexpr const char* SECTION_LIMITER = "Limiter";
	static constexpr const char* CKEY_ONETHREADWHILELOADNG = "OneThreadWhileLoading";

	static constexpr const char* SECTION_FIXES = "Fixes";
	static constexpr const char* CKEY_FIXTHREADS = "FixCPUThreads";

	static constexpr const char* SECTION_MISC = "Miscellaneous";
	static constexpr const char* CKEY_DISABLE_ACTOR_FADE = "DisableActorFade";
	static constexpr const char* CKEY_DISABLE_PLAYER_FADE = "DisablePlayerFade";

	DMisc DMisc::m_Instance;

	DMisc::DMisc()
	{
	}

	void DMisc::LoadConfig()
	{
		m_conf.one_thread = GetConfigValue(SECTION_LIMITER, CKEY_ONETHREADWHILELOADNG, true);
		m_conf.disable_black_loading = GetConfigValue(SECTION_MAIN, CKEY_DISABLEBLACKLOADING, false);
		m_conf.disable_loading_screens = GetConfigValue(SECTION_MAIN, CKEY_DISABLELOADING, false);
		m_conf.post_loading_speed = GetConfigValue(SECTION_MAIN, CKEY_POSTLOADINGSPEED, 1.0f);
		m_conf.fix_cpu_threads = GetConfigValue(SECTION_FIXES, CKEY_FIXTHREADS, true);
		m_conf.disable_actor_fade = GetConfigValue(SECTION_MISC, CKEY_DISABLE_ACTOR_FADE, false);
		m_conf.disable_player_fade = GetConfigValue(SECTION_MISC, CKEY_DISABLE_PLAYER_FADE, false);
	}

	void DMisc::PostLoadConfig()
	{
	}

	void DMisc::Patch()
	{
		if (m_conf.disable_black_loading) {
			REL::safe_write(
				BlackLoadingScreensAddress.address(),
				reinterpret_cast<const void*>(Payloads::disable_blackloading_patch),
				sizeof(Payloads::disable_blackloading_patch));
		}
		if (m_conf.disable_loading_screens) {
			REL::safe_write(
				LoadingScreensAddress.address(),
				reinterpret_cast<const void*>(Payloads::NOP4),
				sizeof(Payloads::NOP4));
		}
		if (m_conf.post_loading_speed != 1.0f) {
			{
				struct PostLoadPatch : Xbyak::CodeGenerator
				{
					PostLoadPatch(std::uintptr_t a_hookTarget, float* a_value, std::uintptr_t a_frameTimer)
					{
						Xbyak::Label retnLabel;
						Xbyak::Label timerLabel;
						Xbyak::Label valueLabel;

						movss(xmm0, dword[rip + valueLabel]);
						mov(rcx, ptr[rip + timerLabel]);
						mulss(xmm0, dword[rcx]);

						jmp(ptr[rip + retnLabel]);

						L(retnLabel);
						dq(a_hookTarget + 0x8);

						L(timerLabel);
						dq(a_frameTimer);

						L(valueLabel);
						db(reinterpret_cast<Xbyak::uint8*>(a_value), sizeof(float));
					}
				};
				logger::info("[Miscellaneous] [Patch] [Postloading menu speed] patching...");
				{
					PostLoadPatch code(PostLoadInjectAddress.address(), &m_conf.post_loading_speed, Game::g_frameTimer.address());
					code.ready();

					auto& trampoline = F4SE::GetTrampoline();
					trampoline.write_branch<5>(
						PostLoadInjectAddress.address(),
						trampoline.allocate(code));
				}
				REL::safe_write(PostLoadInjectAddress.address() + 0x5, &Payloads::NOP3, 0x3);
				logger::info("[Miscellaneous] [Patch] [Postloading menu speed] OK");
			}
		}

		auto rd = IDDispatcher::GetDriver<DRender>();
		if (!rd->IsOK()) {
			logger::warn("[Miscellaneous] Render driver unavailable, FixCPUThreads disabling");
			m_conf.fix_cpu_threads = false;
		}

		if (m_conf.fix_cpu_threads) {
			REL::safe_write(PresentThreadBlockAddress.address(),
				reinterpret_cast<const void*>(Payloads::loading_patch),
				sizeof(Payloads::loading_patch));

			timing = IPerfCounter::Query();
			auto& trampoline = F4SE::GetTrampoline();
			trampoline.write_call<5>(Present.address(), reinterpret_cast<std::uintptr_t>(ThreadWait));
			m_conf.max_wait_time = static_cast<long long>((1.0L / 60.0L) * 1000000.0L);
		}

		if (m_conf.disable_actor_fade) {
			REL::safe_write(ActorFade_a.address(), &Payloads::JMP8, sizeof(Payloads::JMP8));

			logger::info("[Miscellaneous] Actor fade patch applied");
		}

		if (m_conf.disable_player_fade) {
			REL::safe_write(PlayerFade_a.address(), &Payloads::player_fade_jmp, sizeof(Payloads::player_fade_jmp));
			logger::info("[Miscellaneous] Player fade patch applied");
		}

		if (m_conf.one_thread) {
			Patch_SetThreadsNG();
		}
	}

	int32_t GetCurrentThreadCount()
	{
		DWORD  procId = GetCurrentProcessId();
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

		PROCESSENTRY32 entry = { 0 };
		entry.dwSize = sizeof(entry);

		BOOL procFound = true;
		procFound = Process32First(snapshot, &entry);
		while (procFound && entry.th32ProcessID != procId)
			procFound = Process32Next(snapshot, &entry);
		CloseHandle(snapshot);

		if (procFound)
			return entry.cntThreads;

		return -1;
	}

	void DMisc::RegisterHooks()
	{
	}

	bool DMisc::Prepare()
	{
		return true;
	}

	// Tries to make sure all the threads are finished before waiting for Vsync
	// Vsync will block all threads immediately on completion of the draw (which is very quickly on a modern PC).
	// Unless a 60fPS VSync comes first, then let it go.
	void DMisc::ThreadWait()
	{
		long long wait_time_us = 0;
		while (SwitchToThread()) {
			wait_time_us = m_Instance.m_conf.max_wait_time - IPerfCounter::delta_us(m_Instance.timing, IPerfCounter::Query());

			if (wait_time_us <= 0)
				break;

			_mm_pause();
		}

		m_Instance.timing = IPerfCounter::Query() + wait_time_us;
	}

	void DMisc::Patch_SetThreadsNG()
	{
		hProcess = GetCurrentProcess();
		if (!hProcess) {
			m_Instance.m_conf.one_thread = false;
			logger::error("[Miscellaneous] Process Fallout4.exe not found. If the errors continues, set OneThreadWhileLoading=false.");
		}
		if (GetProcessAffinityMask(hProcess, &nMaxProcessMaskAfterLoad, &dwSystemAffinity)) {
			logger::info("[Miscellaneous] Process Affinity Mask: {}, System Affinity Mask: {}", nMaxProcessMaskAfterLoad, dwSystemAffinity);
		} else {
			logger::error("[Miscellaneous] Error retrieving affinity mask: {}", ::GetLastError());
		}

		nMaxProcessMaskNG = 0x1;
	}

	void DMisc::SetThreadsNG()
	{
		if (m_Instance.m_conf.one_thread) {
			LimitThreads = true;
			SetProcessAffinityMask(hProcess, nMaxProcessMaskNG);
		}
	}

	void DMisc::ReturnThreadsNG()
	{
		LimitThreads = false;
		SetProcessAffinityMask(hProcess, nMaxProcessMaskAfterLoad);
	}
}
