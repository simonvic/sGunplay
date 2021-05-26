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
		registerFilter(new AimingModelFilterMovement(this));
		registerFilter(new AimingModelFilterInertia(this));
		//registerFilter(new AimingModelInjuryFilter(this)); //added as a child filter to the movement filter
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
	
	PlayerBase getPlayer(){
		return m_PlayerPb;
	}
	
	Weapon_Base getWeapon(){
		return m_weapon;
	}
	
	/**
	*	@brief Get the user input aim change
	*	 @return vector - Aim change of the player (x, y, 0)
	*/
	vector getAimChangeDegree(){
		return DayZPlayerImplementAiming.getAimChangeDegree(m_PlayerDpi);
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
	*	@brief Get the user input aim change
	*	 @param player \p DayZPlayerImplement player
	*	 @return vector - Aim change of the player (x, y, 0)
	*/
	static vector getAimChangeDegree(DayZPlayerImplement player){
		vector aimChange = "0 0 0";
		aimChange[0] = player.GetInputController().GetAimChange()[0] * Math.RAD2DEG;
		aimChange[1] = player.GetInputController().GetAimChange()[1] * Math.RAD2DEG;
		return aimChange;
	}
	
}