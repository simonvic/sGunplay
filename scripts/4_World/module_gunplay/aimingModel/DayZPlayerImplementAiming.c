typedef array<ref AimingModelFilterBase> TAimingModelFiltersList;

modded class DayZPlayerImplementAiming{
	
	protected Weapon_Base m_weapon;
	
	protected vector m_handsOffset;
	
	protected vector m_lensPosition;
	
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
	
	/**
	*	@brief Register the filters to be applied to the aiming model
	*	 @note The order matters! Filters operation may not be commutative
	*/
	protected void registerFilters(){
		//@todo add cam shake
		registerFilter(new AimingModelFilterBreathing(this));
		registerFilter(new AimingModelFilterMovement(this));
		registerFilter(new AimingModelFilterShake(this));
		registerFilter(new AimingModelFilterRecoil(this));
		registerFilter(new AimingModelFilterKuru(this));
		registerFilter(new AimingModelFilterInertia(this));
		registerFilter(new AimingModelFilterWallPush(this));
	}
	
	/**
	*	@brief Register a filter
	*	 @param filter \p AimingModelFilterBase - Filter to register
	*/
	protected void registerFilter(AimingModelFilterBase filter){
		if((!filter || !m_filters) && m_filters.Find(filter) == -1) return;
		m_filters.Insert(filter);
	}
	
	
	//on raise begin doesn't get called when quickly changing weapon while lowering
	override void OnRaiseBegin(DayZPlayerImplement player){
		super.OnRaiseBegin(player);
	}
	
	//@todo update all aiming model variables from the filter, so we don't break other mods that use them
	override void OnSwayStateChange(int state){
		super.OnSwayStateChange(state);
	}
	
	/**
	*	@brief Process all registered aiming model filters
	*	 @param pDt \p float - delta time
	*	 @param pModel \p SDayZPlayerAimingModel - aiming model values
	*	 @param stance_index \p ind - stance index
	*/
	override bool ProcessAimFilters(float pDt, SDayZPlayerAimingModel pModel, int stance_index){
		/* @todo process aim filters keeps getting called even after holstered weapon.
			to activae quickly releas right mouse button, holster weapon, and right mouse button again 
		*/
		m_weapon = Weapon_Base.Cast(m_PlayerPb.GetHumanInventory().GetEntityInHands());
		if(!m_weapon) return true;
		foreach(AimingModelFilterBase filter : m_filters){
			if(filter.isActive()){
				filter.onUpdate(pDt, pModel, stance_index);
			}
		}
		
		// @todo finish this and double check everything
		//if (stance_index == DayZPlayerConstants.STANCEIDX_RAISEDPRONE){			
		//	float newVal = DayZPlayerUtils.LinearRangeClamp(pModel.m_fCurrentAimX, pModel.m_fCurrentAimY, m_AimXClampRanges);
		//	pModel.m_fAimYHandsOffset += newVal - pModel.m_fCurrentAimY;
		//}
		
		updateHandsOffset(pModel);
		
		//get positions in local space so we don't lose precision
		DayZPlayerImplementAiming.getWeaponComponentsPositionLS(
			m_weapon,
			m_weaponBarrelPosition,
			m_weaponMuzzlePosition,
			m_weaponTargetPosition); 
		
		
		updateSCrosshair(pDt, 
			m_weapon, 
			m_weapon.ModelToWorld(m_weaponMuzzlePosition),
			m_weapon.ModelToWorld(m_weaponTargetPosition),
			GunplayConstants.CROSSHAIR_PRECISION);
		
		//The lens must be computed in the aiming model after all filters transformation
		updateOpticLensPosition(m_weapon.GetAttachedOptics());
		
		return true;
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
	protected void updateSCrosshair(float pDt, Weapon_Base weapon, vector from, vector to, float distance = 1){
		m_sCrosshairRay.from(from);
		m_sCrosshairRay.to(from + (vector.Direction(from, to) * distance));
		m_sCrosshairRay.ignore(weapon, m_PlayerPb);
		m_sCrosshairRay.launch();
		
		vector pos = GetGame().GetScreenPosRelative(m_sCrosshairRay.getContactPosition());
		
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
	*	@brief Compute the optic lens position
	*/
	protected void updateOpticLensPosition(ItemOptics optic, float distance = 50){
		if(!optic) return;
		
		vector from = optic.GetSelectionPositionLS( "eyeScope" );
		vector to = optic.GetSelectionPositionLS( "cameraDir" );
		m_lensPosition = optic.ModelToWorld(from + (vector.Direction(from, to) * distance));
	}
	
	/**
	*	@brief Get the computed position of where the optic lens should be
	*	 @return vector - Position in WS
	*/
	vector getLensPositionWS(){
		return m_lensPosition;
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
	*	@brief Get the current Kuru shake. 
	*	 @return current kuru shake, null if not present
	*/
	KuruShake getKuruShake(){
		return m_KuruShake;
	}
	
	/**
	*	@brief Get the current recoil . 
	*	 @return current recoil, null if not present
	*/
	RecoilBase getRecoil(){
		return m_CurrentRecoil;
	}
	
	
	/**
	*	@brief Get the barrel position, muzzle position and the target position at the given distance in LOCAL SPACE
	*	 @param weapon \p Weapon_Base - 
	*	 @param barrelPosition \p vector - 
	*	 @param muzzlePosition \p vector - 
	*	 @param targetPosition \p vector - 
	*	 @param distance \p float - 
	*/
	static void getWeaponComponentsPositionLS(Weapon_Base weapon, out vector barrelPosition, out vector muzzlePosition, out vector targetPosition, float distance = 1){
		barrelPosition = weapon.GetSelectionPositionLS( "konec hlavne" );
		muzzlePosition = weapon.GetSelectionPositionLS( "usti hlavne" );
		targetPosition = muzzlePosition + (vector.Direction(barrelPosition, muzzlePosition ) * distance);
		//@todo try this. Thanks Mario :)
		//vector barrelPosition = weapon.GetSelectionPositionLS("usti hlavne");
		//vector muzzlePosition = weapon.GetSelectionPositionLS("konec hlavne");
		//vector directionLS = vector.Direction(barrelPosition, muzzlePosition);
		//vector direction = directionLS[0] * weapon.GetTransformAxis(0);
	}
	
	/**
	*	@brief Get the barrel position, muzzle position and the target position at the given distance in WORLD SPACE
	*	 @param weapon \p Weapon_Base - 
	*	 @param barrelPosition \p vector - 
	*	 @param muzzlePosition \p vector - 
	*	 @param targetPosition \p vector - 
	*	 @param distance \p float - 
	*/
	static void getWeaponComponentsPositionWS(Weapon_Base weapon, out vector barrelPosition, out vector muzzlePosition, out vector targetPosition, float distance = 1){
		barrelPosition = weapon.ModelToWorld(weapon.GetSelectionPositionLS( "konec hlavne" ));
		muzzlePosition = weapon.ModelToWorld(weapon.GetSelectionPositionLS( "usti hlavne" ));
		targetPosition = muzzlePosition + (vector.Direction(barrelPosition, muzzlePosition ) * distance);
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