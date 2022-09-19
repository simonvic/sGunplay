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
		auto dui = SDebugUI.of("inertia");
		dui.begin();
		dui.pos("0.7 0").size("512px").window();
		float multiplier = computeInertiaMultiplier();
		
		//////////////////////////
		// ACCELERATION
		m_accel = getAimingModel().getAimChangeDegree() * multiplier;
		m_vel += m_accel;
		m_vel[0] = Math.Clamp(m_vel[0], GunplayConstants.INERTIA_VELOCITY_LIMIT[1], GunplayConstants.INERTIA_VELOCITY_LIMIT[2]);
		m_vel[1] = Math.Clamp(m_vel[1], GunplayConstants.INERTIA_VELOCITY_LIMIT[3], GunplayConstants.INERTIA_VELOCITY_LIMIT[0]);
		float resetSpeed = 0.20;
		float accelSpeed = 0.05;
		float inertiaSpeedAcceleration[2] = {accelSpeed, accelSpeed};
		float inertiaSpeedReset[2] = {resetSpeed, resetSpeed};
		
		dui.table({
			{"",               "inertia multipliers",                    ""}
			{"base",           "0","x"}
			{"stance",         ""+getInertiaMultiplierStance(),          "x"}
			{"movement",       ""+getInertiaMultiplierMovement(),        "x"}
			{"wep weight",     ""+getInertiaMultiplierWeapon(),          "x"}
			{"wep length",     ""+getInertiaMultiplierWeaponLength(),    "x"}
			{"inventory",      ""+getInertiaMultiplierInventoryWeight(), "x"}
			{"hipfire",        ""+getInertiaMultiplierHipfire(),         "="}
			{"--------------------"}
			{"total",          ""+multiplier,                     " "}
		});
		dui.spacer();
		dui.table({
			{"Multiplier" , ""+multiplier}
			{"accelSpeed" , ""+accelSpeed}
			{"resetSpeed" , ""+resetSpeed}
			{"m_accel" , ""+m_accel}
			{"wepLength" , ""+getWeapon().getWeaponLength()}
			{"m_vel" , ""+m_vel[0], ""+m_vel[1]}
		});
		
		vector initial;
		initial[0] = pModel.m_fAimXHandsOffset;
		initial[1] = pModel.m_fAimYHandsOffset;
		
		if (false) {
			pModel.m_fAimXHandsOffset -= m_vel[0];
			pModel.m_fAimYHandsOffset -= m_vel[1];
		} else {
			pModel.m_fAimXHandsOffset = Math.SmoothCD(
				pModel.m_fAimXHandsOffset,
				pModel.m_fAimXHandsOffset - m_vel[0],
				m_currInertiaVelX,
				inertiaSpeedAcceleration[0], 1000, pDt);
			
			pModel.m_fAimYHandsOffset = Math.SmoothCD(
				pModel.m_fAimYHandsOffset,
				pModel.m_fAimYHandsOffset - m_vel[1],
				m_currInertiaVelY,
				inertiaSpeedAcceleration[1], 1000, pDt);
		}
			
		vector final;
		final[0] = pModel.m_fAimXHandsOffset;
		final[1] = pModel.m_fAimYHandsOffset;
		vector delta = Vector(initial[0] - final[0], initial[1] - final[1], 0);
		
		
		
		/*
		dui.table({
			{"initial", ""+initial}
			{"final", ""+final}
		});
		dui.plotlive("m_velX", Math.AbsFloat(m_vel[0]), GunplayConstants.INERTIA_VELOCITY_LIMIT[1], GunplayConstants.INERTIA_VELOCITY_LIMIT[2]);
		dui.plotlive("deltaX", delta[0], -10, 10);
		dui.plotlive("deltaY", delta[1], -10, 10);
		*/
		
		//////////////////////////
		// DECELERATION		
		m_vel[0] = Math.SmoothCD(
			m_vel[0],
			0,
			m_currResetVelX,
			inertiaSpeedReset[0], 1000, pDt);
		
		m_vel[1] = Math.SmoothCD(
			m_vel[1],
			0,
			m_currResetVelY,
			inertiaSpeedReset[1], 1000, pDt);
		
		if (GetGame().IsClient()) {
			pModel.m_fAimXCamOffset += m_vel[0] * 0.05;
			pModel.m_fAimYCamOffset += m_vel[1] * 0.05;
		}
		
		dui.end();
	}
	
	/**
	*	@brief Compute the amount of inertia
	*	 @param weapon \p Weapon_Base - Weapon used for the computation
	*	 @return float - inertia amount
	*/
	protected float computeInertiaMultiplier() {		
		float inertiaMultiplier = 1.0;
		inertiaMultiplier *= getInertiaMultiplierStance();
		inertiaMultiplier *= getInertiaMultiplierMovement();
		inertiaMultiplier *= getInertiaMultiplierWeapon();
		inertiaMultiplier *= getInertiaMultiplierWeaponLength();
		inertiaMultiplier *= getInertiaMultiplierInventoryWeight();
		inertiaMultiplier *= getInertiaMultiplierHipfire();
		inertiaMultiplier  = Math.Clamp(inertiaMultiplier, 0, 1);		
		return inertiaMultiplier;
	}
		
	
	/**
	*	@brief Get the inertia multiplier based on the player stance
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierStance() {
		if (getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDERECT | DayZPlayerConstants.STANCEMASK_ERECT)) {
			return 1;
		} else if (getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDCROUCH | DayZPlayerConstants.STANCEMASK_CROUCH)) {
			return 0.30;
		} else if (getPlayer().IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE | DayZPlayerConstants.STANCEMASK_PRONE)) {
			return 0.25;
		}
		return 1;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the player movement
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierMovement() {
		switch (getPlayer().m_MovementState.m_iMovement) { 
			case 0:	return 1;
			case 1: return 1.25;
			case 2:	return 1.50;
		}
		return 1;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the weapon
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierWeapon() {
		int w = getWeapon().GetWeight();
		if (w > 6000) return 2.00;
		if (w > 4000) return 1.75;
		if (w > 2000) return 1.25;
		if (w > 1000) return 1.10;
		return 1;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the weapon length
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierWeaponLength() {
		return getWeapon().getWeaponLength() * 0.25;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the weapon
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierInventoryWeight() {
		int w = getPlayer().GetWeight();
		if (w > 40000) return 1.90;
		if (w > 20000) return 1.75;
		if (w > 10000) return 1.50;
		if (w > 5000)  return 1.25;
		return 1.00;
	}
	
	/**
	*	@brief Get the hipfire inertia multiplier
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierHipfire() {
		return 1;
	}

}