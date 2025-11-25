#pragma once

namespace HFPF
{
	class DHavok :
		public IDriver,
		IConfig
	{
	public:
		static inline constexpr auto ID = DRIVER_ID::HAVOK;

		FN_NAMEPROC("HAVOK");
		FN_ESSENTIAL(false);
		FN_DRVDEF(6);

	private:
		virtual void LoadConfig() override;
		virtual void PostLoadConfig() override;
		virtual void RegisterHooks() override;
		virtual void Patch() override;
		virtual bool Prepare() override;
		virtual void OnGameConfigLoaded() override;

		static void PostConfigLoad(Event code, void* data);

		struct
		{
			bool untie_game_speed;
			bool fix_stuttering;
			bool fix_white_screen;
			bool fix_wind_speed;
			bool fix_rot_speed;
			bool fix_sit_rot_speed;
			bool fix_ws_rot_speed;
			bool fix_load_model;
			bool fix_stuck_anim;
			bool fix_responsive;
			bool fix_ocbp_speed;
		} m_conf;

		struct
		{
			float* fLoadingModel_TriggerZoomSpeed{ nullptr };
			float* fLoadingModel_MouseToRotateSpeed{ nullptr };
		} m_gv;

		void Patch_FixStuttering();
		void Patch_FixWindSpeed();
		void Patch_FixRotationSpeed();
		void Patch_FixSittingRotation();
		void Patch_FixWSRotation();
		void Patch_FixLoadModelSpeed1();
		void Patch_FixLoadModelSpeed2();
		void Patch_FixStuck();

		inline static DWORD_PTR ft4handle;

		static inline std::int32_t                    Magic1 = 0x426b4b44;  //58.8235
		static inline std::int32_t                    Magic2 = 0xc26b4b44;  //-58.8235
		inline static REL::Relocation<std::uintptr_t> Untie{ AID::Untie, Offsets::Untie };
		inline static REL::Relocation<std::uintptr_t> FixStuttering1{ AID::FixStuttering1, Offsets::FixStuttering1 };
		inline static REL::Relocation<std::uintptr_t> FixStuttering2{ AID::FixStuttering2, Offsets::FixStuttering2 };
		inline static REL::Relocation<std::uintptr_t> FixStuttering3{ AID::FixStuttering1, Offsets::FixStuttering3 };
		inline static REL::Relocation<std::uintptr_t> FixObjectsTransfer{ AID::ObjectsTransfer };
		inline static REL::Relocation<std::uintptr_t> FixWhiteScreen{ AID::FixWhiteScreen, Offsets::FixWhiteScreen };
		inline static REL::Relocation<std::uintptr_t> FixWindSpeed1{ AID::FixWindSpeed1, Offsets::FixWindSpeed1 };
		inline static REL::Relocation<std::uintptr_t> FixWindSpeed2{ AID::FixWindSpeed2, Offsets::FixWindSpeed2 };
		inline static REL::Relocation<std::uintptr_t> FixWindSpeed3{ AID::FixWindSpeed2, Offsets::FixWindSpeed3 };
		inline static REL::Relocation<std::uintptr_t> FixWindSpeed4{ AID::FixWindSpeed2, Offsets::FixWindSpeed4 };
		inline static REL::Relocation<std::uintptr_t> FixRotationSpeed{ AID::FixRotationSpeed, Offsets::FixRotationSpeed };
		inline static REL::Relocation<std::uintptr_t> FixLockpickRotation{ AID::FixLockpickRotation, Offsets::FixLockpickRotation };
		inline static REL::Relocation<std::uintptr_t> FixWSRotationSpeed{ AID::FixWSRotationSpeed, Offsets::FixWSRotationSpeed };
		inline static REL::Relocation<std::uintptr_t> FixRepeateRate{ AID::FixRepeateRate, Offsets::FixRepeateRate };
		inline static REL::Relocation<std::uintptr_t> FixLeftTriggerZoomSpeed{ AID::FixTriggerZoomSpeed, Offsets::FixLeftTriggerZoomSpeed };
		inline static REL::Relocation<std::uintptr_t> FixRightTriggerZoomSpeed{ AID::FixTriggerZoomSpeed, Offsets::FixRightTriggerZoomSpeed };
		inline static REL::Relocation<std::uintptr_t> FixLoadScreenRotationSpeedUp{ AID::FixRepeateRate, Offsets::FixLoadScreenRotationSpeedUp };
		inline static REL::Relocation<std::uintptr_t> FixLoadScreenRotationSpeedDown{ AID::FixRepeateRate, Offsets::FixLoadScreenRotationSpeedDown };
		inline static REL::Relocation<std::uintptr_t> FixLoadScreenRotationSpeedLeft{ AID::FixRepeateRate, Offsets::FixLoadScreenRotationSpeedLeft };
		inline static REL::Relocation<std::uintptr_t> FixLoadScreenRotationSpeedRight{ AID::FixRepeateRate, Offsets::FixLoadScreenRotationSpeedRight };
		inline static REL::Relocation<std::uintptr_t> FixLoadScreenRotationSpeed{ AID::FixLoadScreenRotationSpeed, Offsets::FixLoadScreenRotationSpeed };
		inline static REL::Relocation<std::uintptr_t> FixStuckAnim{ AID::FixStuckAnim, Offsets::FixStuckAnim };
		inline static REL::Relocation<std::uintptr_t> FixMotionFeedback{ AID::FixMotionFeedback, Offsets::FixMotionFeedback };
		inline static REL::Relocation<std::uintptr_t> FixSittingRotationX{ AID::FixSittingRotationX, Offsets::FixSittingRotationX };
		inline static REL::Relocation<std::uintptr_t> FixSittingRotationY{ AID::FixSittingRotationX, Offsets::FixSittingRotationY };
		inline static REL::Relocation<std::uintptr_t> CalculateOCBP{ AID::CalculateOCBP };

		void* TrampHook64(void* src, void* dst, int len)
		{
			if (len < 14)
				return nullptr;
			BYTE stub[14] = {
				0xFF, 0x25, 0x00, 0x00, 0x00, 0x00,             // jmp qword ptr instruction
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // 8 byte ptr to jmp destination
			};

			void* pTrampoline = VirtualAlloc(0, len + sizeof(stub), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

			DWORD oldProtect = 0;
			VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &oldProtect);

			uintptr_t jmpBackAddr = (uintptr_t)src + len;

			// copy trampoline jmpback addr to stub
			memcpy(stub + 6, &jmpBackAddr, 8);
			// copy stolen bytes to trampoline
			memcpy((void*)(pTrampoline), src, len);
			// copy stub to trampoline
			memcpy((void*)((uintptr_t)pTrampoline + len), stub, sizeof(stub));

			// copy dst to the stub, creating our jmp to our hook function
			memcpy(stub + 6, &dst, 8);
			// copy new stub to src
			memcpy(src, stub, sizeof(stub));

			// nop any stolen bytes in src
			for (int i = 14; i < len; i++) {
				*(BYTE*)((uintptr_t)src + i) = 0x90;
			}

			VirtualProtect(src, len, oldProtect, &oldProtect);
			return (void*)(pTrampoline);
		}

		static DHavok m_Instance;
	};

}
