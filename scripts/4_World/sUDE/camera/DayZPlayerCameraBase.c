modded class DayZPlayerCameraBase {
	
	protected static ref SCOOpticMisalignment m_opticMisalignmentOverlay;
	protected static SUserConfigGunplay userCfgGunplay;
	
	void DayZPlayerCameraBase(DayZPlayer pPlayer, HumanInputController pInput) {
		if (!m_opticMisalignmentOverlay) m_opticMisalignmentOverlay = new SCOOpticMisalignment();
		userCfgGunplay = SUserConfig.gunplay();
	}
	
	override void OnActivate(DayZPlayerCamera pPrevCamera, DayZPlayerCameraResult pPrevCameraResult) {
		super.OnActivate(pPrevCamera, pPrevCameraResult);
		if (pPrevCamera && pPrevCamera.Type() == DayZPlayerCameraOptics) {
			m_opticMisalignmentOverlay.deactivate();
		}
	}
	
	protected static array<float> getDeadzoneLimits() {
		return userCfgGunplay.getDeadzoneLimits();
	}
	
	protected static bool isAdsDOFEnabled() {
		return userCfgGunplay.isAdsDOFEnabled();
	}
	
	protected static float getAdsDOFIntensity() {
		return userCfgGunplay.getAdsDOFIntensity();
	}
	
	protected static bool isResetDeadzoneOnFocusEnabled() {
		return userCfgGunplay.isResetDeadzoneOnFocusEnabled();
	}
	
	protected static bool isHideClothingInOpticEnabled() {
		return userCfgGunplay.isHideClothingInOpticEnabled();
	}
	
	protected static bool isHideWeaponBarrelInOpticEnabled() {
		return userCfgGunplay.isHideWeaponBarrelInOpticEnabled();
	}
}