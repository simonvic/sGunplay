modded class SUserConfigConstraints {
	
	static SUserConfigConstraints_Gunplay gunplay(bool reload = false) {
		return SUserConfigConstraints_Gunplay.Cast(getInstance().load(SUserConfigConstraints_Gunplay, reload));
	}

	override void onPreload() {
		super.onPreload();
		SUserConfigConstraints.gunplay();
	}
	
}

modded class SyncSUserConfigConstraintsRPC {
	override void onSetup(ParamsWriteContext ctx) {
		super.onSetup(ctx);
		ctx.Write(SUserConfigConstraints.gunplay());
	}
}