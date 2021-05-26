modded class PlayerSwayConstants{
	static const float SWAY_MULTIPLIER_DEFAULT = 1.0;
	static const float SWAY_MULTIPLIER_STABLE = 0.5;
	static const float SWAY_MULTIPLIER_EXHAUSTED = 2;
	static const float SWAY_TIME_IN = 1.5;
	static const float SWAY_TIME_STABLE = 3.0;
	static const float SWAY_TIME_EXHAUSTED = 1.5;
	static const float SWAY_TIME_OUT = 0.5;
}

typedef array<ref AimingModelFilterBase> TAimingModelFiltersList;

modded class DayZPlayerImplementAiming{
	
	protected Weapon_Base m_weapon;
	
	protected vector m_handsOffset;
	
	protected float m_inertiaXVel[1];
	protected float m_inertiaYVel[1];
	
	protected vector m_sCrosshairPosition;
	protected float m_sCrosshairXVel[1];
	protected float m_sCrosshairYVel[1];
	
	protected vector m_weaponBarrelPosition;
	protected vector m_weaponMuzzlePosition;
	protected vector m_weaponTargetPosition;
	
	protected ref SRaycast m_sCrosshairRay;
	
	protected ref TAimingModelFiltersList m_filters;
	
	void DayZPlayerImplementAiming(DayZPlayerImplement player){
		m_sCrosshairRay = new SRaycast("0 0 0", "0 0 0", 0.01, ObjIntersectFire, CollisionFlags.NEARESTCONTACT);
		m_filters = new TAimingModelFiltersList();
		registerFilters();	
	}
	
	protected void registerFilters(){
		registerFilter(new AimingModelFilterMovement(m_PlayerPb, m_weapon));
		//registerFilter(new AimingModelInjuryFilter(m_PlayerPb, m_weapon)); //added as a child filter to the movement filter
	}
	
	protected void registerFilter(AimingModelFilterBase filter){
		if(!filter || !m_filters) return;
		m_filters.Insert(filter);
	}
	
	
	
	
	override bool ProcessAimFilters(float pDt, SDayZPlayerAimingModel pModel, int stance_index){
		bool result = super.ProcessAimFilters(pDt, pModel, stance_index);
			
		m_weapon = Weapon_Base.Cast(m_PlayerPb.GetItemInHands());
		/* @todo process aim filters keeps getting called even after holstered weapon
			to activae quickly releas right mouse button, holster weapon, and right mouse button again 
		*/
		if(!m_weapon) return result;
		
		foreach(AimingModelFilterBase filter : m_filters){
			filter.onUpdate(pDt, pModel, stance_index);
		}
		updateHandsOffset(pModel);
		updateSCrosshair(m_weapon, pDt);
		
		return result;
	}
	
	override void ApplyHorizontalNoise(out float x_axis, out float y_axis, float smooth_time,float max_velocity_low, float max_velocity_high, float velocity_modifier,  float max_distance, float weight, float pDt){
		return;
	}
	
	override void ApplyBreathingPattern(out float x_axis, out float y_axis, float pAmplitude, float pTotalTime, float weight){		
		float frequency[] = {0.2, 0.4};
		float amplitude[] = {1.5, 1.8};
		float multiplier = Math.Lerp(PlayerSwayConstants.SWAY_MULTIPLIER_DEFAULT,0,m_LastSwayMultiplier);
				
		x_axis = Math.Sin(pTotalTime * frequency[0]) * amplitude[0] * weight;
		y_axis = Math.Sin(pTotalTime * frequency[1]) * amplitude[1] * weight;
		
		x_axis += m_BreathingXAxisOffset * multiplier;
		y_axis += m_BreathingYAxisOffset * multiplier;
	}
		
	
	/**
	*	@brief Apply the inertia to the given Aiming Model 
	*	 @param pModel \p SDayZPlayerAimingModel - Player aiming model
	*	 @param inertia \p float - Amount of inertia
	*/
	protected void applyWeaponInertia(SDayZPlayerAimingModel pModel, float inertia, float pDt){
		pModel.m_fAimXHandsOffset = Math.SmoothCD(
			pModel.m_fAimXHandsOffset, 
			pModel.m_fAimXHandsOffset - (getAimChangeDegree()[0] * inertia),
			m_inertiaXVel,
			GunplayConstants.INERTIA_SMOOTHNESS,
			1000, pDt);
		
		pModel.m_fAimYHandsOffset = Math.SmoothCD(
			pModel.m_fAimYHandsOffset,
			pModel.m_fAimYHandsOffset - (getAimChangeDegree()[1] * inertia),
			m_inertiaYVel,
			GunplayConstants.INERTIA_SMOOTHNESS,
			1000, pDt);
	}
	
	/**
	*	@brief Update the current value of the hands offset
	*	 @param pModel \p SDayZPlayerAimingModel - Player aiming model
	*/
	protected void updateHandsOffset(SDayZPlayerAimingModel pModel){
		m_handsOffset[0] = pModel.m_fAimXHandsOffset;
		m_handsOffset[1] = pModel.m_fAimYHandsOffset;
		if(m_CurrentRecoil){
			m_handsOffset[0] = m_handsOffset[0] + m_CurrentRecoil.getCurrentHandsOffset()[0] * GunplayConstants.AIMING_MODEL_HANDS_OFFSET_RECOIL_CONTRIBUTION[0];
			m_handsOffset[1] = m_handsOffset[1] + m_CurrentRecoil.getCurrentHandsOffset()[1] * GunplayConstants.AIMING_MODEL_HANDS_OFFSET_RECOIL_CONTRIBUTION[1];
		}
	}
	
	
	/**
	*	@brief Update the crosshair position on the screen vector and its visibility
	*	 @param weapon \p Weapon_Base - Weapon used to get the direction of the raycast
	*/
	protected void updateSCrosshair(Weapon_Base weapon, float pDt){
		getWeaponComponentsPosition(weapon, m_weaponBarrelPosition, m_weaponMuzzlePosition, m_weaponTargetPosition, GunplayConstants.CROSSHAIR_PRECISION);
		m_sCrosshairRay.setBegPos(m_weaponMuzzlePosition);
		m_sCrosshairRay.setEndPos(m_weaponTargetPosition);
		/*
		m_sCrosshairRay.addIgnoredObject(weapon);
		m_sCrosshairRay.addIgnoredObject(m_PlayerPb);
		*/
		m_sCrosshairRay.launch();
		
		vector pos = GetGame().GetScreenPosRelative(m_sCrosshairRay.getContactPos());
		
		m_sCrosshairPosition[0] = Math.SmoothCD(m_sCrosshairPosition[0], pos[0], m_sCrosshairXVel, GunplayConstants.CROSSHAIR_SMOOTHNESS, 1000, pDt);
		m_sCrosshairPosition[1] = Math.SmoothCD(m_sCrosshairPosition[1], pos[1], m_sCrosshairYVel, GunplayConstants.CROSSHAIR_SMOOTHNESS, 1000, pDt);
	}
	
	
	/**
	*	@brief Get the barrel position, muzzle position and the target position at the given distance
	*	 @param weapon \p Weapon_Base - 
	*	 @param barrelPosition \p vector - 
	*	 @param muzzlePosition \p vector - 
	*	 @param targetPosition \p vector - 
	*	 @param distance \p float - 
	*/
	static void getWeaponComponentsPosition(Weapon_Base weapon, out vector barrelPosition, out vector muzzlePosition, out vector targetPosition, float distance = 1){
		barrelPosition = weapon.ModelToWorld(weapon.GetSelectionPositionLS( "konec hlavne" ));
		muzzlePosition = weapon.ModelToWorld(weapon.GetSelectionPositionLS( "usti hlavne" ));
		targetPosition = barrelPosition + (vector.Direction(barrelPosition, muzzlePosition ) * distance);
	}
	

	/**
	*	@brief Compute the amount of inertia
	*	 @param weapon \p Weapon_Base - Weapon used for the computation
	*	 @return float - inertia amount
	*/
	protected float computeInertiaMultiplier(Weapon_Base weapon){
		float inertiaMultiplier = GunplayConstants.INERTIA_MULTIPLIER_BASE;

		////////////////////////
		// STANCE 
		inertiaMultiplier *= getInertiaMultiplierStance();
		
		////////////////////////
		// MOVEMENT
		inertiaMultiplier *= getInertiaMultiplierMovement();
		
		////////////////////////
		// WEAPON WEIGHT
		inertiaMultiplier *= getInertiaMultiplierWeapon(weapon);
		
		////////////////////////
		// PLAYER INVENTORY WEIGHT
		inertiaMultiplier *= getInertiaMultiplierInventoryWeight();
				
		////////////////////////
		// HIPFIRE 
		inertiaMultiplier *= getInertiaMultiplierHipfire();
		
		//inertiaMultiplier = 40;
		return Math.Clamp(inertiaMultiplier, GunplayConstants.INERTIA_MIN_MULTIPLIER, GunplayConstants.INERTIA_MAX_MULTIPLIER);
	}
		
	
	/**
	*	@brief Get the inertia multiplier based on the player stance
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierStance(){
		if(m_PlayerPb.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDERECT | DayZPlayerConstants.STANCEMASK_ERECT)){
			return GunplayConstants.INERTIA_MULTIPLIER_ERECT;
		} else if(m_PlayerPb.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDCROUCH | DayZPlayerConstants.STANCEMASK_CROUCH)){
			return GunplayConstants.INERTIA_MULTIPLIER_CROUCHED;
		} else if(m_PlayerPb.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE | DayZPlayerConstants.STANCEMASK_PRONE)){
			return GunplayConstants.INERTIA_MULTIPLIER_PRONE;
		} 
		
		return 1;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the player movement
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierMovement(){
		switch(m_PlayerDpi.m_MovementState.m_iMovement){ 
			case 0:	//standing
				return GunplayConstants.INERTIA_MULTIPLIER_STANDING;
				break;

			case 1:	//walking
				return GunplayConstants.INERTIA_MULTIPLIER_WALKING;
				break;

			case 2:	//jogging
				return GunplayConstants.INERTIA_MULTIPLIER_JOGGING;
				break;
		}
		return 1;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the weapon
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierWeapon(Weapon_Base weapon){
		return weapon.GetWeight() * GunplayConstants.INERTIA_MULTIPLIER_WEAPON_WEIGHT;
	}
	
	/**
	*	@brief Get the inertia multiplier based on the weapon
	*	 @return float - inertia multiplier
	*/
	//@todo use m_PlayerPb.GetPlayerLoad() instead
	protected float getInertiaMultiplierInventoryWeight(){
		if(m_PlayerPb.GetWeight() == 0) { //@todo temp-fix for weight not updating. find a solution
			m_PlayerPb.UpdateWeight();
		}
		return m_PlayerPb.GetWeight() * GunplayConstants.INERTIA_MULTIPLIER_PLAYER_WEIGHT;
	}
	
	/**
	*	@brief Get the hipfire inertia multiplier
	*	 @return float - inertia multiplier
	*/
	protected float getInertiaMultiplierHipfire(){
		if(!m_PlayerDpi.IsInOptics() && !m_PlayerDpi.IsInIronsights()){
			return GunplayConstants.INERTIA_MULTIPLIER_HIPFIRE;
		}
		return 1;
	}
	
	
	
	
	

	/**
	*	@brief Get the user input aim change
	*	 @return vector - Aim change of the player (x, y, 0)
	*/
	vector getAimChangeDegree(){
		vector aimChange = "0 0 0";
		aimChange[0] = m_PlayerDpi.GetInputController().GetAimChange()[0] * Math.RAD2DEG;
		aimChange[1] = m_PlayerDpi.GetInputController().GetAimChange()[1] * Math.RAD2DEG;
		return aimChange;
	}
	
	/**
	*	@brief Get current aiming model hands offset
	*	 @return vector - Hands offset (x, y, 0);
	*/
	vector getHandsOffset(){
		return m_handsOffset;
	}
		
	/**
	*	@brief Get where the weapon is pointing
	*	 @return vector - Weapon target position
	*/
	vector getWeaponTargetPosition(){
		return m_weaponTargetPosition;
	}
	
	/**
	*	@brief Get relative position on screen (0.0 - 1.0) of the crosshair
	*	 @return vector - Relative screen position (x, y, 0);
	*/
	vector getSCrosshairPosition(){
		return m_sCrosshairPosition;
	}	
	
}