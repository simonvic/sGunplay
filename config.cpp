#define S_GUNPLAY

class CfgPatches {
	class sGunplay {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {
			"DZ_Weapons_Supports",
			"DZ_Weapons_Muzzles",
			"sFramework"
		};
	};
};

class CfgMods {
	class sGunplay {
		dir = "MyMODS/sGunplay";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "sGunplay";
		credits = "simonvic";
		author = "simonvic";
		authorID = "0";
		version = "0.1";
		extra = 0;
		type = "mod";
		
		dependencies[] = {
			"World",
			"Game",
			"Mission"
		};

		inputs = "MyMODS/sGunplay/scripts/data/inputs.xml";

		class defs {
			class imageSets{
				files[]={
					"MyMODS/sGunplay/GUI/imagesets/sGunplay_stats.imageset",
					"MyMODS/sGunplay/GUI/imagesets/sCrosshairs.imageset"
				};
			};
			class gameScriptModule {
				value = "";
				files[] = {
					"MyMODS/sGunplay/scripts/defines",
					"MyMODS/sGunplay/scripts/3_Game"
				};
			};
			class worldScriptModule {
				value = "";
				files[] = {
					"MyMODS/sGunplay/scripts/defines",
					"MyMODS/sGunplay/scripts/4_World"
				};
			};
			class missionScriptModule {
				value = "";
				files[] = {
					"MyMODS/sGunplay/scripts/defines",
					"MyMODS/sGunplay/scripts/5_Mission"
				};
			};
		};
	};
};

class Cfg_sUDE{
	class sGunplay{
		enabled = 1;
		class Gunplay {
			class Focus {
				speedReset = 0.2;
				speedErect = 0.6;
				speedCrouched = 0.4;
				speedProne = 0.1;
				speedMultiplierNoMagnification = 0.70;
				speedMultiplierIronsight = 0.75;
				releaseSpeed = 0.75;
			};
			class ADS {
				lensActivationDelayMS = -250;
				lensStrengthConstraints[] = {0, 4};
				hideClothingDelayMS = -200;
				fovReduction = 3;
				weaponInspectConstraintsDegree[] = {
					   10,
					-35, 35,
					   -5
				};
				resetSpeedInspection = 0.1;
				freelookConstraintsDegree[] = {
					   45,
					-45, 45,
					   -45
				};
				resetSpeedFreelook = 0.1;
				timeToADS = 0.4;
				timeFromADS = 0.3:
				time3rd = -0.2;
				timeBackupSight = 0.25;
				movementMisalignmentStrength = 2;
				movementMisalignmentFrequency = 1.15;
				movementMisalignmentSmoothness = 0.3;
			};
			class AimingModel {
				resetSpeedDeadzone = 0.3;
				resetSpeedWeaponInertia = 0.3;
				cameraFollowsBreathingSway = 0;
				class Filters {
					class FilterBase {
						enabled = 1;
					};
					class WeaponInertia : FilterBase{
						smoothness = 0.3;
						multiplierBase = 2;
						multiplierWeaponWeight = 3.5 * 0.0001;
						multiplierWeaponLength = 2;
						multiplierPlayerWeight = 0.45 * 0.0001;
						multiplierHipfire = 1.0;
						multiplierStanding = 1.0;
						multiplierWalking = 1.1;
						multiplierJogging = 1.75;
						multiplierErect = 1;
						multiplierCrouched = 0.5;
						multiplierProne = 0.75;
						minMultiplier = 1;
						maxMultiplier = 50;
						speedAcceleration[] = {0.5, 0.5};
						speedReset[] = {0.2, 0.2}; 
						speedAccelerationHipfire[] = {0.6, 0.6}; 
						speedResetHipfire[] = {0.3, 0.3}; 
						velocityLimit = 250;
					};
					class Movement : FilterBase{
						multiplier = 2;
						smoothTime = 0.4;
						strength[] = {
							2.5, 2.0,  //yaw strength, yaw frequency
							3.5, 7.5   //pitch strength, pitch frequency
						};
					};
					class Injury : FilterBase{
						multiplier = 1;
						strength[] = {
							15, 2,
							2, 0
						};
					};
					class WeaponInteraction : FilterBase{
						offsets[] = {-20, 10};
						smoothTime = 0.45;
					};
					class HipfireDeadzone : FilterBase{
						amountDegree[] = {
							   25,
							-25, 25,
							  -25
						};
					};
				};
				recoilHandsOffsetContribution[] = {0, 0};
			};
			class Sway {
				amplitude[] = {1.5, 2.8};
				frequency[] = {0.2, 0.7};
				multiplierErect = 1;
				multiplierCrouched = 0.3;
				multiplierProne = 0.1;
				decreaseFocusing = 4;
				decayPower = 8;
				minimum = 0.2;
			};
			class Recoil {
				handMultiplier = 1;
				reloadTimeMultiplier = 1;
				hipfireMultiplierH = 5;
				hipfireMultiplierV = 2;
				hipfireMultiplierReloadTime = 2;

			};
		};
		class DynamicCrosshair {
			precision = 50;
			smoothness = 0.05;
		};
	};	
};

class cfgVehicles{
	
	class ItemOptics;

