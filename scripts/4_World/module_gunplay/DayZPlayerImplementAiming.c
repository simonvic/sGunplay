modded class DayZPlayerImplementAiming{

	protected vector m_handsOffset;
	protected vector m_breathingSwayOffset;	
	protected float m_inertiaXVel[1];
	protected float m_inertiaYVel[1];
	
	protected vector m_sCrosshairPosition;
	protected float m_sCrosshairXVel[1];
	protected float m_sCrosshairYVel[1];
	
	protected ref SRaycast m_sCrosshairRay;
	
	void DayZPlayerImplementAiming(DayZPlayerImplement player){
		m_sCrosshairRay = new SRaycast("0 0 0", "0 0 0", 0.05, ObjIntersectFire, CollisionFlags.NEARESTCONTACT);
	}
	
	override bool ProcessAimFilters(float pDt, SDayZPlayerAimingModel pModel, int stance_index){
		bool result = super.ProcessAimFilters(pDt, pModel, stance_index);
		//pModel.m_fAimXHandsOffset *= 0;
		//pModel.m_fAimYHandsOffset *= 0;
		Weapon_Base weapon = Weapon_Base.Cast(m_PlayerPb.GetItemInHands());
		
		if(GunplayConstants.USE_WEAPON_INERTIA){
			applyWeaponInertia(pModel, computeInertiaMultiplier(weapon), pDt);
			updateHandsOffset(pModel);
		}		
	
		if(!GunplayConstants.CAMERA_FOLLOWS_BREATHING_SWAY){
			updateBreathingSwayOffset(pModel);
		}
		
		updateSCrosshair(weapon, pDt);
		
		return result;
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
	}
	
	/**
	*	@brief Update the current value of the breathing sway offset
	*	 @param pModel \p SDayZPlayerAimingModel - Player aiming model
	*/
	protected void updateBreathingSwayOffset(SDayZPlayerAimingModel pModel){
		m_breathingSwayOffset[0] = m_BreathingXAxisOffset;
		m_breathingSwayOffset[1] = m_BreathingYAxisOffset;
	}
	
	
	/**
	*	@brief Update the crosshair position on the screen vector and its visibility
	*	 @param weapon \p Weapon_Base - Weapon used to get the direction of the raycast
	*/
	protected void updateSCrosshair(Weapon_Base weapon, float pDt){
		if(GetGame().GetMission()){
			vector muzzlePosition = weapon.ModelToWorld(weapon.GetSelectionPositionLS( "usti hlavne" ));
			vector barrelPosition = weapon.ModelToWorld(weapon.GetSelectionPositionLS( "konec hlavne" ));
			vector target = barrelPosition + (vector.Direction(barrelPosition, muzzlePosition ) * GunplayConstants.CROSSHAIR_PRECISION);
			
			m_sCrosshairRay.setBegPos(muzzlePosition);
			m_sCrosshairRay.setEndPos(target);
			m_sCrosshairRay.launch();
			
			vector pos = GetGame().GetScreenPosRelative(m_sCrosshairRay.getContactPos());
			
			m_sCrosshairPosition[0] = Math.SmoothCD(m_sCrosshairPosition[0], pos[0], m_sCrosshairXVel, GunplayConstants.CROSSHAIR_SMOOTHNESS, 1000, pDt);
			m_sCrosshairPosition[1] = Math.SmoothCD(m_sCrosshairPosition[1], pos[1], m_sCrosshairYVel, GunplayConstants.CROSSHAIR_SMOOTHNESS, 1000, pDt);
		}
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
	*	@brief Get current aiming model breathing sway offset
	*	 @return vector - Hands offset (x, y, 0);
	*/
	vector getBreathingSwayOffset(){
		return m_breathingSwayOffset;
	}
	
	vector getSCrosshairPosition(){
		return m_sCrosshairPosition;
	}	
	
}