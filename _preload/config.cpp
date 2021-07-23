class CfgPatches {
	class sGunplay_preload {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {};
	};
};

class CfgMods {
	class sGunplay_preload {

		type = "mod";
		
		dependencies[] = {
			"World",
			"Game",
			"Mission"
		};

		class defs {
			class engineScriptModule{
				value = "";
				files[] = { 
					"MyMODS/sGunplay/_preload/defines"
				};
			};
			class gameLibScriptModule{
				value = "";
				files[] = {
					"MyMODS/sGunplay/_preload/defines"
				};
			};
			class gameScriptModule {
				value = "";
				files[] = {
					"MyMODS/sGunplay/_preload/defines",
					"MyMODS/sGunplay/_preload/scripts/3_Game"
				};
			};
			class worldScriptModule {
				value = "";
				files[] = {
					"MyMODS/sGunplay/_preload/defines",
					"MyMODS/sGunplay/_preload/scripts/4_World"
				};
			};
			class missionScriptModule {
				value = "";
				files[] = {
					"MyMODS/sGunplay/_preload/defines"
				};
			};
		};
	};
};
