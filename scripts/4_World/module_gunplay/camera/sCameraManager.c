modded class SCameraManager{
	
	//@todo move this stuff to AimingModel
	protected SUserConfigGunplay m_sUserConfigGunplay;
	
	override void onInit(){
		super.onInit();
		m_sUserConfigGunplay = SUserConfig.gunplay();
	}
		
	float getAdsFovReduction(){
		return GunplayConstants.ADS_FOV_REDUCTION;
	}
	
	bool isHideWeaponBarrelInOpticEnabled(){
		return m_sUserConfigGunplay.isHideWeaponBarrelInOpticEnabled();
	}
	
	bool isHideClothingInOpticEnabled(){
		return m_sUserConfigGunplay.isHideClothingInOpticEnabled();
	}
	
	bool isResetDeadzoneOnFocusEnabled(){
		return m_sUserConfigGunplay.isResetDeadzoneOnFocusEnabled();
	}
	
	float getLensZoomStrength(){
		return SMath.mapTo(
			m_sUserConfigGunplay.getLensZoomStrength(), 0, 1,
			GunplayConstants.ADS_LENS_STRENGTH_CONSTRAINTS[0],
			GunplayConstants.ADS_LENS_STRENGTH_CONSTRAINTS[1]);
	}
	
	TFloatArray getDeadzoneLimits(){
		return m_sUserConfigGunplay.getDeadzoneLimits();
	}
	
	void getDeadzoneLimits(out float deadzoneLimits[4]){
		m_sUserConfigGunplay.getDeadzoneLimits(deadzoneLimits);
	} 
	
	bool isAdsDOFEnabled(){
		return getAdsDOFIntensity() > 0;
	}
	
	float getAdsDOFIntensity(){
		return m_sUserConfigGunplay.getAdsDOFIntensity();
	}
	
}