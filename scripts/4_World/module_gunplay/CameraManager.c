modded class CameraManager{
	
	protected ref SUserConfigGunplay m_sUserConfigGunplay;
	
	void CameraManager(DayZPlayerCameraBase camera, PlayerBase player){
		m_sUserConfigGunplay = SUserConfig.getInstance().gunplay();
	}
	
	override void onUpdate(float pDt, out DayZPlayerCameraResult pOutResult){
		super.onUpdate(pDt, pOutResult);
	}
	
	float getAdsFovReduction(){
		return m_sUserConfigGunplay.adsFovReduction;
	}
	
	bool isHideBarrelInOpticEnabled(){
		return m_sUserConfigGunplay.hideWeaponBarrelInOptic;
	}
	
	float getLensZoomStrength(){
		return m_sUserConfigGunplay.lensZoomStrength;
	}
	
	void getDeadzoneLimits(out float deadzoneLimits[4]){
		deadzoneLimits[0] = m_sUserConfigGunplay.deadzoneLimits[0];
		deadzoneLimits[1] = m_sUserConfigGunplay.deadzoneLimits[1];
		deadzoneLimits[2] = m_sUserConfigGunplay.deadzoneLimits[2];
		deadzoneLimits[3] = m_sUserConfigGunplay.deadzoneLimits[3];
	} 
	
}