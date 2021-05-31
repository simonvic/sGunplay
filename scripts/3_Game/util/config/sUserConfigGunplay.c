class SUserConfigGunplay : SUserConfigBase{

	override string getPath(){
		return "$saves:\\sUDE\\config\\sGunplay.json";
	}
	
	override string getDefaultPath(){
		return "$profile:\\sUDE\\config\\sGunplay_default.json";
	}
	
	override void deserialize(string data, out string error){
		SUserConfigGunplay cfg = this;
		m_serializer.ReadFromString(cfg, data, error);
	}
	
	override string serialize(bool serializeDefault = false){
		string result;		
		SUserConfigGunplay cfg;
		if(serializeDefault) {
			cfg = new SUserConfigGunplay();
		}else{
			cfg = this;
		}
		m_serializer.WriteToString(cfg, true, result);
		return result;
	}
		
	///////////////////////////////////////
	// these go in json
	protected float adsDOFIntensity = 0.5;
	protected bool hideWeaponBarrelInOptic = false;
	protected bool hideClothingInOptic = true;
	protected float lensZoomStrength = 1.0;
	protected float deadzoneLimits[4] = { 0.2, 0.8, 0.2, 0.8 };
	protected bool resetDeadzoneOnFocus = true;
	protected bool showDynamicCrosshair = true;
	///////////////////////////////////////
	
	
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
	
	bool isDynamicCrosshairEnabled(){
		return showDynamicCrosshair;
	}
	
	void setDynamicCrosshairEnabled(bool enabled){
		showDynamicCrosshair = enabled;
	}
	
}