modded class CameraManager{
	
	//@todo move this stuff to AimingModel
	protected SUserConfigGunplay m_sUserConfigGunplay;
	
	void CameraManager(DayZPlayerCameraBase camera, PlayerBase player){
		m_sUserConfigGunplay = SUserConfig.getInstance().gunplay();
	}
	
	override void onUpdate(float pDt, out DayZPlayerCameraResult pOutResult){
		super.onUpdate(pDt, pOutResult);
	}
	
	float getAdsFovReduction(){
		return SMath.mapTo(
			m_sUserConfigGunplay.getAdsFovReduction(), 0, 1,
			GunplayConstants.ADS_FOV_REDUCTION_CONSTRAINTS[0],
			GunplayConstants.ADS_FOV_REDUCTION_CONSTRAINTS[1]);
	}
	
	bool isHideWeaponBarrelInOpticEnabled(){
		return m_sUserConfigGunplay.isHideWeaponBarrelInOpticEnabled();
	}
	
	bool isResetDeadzoneOnFocusEnabled(){
		return m_sUserConfigGunplay.isResetDeadzoneOnFocusEnabled();
	}
	
	float getLensZoomStrength(){
		return m_sUserConfigGunplay.getLensZoomStrength();
	}
	
	TFloatArray getDeadzoneLimits(){
		return m_sUserConfigGunplay.getDeadzoneLimits();
	}
	
	void getDeadzoneLimits(out float deadzoneLimits[4]){
		m_sUserConfigGunplay.getDeadzoneLimits(deadzoneLimits);
	} 
	
}