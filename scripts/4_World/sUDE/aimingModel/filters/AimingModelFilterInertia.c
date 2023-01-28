class AimingModelFilterInertia : AimingModelFilterBase {
	
	
	protected vector m_accel;
	protected vector m_vel;
	
	protected float m_currInertiaVelX[1];
	protected float m_currInertiaVelY[1];
	protected float m_currResetVelX[1];
	protected float m_currResetVelY[1];
	
	override bool isActive() {
		return GunplayConstants.AIMING_MODEL_USE_WEAPON_INERTIA;
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		
		//////////////////////////
		// ACCELERATION
		m_accel = getAimingModel().getAimChangeDegree() * computeInertiaMultiplier();
		m_vel += m_accel;
		m_vel[0] = Math.Clamp(m_vel[0], GunplayConstants.INERTIA_VELOCITY_LIMIT[1], GunplayConstants.INERTIA_VELOCITY_LIMIT[2]);
		m_vel[1] = Math.Clamp(m_vel[1], GunplayConstants.INERTIA_VELOCITY_LIMIT[3], GunplayConstants.INERTIA_VELOCITY_LIMIT[0]);
		
		pModel.m_fAimXHandsOffset = Math.SmoothCD(
			pModel.m_fAimXHandsOffset,
			pModel.m_fAimXHandsOffset - m_vel[0],
			m_currInertiaVelX,
			GunplayConstants.INERTIA_SPEED_ACCELERATION[0], 1000, pDt);
		
		pModel.m_fAimYHandsOffset = Math.SmoothCD(
			pModel.m_fAimYHandsOffset,
			pModel.m_fAimYHandsOffset - m_vel[1],
			m_currInertiaVelY,
			GunplayConstants.INERTIA_SPEED_ACCELERATION[1], 1000, pDt);
		
		//////////////////////////
		// DECELERATION		
		m_vel[0] = Math.SmoothCD(
			m_vel[0],
			0,
			m_currResetVelX,
			GunplayConstants.INERTIA_SPEED_RESET[0], 1000, pDt);
		
		m_vel[1] = Math.SmoothCD(
			m_vel[1],
			0,
			m_currResetVelY,
			GunplayConstants.INERTIA_SPEED_RESET[1], 1000, pDt);
		
		if (GetGame().IsClient()) {
			pModel.m_fAimXCamOffset += m_vel[0] * GunplayConstants.INERTIA_MISALIGNMENT_INTENSITY[0];
			pModel.m_fAimYCamOffset += m_vel[1] * GunplayConstants.INERTIA_MISALIGNMENT_INTENSITY[1];
		}
		
	}
	
	/**
	*	@brief Compute the amount of inertia
	*	 @param weapon \p Weapon_Base - Weapon used for the computation
	*	 @return float - inertia amount
	*/
	protected float computeInertiaMultiplier() {		
		float inertiaMultiplier = GunplayConstants.INERTIA_MULTIPLIER_BASE;
		inertiaMultiplier *= getInertiaMultiplierStance();
		inertiaMultiplier *= getInertiaMultiplierMovement();
		inertiaMultiplier *= getInertiaMultiplierWeapon();
		inertiaMultiplier *= getInertiaMultiplierWeaponLength();
		inertiaMultiplier *= getInertiaMultiplierInventoryWeight();
		inertiaMultiplier *= getInertiaMultiplierHipfire();
		inertiaMultiplier  = Math.Clamp(inertiaMultiplier, GunplayConstants.INERTIA_MIN_MULTIPLIER, GunplayConstants.INERTIA_MAX_MULTIPLIER);
		return inertiaMultiplier;
	}
		
	
	/**
	*	@brief Get the inertia multiplier based on the player stance
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierStance() {
		//@todo improve this
		if (getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDERECT | DayZPlayerConstants.STANCEMASK_ERECT)) {
			return GunplayConstants.INERTIA_MULTIPLIER_ERECT;
		}
		if (getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDCROUCH | DayZPlayerConstants.STANCEMASK_CROUCH)) {
			return GunplayConstants.INERTIA_MULTIPLIER_CROUCHED;
		}
		if (getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE | DayZPlayerConstants.STANCEMASK_PRONE)) {
			return GunplayConstants.INERTIA_MULTIPLIER_PRONE;
		}
		return 1;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the player movement
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierMovement() {
		switch (getPlayer().m_MovementState.m_iMovement) { 
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
	protected float getInertiaMultiplierWeapon() {
		int w = getWeapon().GetWeight();
		if (w > GunplayConstants.WEAPON_WEIGHT_GRAMS_VERYHEAVY)  return GunplayConstants.INERTIA_MULTIPLIER_WEAPON_WEIGHT_VERYHEAVY;
		if (w > GunplayConstants.WEAPON_WEIGHT_GRAMS_HEAVY)      return GunplayConstants.INERTIA_MULTIPLIER_WEAPON_WEIGHT_HEAVY;
		if (w > GunplayConstants.WEAPON_WEIGHT_GRAMS_MEDIUM)     return GunplayConstants.INERTIA_MULTIPLIER_WEAPON_WEIGHT_MEDIUM;
		if (w > GunplayConstants.WEAPON_WEIGHT_GRAMS_LIGHT)      return GunplayConstants.INERTIA_MULTIPLIER_WEAPON_WEIGHT_LIGHT;
		return GunplayConstants.INERTIA_MULTIPLIER_WEAPON_WEIGHT_VERYLIGHT;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the weapon length
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierWeaponLength() {
		return getWeapon().getWeaponLength() * GunplayConstants.INERTIA_MULTIPLIER_WEAPON_LENGTH_WEIGHT;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the weapon
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierInventoryWeight() {
		int w = getPlayer().GetWeight();
		if (w > GunplayConstants.INVENTORY_WEIGHT_GRAMS_OVERLOADED) return GunplayConstants.INERTIA_MULTIPLIER_INVENTORY_WEIGHT_OVERLOADED;
		if (w > GunplayConstants.INVENTORY_WEIGHT_GRAMS_HEAVY)      return GunplayConstants.INERTIA_MULTIPLIER_INVENTORY_WEIGHT_HEAVY;
		if (w > GunplayConstants.INVENTORY_WEIGHT_GRAMS_MEDIUM)     return GunplayConstants.INERTIA_MULTIPLIER_INVENTORY_WEIGHT_MEDIUM;
		if (w > GunplayConstants.INVENTORY_WEIGHT_GRAMS_LIGHT)      return GunplayConstants.INERTIA_MULTIPLIER_INVENTORY_WEIGHT_LIGHT;
		return GunplayConstants.INERTIA_MULTIPLIER_INVENTORY_WEIGHT_VERYLIGHT;
	}
	
	/**
	*	@brief Get the hipfire inertia multiplier
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierHipfire() {
		return GunplayConstants.INERTIA_MULTIPLIER_HIPFIRE;
	}

}