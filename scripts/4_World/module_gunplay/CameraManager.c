modded class CameraManager{
	
	protected SUserConfigGunplay m_sUserConfigGunplay;
	
	void CameraManager(DayZPlayerCameraBase camera, PlayerBase player){
		m_sUserConfigGunplay = SUserConfig.getInstance().gunplay();
	}
	
	override void onUpdate(float pDt, out DayZPlayerCameraResult pOutResult){
		super.onUpdate(pDt, pOutResult);
	}
	
	float getAdsFovReduction(){
		return m_sUserConfigGunplay.getAdsFovReduction();
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