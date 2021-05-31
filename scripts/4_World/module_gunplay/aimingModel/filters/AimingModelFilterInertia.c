class AimingModelFilterInertia : AimingModelFilterBase {
	
	protected float m_currentInertia;
	protected float m_inertiaXVel[1];
	protected float m_inertiaYVel[1];
	
	override bool isActive(){
		return GunplayConstants.AIMING_MODEL_USE_WEAPON_INERTIA;
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex){
		
		m_currentInertia = computeInertiaMultiplier();
		
		pModel.m_fAimXHandsOffset = Math.SmoothCD(
			pModel.m_fAimXHandsOffset, 
			pModel.m_fAimXHandsOffset - (getAimingModel().getAimChangeDegree()[0] * m_currentInertia),
			m_inertiaXVel,
			GunplayConstants.INERTIA_SMOOTHNESS,
			1000, pDt);
		
		pModel.m_fAimYHandsOffset = Math.SmoothCD(
			pModel.m_fAimYHandsOffset,
			pModel.m_fAimYHandsOffset - (getAimingModel().getAimChangeDegree()[1] * m_currentInertia),
			m_inertiaYVel,
			GunplayConstants.INERTIA_SMOOTHNESS,
			1000, pDt);
		
	}
	
	/**
	*	@brief Compute the amount of inertia
	*	 @param weapon \p Weapon_Base - Weapon used for the computation
	*	 @return float - inertia amount
	*/
	protected float computeInertiaMultiplier(){
		float inertiaMultiplier = GunplayConstants.INERTIA_MULTIPLIER_BASE;

		////////////////////////
		// STANCE 
		inertiaMultiplier *= getInertiaMultiplierStance();
		
		////////////////////////
		// MOVEMENT
		inertiaMultiplier *= getInertiaMultiplierMovement();
		
		////////////////////////
		// WEAPON WEIGHT
		inertiaMultiplier *= getInertiaMultiplierWeapon();
		
		////////////////////////
		// WEAPON BARREL LENGTH
		inertiaMultiplier *= getInertiaMultiplierWeaponLength();
		
		////////////////////////
		// PLAYER INVENTORY WEIGHT
		inertiaMultiplier *= getInertiaMultiplierInventoryWeight();
				
		////////////////////////
		// HIPFIRE 
		inertiaMultiplier *= getInertiaMultiplierHipfire();
		
		return Math.Clamp(inertiaMultiplier, GunplayConstants.INERTIA_MIN_MULTIPLIER, GunplayConstants.INERTIA_MAX_MULTIPLIER);
	}
		
	
	/**
	*	@brief Get the inertia multiplier based on the player stance
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierStance(){
		if(getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDERECT | DayZPlayerConstants.STANCEMASK_ERECT)){
			return GunplayConstants.INERTIA_MULTIPLIER_ERECT;
		} else if(getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDCROUCH | DayZPlayerConstants.STANCEMASK_CROUCH)){
			return GunplayConstants.INERTIA_MULTIPLIER_CROUCHED;
		} else if(getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE | DayZPlayerConstants.STANCEMASK_PRONE)){
			return GunplayConstants.INERTIA_MULTIPLIER_PRONE;
		} 
		
		return 1;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the player movement
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierMovement(){
		switch(getPlayer().m_MovementState.m_iMovement){ 
			case 0:	return GunplayConstants.INERTIA_MULTIPLIER_STANDING;
			case 1: return GunplayConstants.INERTIA_MULTIPLIER_WALKING;
			case 2:	return GunplayConstants.INERTIA_MULTIPLIER_JOGGING;
		}
		return 1;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the weapon
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierWeapon(){
		return getWeapon().GetWeight() * GunplayConstants.INERTIA_MULTIPLIER_WEAPON_WEIGHT;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the weapon length
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierWeaponLength(){
		return getWeapon().getWeaponLength() * GunplayConstants.INERTIA_MULTIPLIER_WEAPON_LENGTH_WEIGHT;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the weapon
	*	 @return float - inertia multiplier
	*/
	//@todo use getPlayer().GetPlayerLoad() instead
	protected float getInertiaMultiplierInventoryWeight(){
		if(getPlayer().GetWeight() == 0) { //@todo temp-fix for weight not updating. find a solution
			getPlayer().UpdateWeight();
		}
		return getPlayer().GetWeight() * GunplayConstants.INERTIA_MULTIPLIER_PLAYER_WEIGHT;
	}
	
	/**
	*	@brief Get the hipfire inertia multiplier
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierHipfire(){
		if(!getPlayer().IsInOptics() && !getPlayer().IsInIronsights()){
			return GunplayConstants.INERTIA_MULTIPLIER_HIPFIRE;
		}
		return 1;
	}

}