modded class SUserConfigConstraints{
	
	static SUserConfigConstraints_Gunplay gunplay(bool reload = false){
		getInstance().load(SUserConfigConstraints_Gunplay, reload);
		return SUserConfigConstraints_Gunplay.Cast(getInstance().getLoadedModules().Get(SUserConfigConstraints_Gunplay));
	}
	
}

modded class SyncSUserConfigConstraintsRPC {
	override void onSetup(ParamsWriteContext ctx) {
		ctx.Write(SUserConfigConstraints.gunplay());
		super.onSetup(ctx);
	}
}