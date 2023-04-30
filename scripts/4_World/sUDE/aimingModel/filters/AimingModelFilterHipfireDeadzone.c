class AimingModelFilterHipfireDeadzone : AimingModelFilterBase {
	
	protected vector m_deadzone;
	
	protected float m_velX[1];
	protected float m_velY[1];
	
	override bool isActive() {
		return GunplayConstants.AIMING_MODEL_USE_FILTER_HIPFIRE_DEADZONE;
	}
	
	override void onRaiseBegin() {
		m_deadzone = vector.Zero;
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		vector targetDeadzone = "0 0 0";
		if (!getPlayer().IsInOptics() && !getPlayer().IsInIronsights()) {
			vector accel = getAimingModel().getAimChangeDegree();
			targetDeadzone[0] = Math.Clamp(m_deadzone[0] + accel[0], GunplayConstants.HIPFIRE_DEADZONE_AMOUNT_DEGREE[1], GunplayConstants.HIPFIRE_DEADZONE_AMOUNT_DEGREE[2]);
			targetDeadzone[1] = Math.Clamp(m_deadzone[1] + accel[1], GunplayConstants.HIPFIRE_DEADZONE_AMOUNT_DEGREE[3], GunplayConstants.HIPFIRE_DEADZONE_AMOUNT_DEGREE[0]);
		}
		
		m_deadzone[0] = Math.SmoothCD(
			m_deadzone[0],
			targetDeadzone[0],
			m_velX,
			GunplayConstants.INERTIA_SPEED_ACCELERATION[0],
			1000, pDt);
		
		
		m_deadzone[1] = Math.SmoothCD(
			m_deadzone[1],
			targetDeadzone[1],
			m_velY,
			GunplayConstants.INERTIA_SPEED_ACCELERATION[1],
			1000, pDt);
		
		pModel.m_fAimXHandsOffset += m_deadzone[0];
		pModel.m_fAimYHandsOffset += m_deadzone[1];
		
	}
	
}