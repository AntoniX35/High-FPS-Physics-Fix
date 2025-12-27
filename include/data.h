#pragma once

namespace HFPF
{
	namespace AID
	{
		constexpr REL::ID FPS_Cap_Patch1(133902);
		constexpr REL::ID PresentThread(700869);
		constexpr REL::ID FullScreen_Patch1(1547437);
		constexpr REL::ID ResizeBuffers(212827);
		constexpr REL::ID ResizeTarget(796949);
		constexpr REL::ID D3D11Create(224250);
		constexpr REL::ID CreateWindowEx_a(193854);
		constexpr REL::ID Upscale(288964);
		constexpr REL::ID Untie(462873);
		constexpr REL::ID BlackLoadingScreens(991513);
		constexpr REL::ID LoadingScreens(132841);
		constexpr REL::ID PostLoadInject(1289136);
		constexpr REL::ID FixStuttering1(12890);
		constexpr REL::ID FixStuttering2(1395106);
		constexpr REL::ID FixWhiteScreen(703643);
		constexpr REL::ID FixWindSpeed1(1469635);
		constexpr REL::ID FixWindSpeed2(1164603);
		constexpr REL::ID FixRotationSpeed(457276);
		constexpr REL::ID FixLockpickRotation(676000);
		constexpr REL::ID FixWSRotationSpeed(1144472);
		constexpr REL::ID FixRepeateRate(618896);
		constexpr REL::ID FixTriggerZoomSpeed(629736);
		constexpr REL::ID FixLoadScreenRotationSpeed(22234);
		constexpr REL::ID FixStuckAnim(463133);
		constexpr REL::ID FixMotionFeedback(1201084);
		constexpr REL::ID FixSittingRotationX(533372);
		constexpr REL::ID ActorFade(295466);
		constexpr REL::ID PlayerFade(202079);
		constexpr REL::ID BudgetGame(759508);
		constexpr REL::ID BudgetUI(1343068);
		constexpr REL::ID Budget(890788);
		constexpr REL::ID LoadPluginINI_C(1266784);
		constexpr REL::ID CalculateOCBP(212702);
		constexpr REL::ID FrameTimer(922988);
		constexpr REL::ID ExtInt(359440);
		constexpr REL::ID ObjectsTransfer(754666);
		constexpr REL::ID Write_iLocationX(719782);
	}

