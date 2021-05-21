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

class cfgVehicles{
	
	class ItemOptics;

	class ACOGOptic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[]={0.0, -0.005, 0.3, 0.01};
			PPLensProperties[]={0.5, 0.0, 0.0, 0.0};
		};
	};

	class PUScopeOptic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[]={0.0005, -0.005, 0.38, 0.007};
			PPLensProperties[]={0.5, 0.0, 0.0, 0.0};
		};
	};

	class KashtanOptic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[]={0.0, -0.005, 0.5, 0.01};
			PPLensProperties[]={0.5, 0.0, 0.0, 0.0};
		};
	};

	class HuntingOptic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[]={0.0, -0.05, 0.7, 0.05};
			PPLensProperties[]={0.3, 0.0, 0.0, 0.0};
		};
	};

	class PistolOptic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[]={0.001, -0.005, 0.42, 0.005};
			PPLensProperties[]={0.5, 0.0, 0.0, 0.0};
		};
	};

	class PSO1Optic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[]={0.0, -0.01, 0.31, 0.01};
			PPLensProperties[]={0.35, 0.0, 0.0, 0.0};
		};
	};

	class PSO11Optic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[]={0.0, -0.01, 0.31, 0.01};
			PPLensProperties[]={0.35, 0.0, 0.0, 0.0};
		};
	};

	class KazuarOptic: ItemOptics{
		class OpticsInfo{
			PPMaskProperties[]={0.0, 0.0, 2.0, 0.05};
			PPLensProperties[]={-1.0, 0.0, 0.0, 0.0};
		};
	};
};
