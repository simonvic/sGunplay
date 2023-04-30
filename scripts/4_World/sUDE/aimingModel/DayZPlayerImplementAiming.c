modded class DayZPlayerImplementAiming {
	
	protected Weapon_Base m_weapon;
	
	protected vector m_handsOffset;
	static vector m_misalignment;
	
	protected vector m_lensPosition;
	
	protected vector m_sCrosshairPosition;
	protected float m_sCrosshairXVel[1];
	protected float m_sCrosshairYVel[1];
	
	protected vector m_weaponBarrelPosition;
	protected vector m_weaponMuzzlePosition;
	protected vector m_weaponTargetPosition;
	
	protected ref SRaycast m_sCrosshairRay;
	
	protected ref array<ref AimingModelFilterBase> m_filters;
	
	void DayZPlayerImplementAiming(DayZPlayerImplement player) {
		m_sCrosshairRay = new SRaycast("0 0 0", "0 0 0", 0.01, ObjIntersectFire, CollisionFlags.NEARESTCONTACT);
		m_filters = new array<ref AimingModelFilterBase>();
		registerFilters();	
	}
	
	/**
	*	@brief Register the filters to be applied to the aiming model
	*	 @note The order matters! Filters operation may not be commutative
	*/
	protected void registerFilters() {
		registerFilter(new AimingModelFilterBreathing(this));
		registerFilter(new AimingModelFilterMovement(this));
		registerFilter(new AimingModelFilterShake(this));
		registerFilter(new AimingModelFilterRecoil(this));
		registerFilter(new AimingModelFilterKuru(this));
		registerFilter(new AimingModelFilterInertia(this));
		registerFilter(new AimingModelFilterHipfireDeadzone(this));
		registerFilter(new AimingModelFilterWallPush(this));
		registerFilter(new AimingModelFilterWeaponInteraction(this));
		registerFilter(new AimingModelFilterClamps(this));
	}
	
	/**
	*	@brief Register a filter
	*	 @param filter \p AimingModelFilterBase - Filter to register
	*/
	protected void registerFilter(AimingModelFilterBase filter) {
		if ((!filter || !m_filters) && m_filters.Find(filter) == -1) return;
		m_filters.Insert(filter);
	}
	
	//on raise begin doesn't get called when quickly changing weapon while lowering
	override void OnRaiseBegin(DayZPlayerImplement player) {
		super.OnRaiseBegin(player);
		foreach (AimingModelFilterBase filter : m_filters) {
			if (filter.isActive()) {
				filter.onRaiseBegin();
			}
		}
	}

	/**
	*	@brief Process all registered aiming model filters
	*	 @param pDt \p float - delta time
	*	 @param pModel \p SDayZPlayerAimingModel - aiming model values
	*	 @param stance_index \p ind - stance index
	*/
	override bool ProcessAimFilters(float pDt, SDayZPlayerAimingModel pModel, int stance_index) {
		/* @todo process aim filters keeps getting called even after holstered weapon.
			to activae quickly releas right mouse button, holster weapon, and right mouse button again 
		*/
		m_weapon = Weapon_Base.Cast(m_PlayerPb.GetHumanInventory().GetEntityInHands());
		if (!m_weapon) return true;
		foreach (AimingModelFilterBase filter : m_filters) {
			if (filter.isActive()) {
				filter.onUpdate(pDt, pModel, stance_index);
			}
		}
		
		updateHandsOffset(pModel);
		updateMisalignment(pModel);
		
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
		
		//The lens must be computed in the aiming model after all filters transformations
		updateOpticLensPosition(m_weapon.GetAttachedOptics());
		
		return true;
	}
	
	
	/**
	*	@brief Update the current value of the hands offset
	*	 @param pModel \p SDayZPlayerAimingModel - Player aiming model
	*/
	protected void updateHandsOffset(SDayZPlayerAimingModel pModel) {
		m_handsOffset[0] = pModel.m_fAimXHandsOffset;
		m_handsOffset[1] = pModel.m_fAimYHandsOffset;
	}
	
	
	/**
	*	@brief Update the current value of the misalignment
	*	 @param pModel \p SDayZPlayerAimingModel - Player aiming model
	*/
	protected void updateMisalignment(SDayZPlayerAimingModel pModel) {
		m_misalignment[0] = pModel.m_fAimXCamOffset;
		m_misalignment[1] = pModel.m_fAimYCamOffset;
	}
	

	/**
	*	@brief Update the crosshair position on the screen vector and its visibility
	*	 @param weapon \p Weapon_Base - Weapon used to get the direction of the raycast
	*/
	protected void updateSCrosshair(float pDt, Weapon_Base weapon, vector from, vector to, float distance = 1) {
		m_sCrosshairRay.from(from);
		m_sCrosshairRay.to(from + (vector.Direction(from, to) * distance));
		m_sCrosshairRay.ignore(weapon, m_PlayerPb);
		m_sCrosshairRay.launch();
		
		vector pos = GetGame().GetScreenPosRelative(m_sCrosshairRay.getContactPosition());
		
		m_sCrosshairPosition[0] = Math.SmoothCD(m_sCrosshairPosition[0], pos[0], m_sCrosshairXVel, GunplayConstants.CROSSHAIR_SMOOTHNESS, 1000, pDt);
		m_sCrosshairPosition[1] = Math.SmoothCD(m_sCrosshairPosition[1], pos[1], m_sCrosshairYVel, GunplayConstants.CROSSHAIR_SMOOTHNESS, 1000, pDt);
	}
	
	PlayerBase getPlayer() {
		return m_PlayerPb;
	}
	
	Weapon_Base getWeapon() {
		return m_weapon;
	}
	
	vector getCamShake() {
		return Vector(m_CamShakeX, m_CamShakeY, 0);
	}
	
	/**
	*	@brief Compute the optic lens position
	*/
	protected void updateOpticLensPosition(ItemOptics optic, float distance = 50) {
		if (!optic) return;
		vector eyeScopeLS  = optic.GetSelectionPositionLS( "eyeScope" );
		vector cameraDirLS = optic.GetSelectionPositionLS( "cameraDir" );
		m_lensPosition = optic.ModelToWorld(eyeScopeLS + (vector.Direction(eyeScopeLS, cameraDirLS) * distance));
	}
	
	/**
	*	@brief Get the computed position of where the optic lens should be
	*	 @return vector - Position in WS
	*/
	vector getLensPositionWS() {
		return m_lensPosition;
	}

	
	/**
	*	@brief Get the user input aim change per tick in radians
	*	 @return vector - Aim change of the player (x, y, 0)
	*/
	vector getAimChangeRadians() {
		return getPlayer().GetInputController().GetAimChange();
	}
	
	/**
	*	@brief Get the user input aim change per tick in degrees
	*	 @return vector - Aim change of the player (x, y, 0)
	*/
	vector getAimChangeDegree() {
		vector radians = getAimChangeRadians();
		return Vector(radians[0] * Math.RAD2DEG, radians[1] * Math.RAD2DEG, 0);
	}
	
	/**
	*	@brief Get the user input aim change (frame-indipendent) in radians
	*	 @return vector - Aim change of the player (x, y, 0)
	*/
	vector getAimDeltaRadians(float dt) {
#ifdef DAYZ_1_21
		return getPlayer().GetInputController().GetAimDelta(dt);
#else
		return getPlayer().GetInputController().GetAimChange();
#endif
	}
	
	/**
	*	@brief Get the user input aim change (frame-indipendent) in degree
	*	 @return vector - Aim change of the player (x, y, 0)
	*/
	vector getAimDeltaDegree(float dt) {
		vector radians = getAimDeltaRadians(dt);
		return Vector(radians[0] * Math.RAD2DEG, radians[1] * Math.RAD2DEG, 0);
	}
	
	
	/**
	*	@brief Get current aiming model hands offset
	*	 @return vector - Hands offset (x, y, 0);
	*/
	vector getHandsOffset() {
		return m_handsOffset;
	}
	
	/**
	*	@brief Get current aiming model hands offset
	*	 @return vector - Hands offset (x, y, 0);
	*/
	vector getMisalignment() {
		return m_misalignment;
	}
		
	/**
	*	@brief Get where the weapon is pointing
	*	 @return vector - Weapon target position
	*/
	vector getWeaponTargetPosition() {
		return m_weaponTargetPosition;
	}
	
	/**
	*	@brief Get relative position on screen (0.0 - 1.0) of the crosshair
	*	 @return vector - Relative screen position (x, y, 0);
	*/
	vector getSCrosshairPosition() {
		return m_sCrosshairPosition;
	}	
	
	/**
	*	@brief Get the current Kuru shake. 
	*	 @return current kuru shake, null if not present
	*/
	KuruShake getKuruShake() {
		return m_KuruShake;
	}
	
	/**
	*	@brief Get the current recoil . 
	*	 @return current recoil, null if not present
	*/
	RecoilBase getRecoil() {
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
	static void getWeaponComponentsPositionLS(Weapon_Base weapon, out vector barrelPosition, out vector muzzlePosition, out vector targetPosition, float distance = 1) {
		barrelPosition = weapon.GetSelectionPositionLS( "konec hlavne" );
		muzzlePosition = weapon.GetSelectionPositionLS( "usti hlavne" );
		targetPosition = muzzlePosition + (vector.Direction(barrelPosition, muzzlePosition ) * distance);
	}
	
	/**
	*	@brief Get the barrel position, muzzle position and the target position at the given distance in WORLD SPACE
	*	 @param weapon \p Weapon_Base - 
	*	 @param barrelPosition \p vector - 
	*	 @param muzzlePosition \p vector - 
	*	 @param targetPosition \p vector - 
	*	 @param distance \p float - 
	*/
	static void getWeaponComponentsPositionWS(Weapon_Base weapon, out vector barrelPosition, out vector muzzlePosition, out vector targetPosition, float distance = 1) {
		barrelPosition = weapon.ModelToWorld(weapon.GetSelectionPositionLS( "konec hlavne" ));
		muzzlePosition = weapon.ModelToWorld(weapon.GetSelectionPositionLS( "usti hlavne" ));
		targetPosition = muzzlePosition + (vector.Direction(barrelPosition, muzzlePosition ) * distance);
	}
	
}