class CfgPatches {
	class sGunplay {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {
			"sVisual"
		};
	};
};

class CfgMods {
	class sGunplay {
		dir = "sGunplay";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "MyMODS/sGunplay";
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
			class gameScriptModule {
				value = "";
				files[] = {"MyMODS/sGunplay/scripts/3_Game"};
			};
			class worldScriptModule {
				value = "";
				files[] = {"MyMODS/sGunplay/scripts/4_World"};
			};
			class missionScriptModule {
				value = "";
				files[] = {"MyMODS/sGunplay/scripts/5_Mission"};
			};
		};
	};
};

class Cfg_sUDE{
	class Gunplay{
		enabled = 1;
	};
};

class CfgVehicles {
	
		
	//================================OPTICS================================
	class ItemOptics;
	class PUScopeOptic: ItemOptics {
		class OpticsInfo {
			memoryPointCamera = "eyeScope";
			cameraDir = "cameraDir";
			modelOptics = "-";
			opticsDisablePeripherialVision = 0.67000002;
			opticsFlare = 1;
			opticsPPEffects[] = {
				"OpticsCHAbera3",
				"OpticsBlur1"
			};
			opticsZoomMin = "0.3926/3.5";
			opticsZoomMax = "0.3926/3.5";
			opticsZoomInit = "0.3926/3.5";
			distanceZoomMin = 100;
			distanceZoomMax = 1300;
			discreteDistance[] = {
				100,
				200,
				300,
				400,
				500,
				600,
				700,
				800,
				900,
				1000,
				1100,
				1200,
				1300
			};
			discreteDistanceInitIndex = 0;
			PPMaskProperties[] = {
				0.5,
				0.5,
				0.325,
				0.050000001
			};
			PPLensProperties[] = {
				0.5,
				0.15000001,
				0,
				0
			};
			PPBlurProperties = 0.60000002;
		};
	};
	class PistolOptic: ItemOptics {
		class OpticsInfo {
			memoryPointCamera = "eyeScope";
			cameraDir = "cameraDir";
			modelOptics = "-";
			opticsDisablePeripherialVision = 0.67000002;
			opticsFlare = 1;
			opticsPPEffects[] = {
				"OpticsCHAbera5",
				"OpticsBlur1"
			};
			opticsZoomMin = "0.3926/1.8";
			opticsZoomMax = "0.3926/1.8";
			opticsZoomInit = "0.3926/1.8";
			distanceZoomMin = 50;
			distanceZoomMax = 150;
			discreteDistance[] = {
				50,
				100,
				150
			};
			discreteDistanceInitIndex = 0;
			PPMaskProperties[] = {
				0.5,
				0.5,
				0.4,
				0.050000001
			};
			PPLensProperties[] = {
				0.5,
				0.5000001,
				0,
				0
			};
			PPBlurProperties = 0.2;
		};
	};
	class ACOGOptic: ItemOptics {
		class OpticsInfo {
			memoryPointCamera = "eyeScope";
			cameraDir = "cameraDir";
			modelOptics = "-";
			opticsDisablePeripherialVision = 0.67000002;
			opticsFlare = 1;
			opticsPPEffects[] = {};
			opticsZoomMin = "0.3926/4";
			opticsZoomMax = "0.3926/4";
			opticsZoomInit = "0.3926/4";
			distanceZoomMin = 100;
			distanceZoomMax = 600;
			discreteDistance[] = {
				100,
				200,
				300,
				400,
				500,
				600
			};
			discreteDistanceInitIndex = 0;
			PPMaskProperties[] = {
				0.5,
				0.5,
				0.3,
				0.050000001
			};
			PPLensProperties[] = {
				0.5,
				0.15000001,
				0,
				0
			};
			PPBlurProperties = 0.60000002;
		};
	};
	class PSO1Optic: ItemOptics {
		class OpticsInfo {
			memoryPointCamera = "eyeScope";
			cameraDir = "cameraDir";
			modelOptics = "-";
			opticsDisablePeripherialVision = 0.67000002;
			opticsFlare = 1;
			opticsPPEffects[] = {
				"OpticsCHAbera5",
				"OpticsBlur3"
			};
			opticSightTexture = "dz\weapons\attachments\optics\data\reticle_pso1glow_ca.paa";
			opticSightMaterial = "dz\weapons\attachments\optics\data\tritium.rvmat";
			opticsZoomMin = "0.3926/4";
			opticsZoomMax = "0.3926/4";
			opticsZoomInit = "0.3926/4";
			distanceZoomMin = 100;
			distanceZoomMax = 1000;
			discreteDistance[] = {
				100,
				200,
				300,
				400,
				500,
				600,
				700,
				800,
				900,
				1000
			};
			discreteDistanceInitIndex = 0;
			PPMaskProperties[] = {
				0.5,
				0.5,
				0.3,
				0.05
			};
			PPLensProperties[] = {
				0.5,
				0.15000001,
				0,
				0
			};
			PPBlurProperties = 0.60000002;
		};
	};
	class PSO11Optic: ItemOptics {
		class OpticsInfo {
			memoryPointCamera = "eyeScope";
			cameraDir = "cameraDir";
			modelOptics = "-";
			opticsDisablePeripherialVision = 0.67000002;
			opticsFlare = 1;
			opticsPPEffects[] = {
				"OpticsCHAbera5",
				"OpticsBlur3"
			};
			opticSightTexture = "dz\weapons\attachments\optics\data\reticle_pso11glow_ca.paa";
			opticSightMaterial = "dz\weapons\attachments\optics\data\tritium.rvmat";
			opticsZoomMin = "0.3926/4";
			opticsZoomMax = "0.3926/4";
			opticsZoomInit = "0.3926/4";
			distanceZoomMin = 100;
			distanceZoomMax = 1000;
			discreteDistance[] = {
				100,
				200,
				300,
				400,
				500,
				600,
				700,
				800,
				900,
				1000
			};
			discreteDistanceInitIndex = 0;
			PPMaskProperties[] = {
				0.5,
				0.5,
				0.3,
				0.05
			};
			PPLensProperties[] = {
				0.5,
				0.15000001,
				0,
				0
			};
			PPBlurProperties = 0.60000002;
		};
	};
	class HuntingOptic: ItemOptics {
		class OpticsInfo {
			memoryPointCamera = "eyeScope";
			cameraDir = "cameraDir";
			useModelOptics = 1;
			modelOptics = "\DZ\weapons\attachments\optics\opticview_longrange.p3d";
			preloadOpticType = "Preload2DOptic_Longrange";
			opticsDisablePeripherialVision = 0.67000002;
			opticsFlare = 1;
			opticsPPEffects[] = {
				"OpticsCHAbera3",
				"OpticsBlur1"
			};
			opticsZoomMin = "0.3926/4";
			opticsZoomMax = "0.3926/12";
			opticsZoomInit = "0.3926/4";
			discretefov[] = {
				"0.3926/4",
				"0.3926/8",
				"0.3926/12"
			};
			discreteInitIndex = 0;
			distanceZoomMin = 100;
			distanceZoomMax = 1000;
			discreteDistance[] = {
				200,
				300,
				400,
				500,
				600,
				700,
				800
			};
			discreteDistanceInitIndex = 0;
			PPMaskProperties[] = {
				0.5,
				0.5,
				0.5,
				0.1
			};
			PPLensProperties[] = {
				0.30000001,
				0.15000001,
				0,
				0
			};
			PPBlurProperties = 0.30000001;
		};
	};
	class KashtanOptic: ItemOptics {
		class OpticsInfo {
			memoryPointCamera = "eyeScope";
			cameraDir = "cameraDir";
			modelOptics = "-";
			opticsDisablePeripherialVision = 0.67000002;
			opticsFlare = 1;
			opticsPPEffects[] = {
				"OpticsCHAbera3",
				"OpticsBlur1"
			};
			opticsZoomMin = "0.3926/2.8";
			opticsZoomMax = "0.3926/2.8";
			opticsZoomInit = "0.3926/2.8";
			distanceZoomMin = 200;
			distanceZoomMax = 200;
			discreteDistance[] = {
				200
			};
			discreteDistanceInitIndex = 0;
			PPMaskProperties[] = {
				0.5,
				0.5,
				0.45,
				0.050000001
			};
			PPLensProperties[] = {
				0.5,
				0.15000001,
				0,
				0
			};
			PPBlurProperties = 0.2;
		};
	};
};