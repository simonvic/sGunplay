class AimingModelFilterMovement : AimingModelFilterBase {
	
	
	protected float m_time;
		
	protected float m_velHandsX[1];
	protected float m_velHandsY[1];
	
	protected float m_velMisalignX[1];
	protected float m_velMisalignY[1];
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		//@todo clean this shit
		
		float amplitudeX, frequencyX, amplitudeY, frequencyY;
		float speed = getPlayer().m_MovementState.m_iMovement;
		float aimChangeX = getAimingModel().getAimChangeDegree()[0];
		float aimChangeY = getAimingModel().getAimChangeDegree()[1];
		
		if (speed > 0) {
			m_time += pDt;
			aimChangeX += GunplayConstants.ADS_MOVEMENT_MISALIGNMENT_STRENGTH * speed * Math.Sin(Math.PI * speed * m_time * GunplayConstants.ADS_MOVEMENT_MISALIGNMENT_FREQUENCY);
			aimChangeY += GunplayConstants.ADS_MOVEMENT_MISALIGNMENT_STRENGTH * speed * Math.Sin(Math.PI2 * speed * m_time * GunplayConstants.ADS_MOVEMENT_MISALIGNMENT_FREQUENCY);
		} else {
			m_time = 0;
		}
		
		if (!getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE)) {
			if (getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDCROUCH)) {
				speed *= 0.69;
			}
			amplitudeX += speed * GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT[0];
			frequencyX += speed * GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT[1];
			amplitudeY += speed * GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT[2];
			frequencyY += speed * GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT[3];
		}
		
		if (GunplayConstants.AIMING_MODEL_USE_FILTER_INJURY) {
			float injury = getPlayer().m_InjuryHandler.GetInjuryAnimValue();
			amplitudeX += injury * GunplayConstants.AIMING_MODEL_FILTER_INJURY[0];
			frequencyX += injury * GunplayConstants.AIMING_MODEL_FILTER_INJURY[1];
			amplitudeY += injury * GunplayConstants.AIMING_MODEL_FILTER_INJURY[2];
			frequencyY += injury * GunplayConstants.AIMING_MODEL_FILTER_INJURY[3];
		}
		
		pModel.m_fAimXHandsOffset = Math.SmoothCD(
			pModel.m_fAimXHandsOffset,
			pModel.m_fAimXHandsOffset + GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT_MULTIPLIER * amplitudeX * Math.Sin(m_time * frequencyX),
			m_velHandsX,
			GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT_SMOOTHTIME, 1000, pDt);
		
		pModel.m_fAimYHandsOffset = Math.SmoothCD(
			pModel.m_fAimYHandsOffset,
			pModel.m_fAimYHandsOffset + GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT_MULTIPLIER * amplitudeY * Math.Sin(m_time * frequencyY),
			m_velHandsY,
			GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT_SMOOTHTIME, 1000, pDt);
		
		pModel.m_fAimXCamOffset = Math.SmoothCD(
			pModel.m_fAimXCamOffset,
			pModel.m_fAimXCamOffset + aimChangeX,
			m_velMisalignX,
			0.3, 1000, pDt);
		
		pModel.m_fAimYCamOffset = Math.SmoothCD(
			pModel.m_fAimYCamOffset,
			pModel.m_fAimYCamOffset + aimChangeY,
			m_velMisalignY,
			0.3, 1000, pDt);
	}
}