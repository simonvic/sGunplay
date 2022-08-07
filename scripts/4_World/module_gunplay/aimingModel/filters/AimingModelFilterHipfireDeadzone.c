class AimingModelFilterHipfireDeadzone : AimingModelFilterBase {
	
	protected vector m_deadzone;
	
	protected float m_velX[1];
	protected float m_velY[1];
	
	override bool isActive() {
		return GunplayConstants.AIMING_MODEL_USE_FILTER_HIPFIRE_DEADZONE;
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		vector accel = getAimingModel().getAimChangeDegree();
		
		if (getPlayer().IsInOptics() || getPlayer().IsInIronsights()) {
			m_deadzone = "0 0 0";
		} else {
			m_deadzone[0] = m_deadzone[0] + accel[0] * getWeapon().getWeaponLength();
			m_deadzone[1] = m_deadzone[1] + accel[1] * getWeapon().getWeaponLength();
			
			m_deadzone[0] = Math.Clamp(m_deadzone[0], GunplayConstants.HIPFIRE_DEADZONE_AMOUNT_DEGREE[1], GunplayConstants.HIPFIRE_DEADZONE_AMOUNT_DEGREE[2]);
			m_deadzone[1] = Math.Clamp(m_deadzone[1], GunplayConstants.HIPFIRE_DEADZONE_AMOUNT_DEGREE[3], GunplayConstants.HIPFIRE_DEADZONE_AMOUNT_DEGREE[0]);
		}
		
		pModel.m_fAimXHandsOffset = Math.SmoothCD(
			pModel.m_fAimXHandsOffset,
			pModel.m_fAimXHandsOffset + m_deadzone[0],
			m_velX,
			0.2, 1000, pDt);
		
		pModel.m_fAimYHandsOffset = Math.SmoothCD(
			pModel.m_fAimYHandsOffset,
			pModel.m_fAimYHandsOffset + m_deadzone[1],
			m_velY,
			0.2, 1000, pDt);
	}
	
}