	namespace Offsets
	{
		static inline constexpr std::uintptr_t FPS_Cap_Patch1 = 0xAA;                    //Fallout4.exe+0x00D423BA
		static inline constexpr std::uintptr_t FPS_Cap_Patch2 = 0xB3;                    //Fallout4.exe+0x00D423C3
		static inline constexpr std::uintptr_t PresentThreadBlock = 0x30;                //Fallout4.exe+0x01D0B6A0
		static inline constexpr std::uintptr_t Borderless_Patch = 0x5C;                  //Fallout4.exe+0x00D4236C
		static inline constexpr std::uintptr_t FullScreen_Patch1 = 0xD0;                 //Fallout4.exe+0x00CAAC70
		static inline constexpr std::uintptr_t FullScreen_Patch3 = 0x101;                //Fallout4.exe+0x00CAACA1
		static inline constexpr std::uintptr_t Screen_Patch = 0x51;                      //Fallout4.exe+0x00D42361
		static inline constexpr std::uintptr_t MovRaxRcx = 0x1B5;                        //Fallout4.exe+0x01D0ADB5
		static inline constexpr std::uintptr_t ResizeBuffersDisable = 0x27;              //Fallout4.exe+0x01D0AC27
		static inline constexpr std::uintptr_t ResizeTargetDisable = 0x25;               //Fallout4.exe+0x01D0AEB5
		static inline constexpr std::uintptr_t ResizeBuffers = 0x1A0;                    //Fallout4.exe+0x01D0ADA0
		static inline constexpr std::uintptr_t ResizeTarget = 0x119;                     //Fallout4.exe+0x01D0AFA9
		static inline constexpr std::uintptr_t CreateDXGIFactory = 0x2B;                 //Fallout4.exe+0x01D1748B
		static inline constexpr std::uintptr_t D3D11CreateDeviceAndSwapChain = 0x419;    //Fallout4.exe+0x01D17879
		static inline constexpr std::uintptr_t CreateWindowEx_a = 0x187;                 //Fallout4.exe+0x01D17F97
		static inline constexpr std::uintptr_t BlackLoadingScreens = 0x116;              //Fallout4.exe+0x01297076
		static inline constexpr std::uintptr_t LoadingScreens = 0x19D;                   //Fallout4.exe+0x00CBFFCD
		static inline constexpr std::uintptr_t PostLoadInject = 0x2B;                    //Fallout4.exe+0x0126D75B
		static inline constexpr std::uintptr_t BethesdaVsync = 0x332;                    //Fallout4.exe+0x01D17792
		static inline constexpr std::uintptr_t PresentInject = 0x48;                     //Fallout4.exe+0x01D0B6B8
		static inline constexpr std::uintptr_t Untie = 0x6B;                             //Fallout4.exe+0x01B1393B
		static inline constexpr std::uintptr_t FixStuttering1 = 0x196;                   //Fallout4.exe+0x01D6EB96
		static inline constexpr std::uintptr_t FixStuttering2 = 0x1A1;                   //Fallout4.exe+0x01D6EDA1
		static inline constexpr std::uintptr_t FixStuttering3 = 0x145;                   //Fallout4.exe+0x01D6EB45
		static inline constexpr std::uintptr_t FixWhiteScreen = 0x13;                    //Fallout4.exe+0x0172A893
		static inline constexpr std::uintptr_t FixWindSpeed1 = 0x21;                     //Fallout4.exe+0x01DCF701
		static inline constexpr std::uintptr_t FixWindSpeed2 = 0x9E;                     //Fallout4.exe+0x01D6F84E
		static inline constexpr std::uintptr_t FixWindSpeed3 = 0x147;                    //Fallout4.exe+0x01D6F8F7
		static inline constexpr std::uintptr_t FixWindSpeed4 = 0x32B;                    //Fallout4.exe+0x01D6FADB
		static inline constexpr std::uintptr_t FixRotationSpeed = 0xE1;                  //Fallout4.exe+0x00F49621
		static inline constexpr std::uintptr_t FixLockpickRotation = 0x42;               //Fallout4.exe+0x0129CA32
		static inline constexpr std::uintptr_t FixWSRotationSpeed = 0xA2;                //Fallout4.exe+0x002182B2
		static inline constexpr std::uintptr_t FixRepeateRate = 0x354;                   //Fallout4.exe+0x01297474
		static inline constexpr std::uintptr_t FixLeftTriggerZoomSpeed = 0xFF;           //Fallout4.exe+0x0129786F
		static inline constexpr std::uintptr_t FixRightTriggerZoomSpeed = 0x163;         //Fallout4.exe+0x012978D3
		static inline constexpr std::uintptr_t FixLoadScreenRotationSpeedUp = 0x46C;     //Fallout4.exe+0x0129758C
		static inline constexpr std::uintptr_t FixLoadScreenRotationSpeedDown = 0x4C6;   //Fallout4.exe+0x012975E6
		static inline constexpr std::uintptr_t FixLoadScreenRotationSpeedLeft = 0x51F;   //Fallout4.exe+0x0129763F
		static inline constexpr std::uintptr_t FixLoadScreenRotationSpeedRight = 0x584;  //Fallout4.exe+0x012976A4
		static inline constexpr std::uintptr_t FixLoadScreenRotationSpeed = 0xBF;        //Fallout4.exe+0x01298D0F
		static inline constexpr std::uintptr_t FixStuckAnim = 0xA9;                      //Fallout4.exe+0x0252E789
		static inline constexpr std::uintptr_t FixMotionFeedback = 0x9F7;                //Fallout4.exe+0x002844F7
		static inline constexpr std::uintptr_t FixSittingRotationX = 0xC0;               //Fallout4.exe+0x012446D0
		static inline constexpr std::uintptr_t FixSittingRotationY = 0xD7;               //Fallout4.exe+0x012446E7
		static inline constexpr std::uintptr_t Upscale = 0x1BE;                          //Fallout4.exe+0x01D0B5DE
		static inline constexpr std::uintptr_t ActorFade = 0x663;                        //Fallout4.exe+0x00823793
		static inline constexpr std::uintptr_t PlayerFade = 0x162;                       //Fallout4.exe+0x0124C732
		static inline constexpr std::uintptr_t iSizeW = 0x69;                            //Fallout4.exe+0x00D42379
		static inline constexpr std::uintptr_t iSizeH = 0x78;                            //Fallout4.exe+0x00D42388
		static inline constexpr std::uintptr_t BudgetGame = 0x3C;                        //Fallout4.exe+0x0137218C
		static inline constexpr std::uintptr_t BudgetUI = 0xB4;                          //Fallout4.exe+0x01372494
		static inline constexpr std::uintptr_t Budget = 0xB4;                            //Fallout4.exe+0x013725A4
		static inline constexpr std::uintptr_t LoadPluginINI_C = 0xEE;                   //Fallout4.exe+0x00D41D9E
		static inline constexpr std::uintptr_t Write_iLocationX = 0x269;                 //Fallout4.exe+0x00D403F9
		static inline constexpr std::uintptr_t Write_iLocationY = 0x2A4;                 //Fallout4.exe+0x00D40434
	}

