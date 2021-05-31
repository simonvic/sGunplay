class AimingModelFilterBreathing : AimingModelFilterBase{
	
	protected float m_time;
	protected vector m_breathingOffset;
	protected float m_velX[1];
	protected float m_velY[1];
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex){
		m_time += pDt * getSpeed();
		
		computeBreathingPattern(calculateWeight(stanceIndex), GunplayConstants.SWAY_FREQUENCY, GunplayConstants.SWAY_AMPLITUDE);
		
		pModel.m_fAimXHandsOffset += Math.SmoothCD(
			pModel.m_fAimXHandsOffset,
			pModel.m_fAimXHandsOffset + m_breathingOffset[0],
			m_velX,
			0.1, 1000, pDt);
		
		pModel.m_fAimYHandsOffset += Math.SmoothCD(
			pModel.m_fAimYHandsOffset,
			pModel.m_fAimYHandsOffset + m_breathingOffset[1],
			m_velY,
			0.1, 1000, pDt);
		
		
		
		
	}
	
	protected void computeBreathingPattern(float weight, float frequency[2], float amplitude[2]){
		m_breathingOffset[0] = m_breathingOffset[0] / 2 + Math.Sin(m_time + frequency[0]) * amplitude[0] * weight;
		m_breathingOffset[1] = m_breathingOffset[1] / 2 + Math.Sin(m_time + frequency[1]) * amplitude[1] * weight;
	}
	
	protected float getSpeed(){
		float playerStamina =  getPlayerStamina() / getPlayer().GetStaminaHandler().GetStaminaCap();
		if( getPlayer().IsHoldingBreath() ){
			playerStamina *= GunplayConstants.SWAY_DECREASE_FOCUSING;
		}
		return (Math.Pow(GunplayConstants.SWAY_DECAY_POWER, 1 - playerStamina)) + GunplayConstants.SWAY_MINIMUM * getSwayModifier()[2];
	}
	
	protected float getPlayerStamina(){
		if(!GetGame().IsMultiplayer()){
			return getPlayer().GetStaminaHandler().GetStamina();
		}
		
		return getPlayer().GetStaminaHandler().GetSyncedStamina();
	}
	

	protected vector getSwayModifier(){
		return getWeapon().GetPropertyModifierObject().m_SwayModifiers;
	}
	
	
	protected float calculateWeight(int stanceIndex){
		switch(stanceIndex){
			case DayZPlayerConstants.STANCEIDX_RAISEDERECT:
				return GunplayConstants.SWAY_MULTIPLEIR_ERECT;
				break;
			case DayZPlayerConstants.STANCEIDX_RAISEDCROUCH:
				return GunplayConstants.SWAY_MULTIPLEIR_CROUCHED;
				break;
			case DayZPlayerConstants.STANCEIDX_RAISEDPRONE:
				return GunplayConstants.SWAY_MULTIPLEIR_PRONE;
				break;
		}
		return 1;
	}
	
	
}
