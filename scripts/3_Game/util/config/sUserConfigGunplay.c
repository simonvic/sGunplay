class SUserConfigGunplay : SUserModuleConfig{
	
	///////////////////////////////////////
	// these go in json
	float adsFovReduction = 1.0;
	bool hideWeaponBarrelInOptic = false;
	float lensZoomStrength = 1.0;
	float deadzoneLimits[4] = { 10, 20, -10, -20 };
	///////////////////////////////////////
	
	override string getPath(){
		return "$saves:\\sUDE\\config\\sGunplay.json";
	}
	
	override string getDefaultPath(){
		return "$profile:\\sUDE\\config\\sGunplay_default.json";
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