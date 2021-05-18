modded class SUserConfig{
		
	static SUserConfigGunplay gunplay(bool reload = false){
		getInstance().load(SUserConfigGunplay, reload);
		return SUserConfigGunplay.Cast(getInstance().modulesConfigs.Get(SUserConfigGunplay));
	}
	

}