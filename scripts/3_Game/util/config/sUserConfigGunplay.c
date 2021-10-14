class SUserConfigGunplay : SUserConfigBase{

	override string getPath(){
		return "$saves:\\sUDE\\config\\sGunplay.json";
	}
	
	override string getDefaultPath(){
		return "$profile:\\sUDE\\config\\sGunplay_default.json";
	}
	
	override void deserialize(string data, out string error){
		auto cfg = this;
		getSerializer().ReadFromString(cfg, data, error);
	}

	override string serialize(){
		string result;
		auto cfg = this;
		getSerializer().WriteToString(cfg, true, result);
		return result;
	}
	
	override string serializeDefault(){
		string result;
		auto cfg = new SUserConfigGunplay();
		getSerializer().WriteToString(cfg, true, result);
		return result;
	}
		
	///////////////////////////////////////
	// these go in json
	protected float adsDOFIntensity = 0.0;
	protected bool hideWeaponBarrelInOptic = false;
	protected bool hideClothingInOptic = true;
	protected float lensZoomStrength = 0.75;
	//protected float deadzoneLimits[4] = { 0.0, 0.0, 0.0, 0.0 };
	protected ref TFloatArray deadzoneLimits = { 0.0, 0.0, 0.0, 0.0 };
	protected bool resetDeadzoneOnFocus = true;
	protected bool showDynamicCrosshair = true;
	///////////////////////////////////////
	
	override void registerOptions() {
		super.registerOptions();
		registerOption("adsDOFIntensity",         new SUCOption_ADSDOFIntensity(adsDOFIntensity));
		registerOption("hideWeaponBarrelInOptic", new SUCOption_HideWeaponBarrelInOptic(hideWeaponBarrelInOptic));
		registerOption("hideClothingInOptic",     new SUCOption_HideClothingInOptic(hideClothingInOptic));
		registerOption("lensZoomStrength",        new SUCOption_LensZoomStrength(lensZoomStrength));
		registerOption("deadzoneLimits",          new SUCOption_DeadzoneLimits(deadzoneLimits));
		registerOption("resetDeadzoneOnFocus",    new SUCOption_ResetDeadzonOnFocus(resetDeadzoneOnFocus));
		registerOption("showDynamicCrosshair",    new SUCOption_ShowDynamicCrosshair(showDynamicCrosshair));		
	}
	
	override void onConstraintsReceive(ParamsReadContext ctx) {
		super.onConstraintsReceive(ctx);
		
		SUserConfigConstraints_Gunplay constraints;
		if (!ctx.Read(constraints)) {
			SLog.c("Can't read constraints, ignoring...",""+this);
			return;
		}
		
		SLog.i("Got constraints from server!",""+this);
		applyConstraints(constraints);
	}
	
	override void applyConstraints(SUserConfigConstraintsBase constraints) {
		SUserConfigConstraints_Gunplay c = SUserConfigConstraints_Gunplay.Cast(constraints);
		if (!c) return;
		
		getOption("adsDOFIntensity").setConstraint(c.getADSDOFIntensity());
		getOption("hideWeaponBarrelInOptic").setConstraint(c.getHideWeaponBarrelInOptic());
		getOption("hideClothingInOptic").setConstraint(c.getHideClothingInOptic());
		getOption("lensZoomStrength").setConstraint(c.getLensZoomStrength());
		getOption("deadzoneLimits").setConstraint(c.getDeadzoneLimits());
		getOption("resetDeadzoneOnFocus").setConstraint(c.getResetDeadzoneOnFocus());
		getOption("showDynamicCrosshair").setConstraint(c.getShowDynamicCrosshair());
	}
	
	
	
	bool isAdsDOFEnabled(){
		return getAdsDOFIntensity() > 0;
	}
	
	float getAdsDOFIntensity(){
		return adsDOFIntensity;
	}
	
	void setAdsDOFIntensity(float intensity){
		adsDOFIntensity = intensity;
	}
	
	bool isHideWeaponBarrelInOpticEnabled(){
		return hideWeaponBarrelInOptic;
	}
	
	void hideWeaponBarrelInOptic(bool enabled){
		hideWeaponBarrelInOptic = enabled;
	}
	
	bool isHideClothingInOpticEnabled(){
		return hideClothingInOptic;
	}
	
	void hideClothingInOptic(bool enabled){
		hideClothingInOptic = enabled;
	}
	
	float getLensZoomStrength(){
		return lensZoomStrength;
	}
	
	void setLensZoomStrength(float strength){
		lensZoomStrength = Math.Clamp(strength, 0, 1);
	}
	
	TFloatArray getDeadzoneLimits(){
		return deadzoneLimits;
	}
	
	void getDeadzoneLimits(out float limits[4]){
		limits[0] = deadzoneLimits[0];
		limits[1] = deadzoneLimits[1];
		limits[2] = deadzoneLimits[2];
		limits[3] = deadzoneLimits[3];
	}
	
	void setDeadzoneLimits(float limits[4]){
		deadzoneLimits[0] = limits[0];
		deadzoneLimits[1] = limits[1];
		deadzoneLimits[2] = limits[2];
		deadzoneLimits[3] = limits[3];
	}
	
	void setDeadzoneLimits(TFloatArray limits){
		deadzoneLimits[0] = limits[0];
		deadzoneLimits[1] = limits[1];
		deadzoneLimits[2] = limits[2];
		deadzoneLimits[3] = limits[3];
	}
	
	void setDeadzoneLimit(int i, float limit){
		if(i < 0 || i > 3) return;
		deadzoneLimits[i] = limit;
	}
	
	bool isResetDeadzoneOnFocusEnabled(){
		return resetDeadzoneOnFocus;
	}
	
	void resetDeadzoneOnFocus(bool enabled){
		resetDeadzoneOnFocus = enabled;
	}
	
	bool isDynamicCrosshairEnabled(){
		return showDynamicCrosshair;
	}
	
	void setDynamicCrosshairEnabled(bool enabled){
		showDynamicCrosshair = enabled;
	}
	
}