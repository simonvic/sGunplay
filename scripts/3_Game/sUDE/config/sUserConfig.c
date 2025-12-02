modded class SUserConfig {
		
	static SUserConfigGunplay gunplay(bool reload = false) {
		getInstance().load(SUserConfigGunplay, reload);
		return SUserConfigGunplay.Cast(getInstance().getLoadedModules().Get(SUserConfigGunplay));
	}
	
	override void onPreload() {
		super.onPreload();
		SUserConfig.gunplay();
	}

	override void onConstraintsReceived(ParamsReadContext ctx) {
		super.onConstraintsReceived(ctx);
		SUserConfigConstraints_Gunplay constraints;
		if (!ctx.Read(constraints)) {
			SLOG.c(""+this, "Can't read constraints, ignoring...");
			return;
		}
		gunplay().applyConstraints(constraints);
	}

}
