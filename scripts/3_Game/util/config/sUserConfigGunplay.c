class SUserConfigGunplay : SUserModuleConfig{

	override string getPath(){
		return "$saves:\\sUDE\\config\\sGunplay.json";
	}
	
	override string getDefaultPath(){
		return "$profile:\\sUDE\\config\\sGunplay_default.json";
	}
		
	///////////////////////////////////////
	// these go in json
	protected float adsFovReduction = 1.0;
	protected bool hideWeaponBarrelInOptic = false;
	protected float lensZoomStrength = 1.0;
	protected float deadzoneLimits[4] = { 0.2, 0.8, -0.2, -0.8 };
	protected bool resetDeadzoneOnFocus = true;
	///////////////////////////////////////
	
	float getAdsFovReduction(){
		return adsFovReduction;
	}
	
	void setAdsFovReduction(float reduction){
		adsFovReduction = Math.Clamp(reduction, 0, 1);
	}
	
	bool isHideWeaponBarrelInOpticEnabled(){
		return hideWeaponBarrelInOptic;
	}
	
	void hideWeaponBarrelInOptic(bool enabled){
		hideWeaponBarrelInOptic = enabled;
	}
	
	float getLensZoomStrength(){
		return lensZoomStrength;
	}
	
	void setLensZoomStrength(float strength){
		lensZoomStrength = Math.Clamp(strength, 0, 1);
	}
	
	TFloatArray getDeadzoneLimits(){
		TFloatArray limits = {};
		limits.Init(deadzoneLimits);
		return limits;
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
	
	override bool isValid(){
		return true; //@todo complete validation
	}
	
	override void load(){
		JsonFileLoader<SUserConfigGunplay> json = new JsonFileLoader<SUserConfigGunplay>;
		load(json);
		delete json;
	}
	
	override void save(){
		JsonFileLoader<SUserConfigGunplay> json = new JsonFileLoader<SUserConfigGunplay>;
		save(json);
		delete json;
	}
	
	override void createDefault(){
		JsonFileLoader<SUserConfigGunplay> json = new JsonFileLoader<SUserConfigGunplay>;
		createDefault(json);
		delete json;
	}
	
	void load(JsonFileLoader<SUserConfigGunplay> json){
		json.JsonLoadFile(getPath(), this);
	}
	
	void save(JsonFileLoader<SUserConfigGunplay> json){
		json.JsonSaveFile(getPath(), this);
	}
	
	void createDefault(JsonFileLoader<SUserConfigGunplay> json){
		json.JsonSaveFile(getDefaultPath(), this);
	}
}