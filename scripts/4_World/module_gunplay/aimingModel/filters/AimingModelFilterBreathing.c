class AimingModelFilterBreathing : AimingModelFilterBase{
	
	protected float m_time;
	protected vector m_breathingOffset;
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex){
		m_time += pDt * getSpeed();
		computeBreathingPattern(calculateWeight(stanceIndex));
		pModel.m_fAimXHandsOffset += m_breathingOffset[0];
		pModel.m_fAimYHandsOffset += m_breathingOffset[1];
	}
	
	protected void computeBreathingPattern(float weight){
		m_breathingOffset[0] = Math.Sin(m_time * GunplayConstants.SWAY_FREQUENCY[0]) * GunplayConstants.SWAY_AMPLITUDE[0];
		m_breathingOffset[1] = Math.Sin(m_time * GunplayConstants.SWAY_FREQUENCY[1]) * GunplayConstants.SWAY_AMPLITUDE[1];
	}
	
	protected float getSpeed(){
		float playerStamina = getPlayer().GetStaminaHandler().GetSyncedStamina() / getPlayer().GetStaminaHandler().GetStaminaCap();
		if( getPlayer().IsHoldingBreath() ){
			playerStamina *= GunplayConstants.SWAY_DECREASE_FOCUSING;
		}
		return (Math.Pow(GunplayConstants.SWAY_DECAY_POWER, 1 - playerStamina)) + GunplayConstants.SWAY_MINIMUM * getSwayModifier()[2];
	}
	

	protected vector getSwayModifier(){
		return getWeapon().GetPropertyModifierObject().m_SwayModifiers;
	}
	
	
	protected float calculateWeight(int stanceIndex){
		float weight = 1;
		switch(stanceIndex){
			case DayZPlayerConstants.STANCEIDX_RAISEDERECT:
				weight = 1;
				break;
			case DayZPlayerConstants.STANCEIDX_RAISEDCROUCH:
				weight = 0.5;
				break;
			case DayZPlayerConstants.STANCEIDX_RAISEDPRONE:
				weight = 0.05;
				break;
		}
		return weight;
	}
	
	
}
