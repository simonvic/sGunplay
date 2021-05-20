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
