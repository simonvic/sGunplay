class AimingModelFilterMovement : AimingModelFilterBase{
	
	protected vector m_finalOffset;
	protected float m_movementAcceleration;
	protected float m_movementVelYaw[1];
	protected float m_movementVelPitch[1];
		
	override bool isActive(){
		return GunplayConstants.AIMING_MODEL_USE_FILTER_MOVEMENT || GunplayConstants.AIMING_MODEL_USE_FILTER_INJURY;
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex){
		float amplitudeX;
		float frequencyX;
		float amplitudeY;
		float frequencyY;
		
		float speed = getPlayer().m_MovementState.m_iMovement;
		
		//@todo use stanceIndex
		if(GunplayConstants.AIMING_MODEL_USE_FILTER_MOVEMENT && !getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE)){
			if(getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDCROUCH)){
				speed /= 1.5;
			}
			amplitudeX += speed * GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT[0];
			frequencyX += speed * GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT[1];
			amplitudeY += speed * GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT[2];
			frequencyY += speed * GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT[3];
		}
		
		if(GunplayConstants.AIMING_MODEL_USE_FILTER_INJURY){
			float injury = getPlayer().m_InjuryHandler.GetInjuryAnimValue();
			amplitudeX += injury * GunplayConstants.AIMING_MODEL_FILTER_INJURY[0];
			frequencyX += injury * GunplayConstants.AIMING_MODEL_FILTER_INJURY[1];
			amplitudeY += injury * GunplayConstants.AIMING_MODEL_FILTER_INJURY[2];
			frequencyY += injury * GunplayConstants.AIMING_MODEL_FILTER_INJURY[3];
		}
		
		if(speed > 0){
			m_movementAcceleration += pDt;
		}else{
			m_movementAcceleration = 0;
		}
		
		//SLog.d(string.Format("Ax: %1 | Ay: %2 | Fx: %3 | Fy: %4",amplitudeX,amplitudeY,frequencyX,frequencyY));
		m_finalOffset[0] = GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT_MULTIPLIER * amplitudeX * Math.Sin(frequencyX * m_movementAcceleration);
		m_finalOffset[1] = GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT_MULTIPLIER * amplitudeY * Math.Sin(frequencyY * m_movementAcceleration);
	
		pModel.m_fAimXHandsOffset += Math.SmoothCD(
			0,
			-m_finalOffset[0],
			m_movementVelYaw,
			GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT_SMOOTHTIME, 1000,
			pDt);
		
		pModel.m_fAimYHandsOffset += Math.SmoothCD(
			0,
			-m_finalOffset[1],
			m_movementVelPitch,
			GunplayConstants.AIMING_MODEL_FILTER_MOVEMENT_SMOOTHTIME, 1000,
			pDt);
			
	}
	
}