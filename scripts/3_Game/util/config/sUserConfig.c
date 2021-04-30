modded class SUserConfig{
		
	SUserConfigGunplay gunplay(bool reload = false){
		load(SUserConfigGunplay, reload);
		return SUserConfigGunplay.Cast(modulesConfigs.Get(SUserConfigGunplay));
	}

}