	class ACOGOptic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[] = {0.0, 0.0, 0.3, 0.01};
			PPLensProperties[] = {0.5, 0.0, 0.0, 0.2};
		};
	};
	
	class ACOGOptic_6x: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[] = {0.0, 0.0, 0.2, 0.01};
			PPLensProperties[] = {0.5, 0.0, 0.0, 0.0};
		};
	};
	

	class PUScopeOptic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[] = {0.0, 0.0, 0.38, 0.007};
			PPLensProperties[] = {0.5, 0.0, 0.0, 0.2};
		};
	};

	class KashtanOptic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[] = {0.0, 0.0, 0.5, 0.01};
			PPLensProperties[] = {0.5, 0.0, 0.0, 0.2};
		};
	};

	class HuntingOptic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[] = {0.0, 0.0, 0.7, 0.05};
			PPLensProperties[] = {0.3, 0.0, 0.0, 0.3};
		};
	};

	class PistolOptic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[] = {0.0, 0.0, 0.42, 0.005};
			PPLensProperties[] = {0.5, 0.0, 0.0, 0.0};
		};
	};

	class PSO1Optic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[] = {0.0, 0.0, 0.31, 0.01};
			PPLensProperties[] = {0.35, 0.0, 0.0, 0.2};
		};
	};

	class PSO11Optic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[] = {0.0, 0.0, 0.31, 0.01};
			PPLensProperties[] = {0.35, 0.0, 0.0, 0.2};
		};
	};

	class KazuarOptic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[] = {0.0, 0.0, 2.0, 0.05};
			PPLensProperties[] = {-1.0, 0.0, 0.0, 0.0};
		};
	};

	class AugOptic : ItemOptics {
		class OpticsInfo {
			PPMaskProperties[] = {0.0, 0.0, 0.5, 0.01};
			PPLensProperties[] = {0.25, 0.0, 0.0, 0.1};
		};
	};

	class Static;
	class Inventory_Base : Static {
		s_mouse[] = {0.0, 0.0};
		s_hands[] = {0.0, 0.0};
		s_misalignment[] = {0.0, 0.0};
		s_kick = 0.0;
	};
	class M4_OEBttstck : Inventory_Base {
		s_hands[] = {0.45, 0.45};
		s_misalignment[] = {0.15, 0.25};
		s_kick = 0.70;
	};
	class M4_MPBttstck : Inventory_Base {
		s_hands[] = {0.50, 0.50};
		s_misalignment[] = {0.20, 0.30};
		s_kick = 0.72;
	};
	class M4_CQBBttstck : Inventory_Base {
		s_hands[] = {0.45, 0.45};
		s_misalignment[] = {0.25, 0.35};
		s_kick = 0.75;
	};
	class M4_RISHndgrd : Inventory_Base {
		s_hands[] = {0.25, 0.25};
		s_misalignment[] = {0.55, 0.50};
	};
	class M4_MPHndgrd : Inventory_Base {
		s_hands[] = {0.30, 0.30};
		s_misalignment[] = {0.60, 0.55};
	};
	class AK_WoodBttstck : Inventory_Base {
		s_hands[] = {0.25, 0.25};
		s_misalignment[] = {0.0, 0.25};
		s_kick = 0.75;
	};
	class AK_PlasticBttstck : Inventory_Base {
		s_hands[] = {0.25, 0.25};
		s_misalignment[] = {0.0, 0.25};
		s_kick = 0.75;
	};
	class AK_FoldingBttstck : Inventory_Base {
		s_hands[] = {0.25, 0.25};
		s_misalignment[] = {0.0, 0.25};
		s_kick = 0.75;
	};
	class AK_WoodHndgrd : Inventory_Base {
		s_hands[] = {0.25, 0.10};
		s_misalignment[] = {0.50, 0.50};
	};
	class AK_RailHndgrd : Inventory_Base {
		s_hands[] = {0.25, 0.10};
		s_misalignment[] = {0.50, 0.50};
	};
	class AKS74U_Bttstck : Inventory_Base {
		s_hands[] = {0.50, 0.50};
		s_misalignment[] = {0.20, 0.20};
		s_kick = 0.75;
	};
	class MP5k_StockBttstck : Inventory_Base {
		s_hands[] = {0.50, 0.50};
		s_misalignment[] = {0.0, 0.25};
		s_kick = 0.75;
	};
	class MP5_PlasticHndgrd : Inventory_Base {
		s_hands[] = {0.20, 0.20};
		s_misalignment[] = {0.50, 0.50};
	};
	class MP5_RailHndgrd : Inventory_Base {
		s_hands[] = {0.20, 0.20};
		s_misalignment[] = {0.50, 0.50};
	};
	class MP5_Compensator : Inventory_Base {
		s_misalignment[] = {0.45, 0.05};
	};
	class Mosin_Compensator : Inventory_Base {
		s_hands[] = {0.50, 0.30};
		s_misalignment[] = {0.50, 0.50};
	};
	class PP19_Bttstck : Inventory_Base {
		s_hands[] = {0.25, 0.25};
		s_misalignment[] = {0.0, 0.50};
		s_kick = 0.50;
	};
	class Saiga_Bttstck : Inventory_Base {
		s_hands[] = {0.30, 0.30};
		s_misalignment[] = {0.30, 0.30};
		s_kick = 0.75;
	};
	class Fal_OeBttstck : Inventory_Base {
		s_hands[] = {0.10, 0.50};
		s_misalignment[] = {0.50, 0.50};
		s_kick = 0.75;
	};
	class Fal_FoldingBttstck : Inventory_Base {
		s_hands[] = {0.00, 0.50};
		s_misalignment[] = {0.50, 0.50};
		s_kick = 0.75;
	};
	
};