	namespace Payloads
	{
		static inline constexpr std::uint8_t JMP8 = { 0xEB };
		static inline constexpr std::uint8_t INT3 = { 0xCC };
		static inline constexpr std::uint8_t NOP = { 0x90 };
		static inline constexpr std::uint8_t NOP2[] = { 0x66, 0x90 };
		static inline constexpr std::uint8_t NOP3[] = { 0x0F, 0x1F, 0x00 };
		static inline constexpr std::uint8_t NOP4[] = { 0x0F, 0x1F, 0x40, 0x00 };
		static inline constexpr std::uint8_t NOP5[] = { 0x0F, 0x1F, 0x44, 0x00, 0x00 };
		static inline constexpr std::uint8_t NOP6[] = { 0x66, 0x0F, 0x1F, 0x44, 0x00, 0x00 };
		static inline constexpr std::uint8_t NOP8[] = { 0x0F, 0x1F, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00 };

		static inline constexpr std::uint8_t loading_patch[] = { 0xF2, 0x48, 0x90, 0xF2, 0x48, 0x90, 0xF2, 0x48, 0x90, 0x90 };
		static inline constexpr std::uint8_t screen_patch[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0x90, 0x90 };
		static inline constexpr std::uint8_t fullscreen1_patch[] = { 0x41, 0x80, 0xFB, 0x01, 0x90, 0x90, 0x90 };
		static inline constexpr std::uint8_t fullscreenJMP_patch[] = { 0xEB, 0x18 };
		static inline constexpr std::uint8_t fullscreenNOP_patch[] = { 0x90, 0x90 };
		static inline constexpr std::uint8_t untie_patch[] = { 0x00 };
		static inline constexpr std::uint8_t ifpsclamp_patch[] = { 0x38 };
		static inline constexpr std::uint8_t disable_blackloading_patch[] = { 0xEB };
		static inline constexpr std::uint8_t ResizeBuffersDisable[] = { 0xE9, 0x46, 0x02, 0x00, 0x00, 0x90 };
		static inline constexpr std::uint8_t ResizeTargetDisable[] = { 0xE9, 0x4F, 0x01, 0x00, 0x00, 0x90 };
		static inline constexpr std::uint8_t res_patch[] = { 0xB8, 0x00, 0x00, 0x00, 0x00, 0x90 };

		static inline constexpr std::uint8_t SkipNoINI[] = { 0x48, 0x8B, 0xCF };

		static inline constexpr std::uint8_t player_fade_jmp[] = { 0xEB, 0x6F, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90 };
	}
}
