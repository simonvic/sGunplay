modded class DayZPlayerImplementAiming{
	
	protected float m_inertiaXVel[1];
	protected float m_inertiaYVel[1];
	
	protected vector m_sCrosshairPosition;
	protected bool m_isSCrosshairVisible;
	protected float m_sCrosshairXVel[1];
	protected float m_sCrosshairYVel[1];
	
	protected ref SRaycast m_sCrosshairRay;
	
	void DayZPlayerImplementAiming(DayZPlayerImplement player){
		m_sCrosshairRay = new SRaycast("0 0 0", "0 0 0", 0.05, ObjIntersectFire, CollisionFlags.NEARESTCONTACT);
	}
	
	override bool ProcessAimFilters(float pDt, SDayZPlayerAimingModel pModel, int stance_index){
		bool result = super.ProcessAimFilters(pDt, pModel, stance_index);

		Weapon_Base weapon = Weapon_Base.Cast(m_PlayerPb.GetItemInHands());
		updateSCrosshair(weapon, pDt);
		
		if(GunplayConstants.USE_WEAPON_INERTIA){
			applyWeaponInertia(pModel);
		}		
	
		if(!GunplayConstants.CAMERA_FOLLOWS_BREATHING_SWAY){
			updateSwayOffset(pModel);
		}
		
		return result;
	}
	
	
	
	
	
	/**
	*	@brief Apply the inertia to the given Aiming Model 
	*	 @param pModel \p SDayZPlayerAimingModel - Player aiming model
	*/
	protected void applyWeaponInertia(SDayZPlayerAimingModel pModel){
		float inertiaMultiplier = computeInertiaMultiplier(weapon);
			
		float aimChangeX = getAimChangeDegree()[0] * inertiaMultiplier;
		float aimChangeY = getAimChangeDegree()[1] * inertiaMultiplier;
	
		pModel.m_fAimXHandsOffset = Math.SmoothCD(pModel.m_fAimXHandsOffset, pModel.m_fAimXHandsOffset - aimChangeX, m_inertiaXVel, GunplayConstants.INERTIA_SMOOTHNESS, 1000, pDt);
		pModel.m_fAimYHandsOffset = Math.SmoothCD(pModel.m_fAimYHandsOffset, pModel.m_fAimYHandsOffset - aimChangeY, m_inertiaYVel, GunplayConstants.INERTIA_SMOOTHNESS, 1000, pDt);
	}
	
	
	/**
	*	@brief Update the crosshair position on the screen vector and its visibility
	*	 @param weapon \p Weapon_Base - Weapon used to get the direction of the raycast
	*/
	protected void updateSCrosshair(Weapon_Base weapon, float pDt){
		if(!GetGame().GetMission() || m_PlayerDpi.IsInIronsights() || m_PlayerDpi.IsInOptics()){
			m_isSCrosshairVisible = false;
		}else{
			m_isSCrosshairVisible = true;
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
	*	@brief Get the user input aim change
	*	 @return vector - Aim change of the player (x, y, 0)
	*/
	protected vector getAimChangeDegree(){
		vector aimChange = "0 0 0";
		aimChange[0] = m_PlayerDpi.GetInputController().GetAimChange()[0] * Math.RAD2DEG;
		aimChange[1] = m_PlayerDpi.GetInputController().GetAimChange()[1] * Math.RAD2DEG;
		return aimChange;
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
		inertiaMultiplier *= getStanceInertiaMultiplier();
		
		////////////////////////
		// MOVEMENT
		switch(m_PlayerDpi.m_MovementState.m_iMovement){ 
			case 0:	//standing
				inertiaMultiplier *= GunplayConstants.INERTIA_MULTIPLIER_STANDING;
				break;

			case 1:	//walking
				inertiaMultiplier *= GunplayConstants.INERTIA_MULTIPLIER_WALKING;
				break;

			case 2:	//jogging
				inertiaMultiplier *= GunplayConstants.INERTIA_MULTIPLIER_JOGGING;
				break;
			
			default: //flying? lol
				inertiaMultiplier *= 1;
		}
		
		////////////////////////
		// WEAPON WEIGHT
		inertiaMultiplier *= weapon.GetWeight() * GunplayConstants.INERTIA_MULTIPLIER_WEAPON_WEIGHT;
		
		////////////////////////
		// HIPFIRE 
		if(!m_PlayerDpi.IsInOptics() && !m_PlayerDpi.IsInIronsights()){
			inertiaMultiplier *= GunplayConstants.INERTIA_MULTIPLIER_HIPFIRE;
		}
		
		
		
		
		return inertiaMultiplier;
	}
		
	
	/**
	*	@brief Get the inertia multiplier based on the player stance
	*	 @return float - inertia multiplier
	*/
	protected float getStanceInertiaMultiplier(){
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
	*	@brief Untie the camera from the weapon sway
	*	 @param pModel \p SDayZPlayerAimingModel - Player aiming model
	*/
	protected void updateSwayOffset(SDayZPlayerAimingModel pModel){
		DayZPlayerCameraIronsights.m_weaponDeadzoneX = pModel.m_fAimXHandsOffset;
		DayZPlayerCameraIronsights.m_weaponDeadzoneY = pModel.m_fAimYHandsOffset;
	}
	
	
	vector getSCrosshairPosition(){
		return m_sCrosshairPosition;
	}
	
	bool isSCrosshairVisible(){
		return m_isSCrosshairVisible;
	}
	
	void setSCrosshairVisible(bool visible){
		m_isSCrosshairVisible = false;
	}
	
	
}