modded class DayZPlayerCameraIronsights {
	
	protected PlayerBase m_player;
	protected DayZPlayerImplementAiming m_aimingModel;
	
	protected float m_focusTargetFOV;
	protected float m_focusVel[1];
	protected float m_focusSpeed;
	
	protected vector m_inspectAngles;
	protected float m_inspectVelX[1];
	protected float m_inspectVelY[1];
	protected bool m_isInspectionDOFReset;
	
	protected vector m_freelookAngles;
	protected float m_freelookVelX[1];
	protected float m_freelookVelY[1];
	
	protected float m_deadzoneX;
	protected float m_deadzoneY;
	protected float m_deadzoneXVel[1];
	protected float m_deadzoneYVel[1];	
	
	protected float m_handsOffsetX;
	protected float m_handsOffsetY;
	protected float m_handsOffsetStartupTime;
	protected float m_handsOffsetResetVelX[1];
	protected float m_handsOffsetResetVelY[1];
	
	protected float m_offsetXResetVel[1];
	protected float m_offsetYResetVel[1];	
	
	protected ref DOFPresetWeaponInspect m_inspectDOFPreset = new DOFPresetWeaponInspect();
	protected static ref SCOFocusing m_scoFocusing = new SCOFocusing();
	
	
	void DayZPlayerCameraIronsights(DayZPlayer pPlayer, HumanInputController pInput) {
		m_player = PlayerBase.Cast(pPlayer);
		m_aimingModel = m_player.GetAimingModel();
		
		//just to be sure, other mods may need this :shrug:
		m_dynamicsSmoothTime = GunplayConstants.ADS_MOVEMENT_MISALIGNMENT_SMOOTHNESS;
		m_dynamicsStrength = GunplayConstants.ADS_MOVEMENT_MISALIGNMENT_STRENGTH;
		
		if (!SCameraOverlaysManager.getInstance().isActive(m_scoFocusing)) {
			SCameraOverlaysManager.getInstance().activate(m_scoFocusing);
		}
		
	}
		
		
	override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult) {
		updateDOF();
		updateAimAngle(m_fLeftRightAngle, m_CurrentCameraPitch, pDt);		
		computeHandsOffset(m_handsOffsetX, m_handsOffsetY, pDt);
		updateCamera(pDt, pOutResult);
		updateCameraShake(pDt);
		AdjustCameraParameters(pDt, pOutResult);
		updateFOVFocus(pDt, pOutResult);
		updateFocusingOverlay(pDt, pOutResult);
		UpdateBatteryOptics(GetCurrentSightEntity());
		UpdateCameraNV(m_player);
	}
	

	/**
	*	@brief Update the Depth of Field
	*/
	protected void updateDOF() {
		//@todo update m_isEntering
		if (m_player.isInspectingWeapon() && canInspectWeapon()) {
			SPPEManager.requestWeaponDOF(m_inspectDOFPreset);
			m_isInspectionDOFReset = true;
		} else if (m_isInspectionDOFReset) {
			setNonMagnifyingOpticDOF();
			m_isInspectionDOFReset = false;
		}
	}
	
	/**
	*	@brief Update Yaw and Pitch angles (used by other vanilla code)
	*	 @param yaw \p float - Yaw angle
	*	 @param pitch \p float - Pitch angle
	*/
	protected void updateAimAngle(out float yaw, out float pitch, float pDt) {
		float min;
		if (m_player && m_player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE)) {
			min = CONST_UD_MIN_BACK;
		} else {
			min = CONST_UD_MIN;
		}
		
		pitch = UpdateUDAngle(m_fUpDownAngle, m_fUpDownAngleAdd, min, CONST_UD_MAX, pDt);
		yaw = UpdateLRAngle(m_fLeftRightAngle, CONST_LR_MIN, CONST_LR_MAX, pDt);
	}
	
	/**
	*	@brief Compute the hands offset from the aiming model
	*	 @param handsOffsetX \p float - 
	*	 @param handsOffsetY \p float - 
	*/
	protected void computeHandsOffset(out float handsOffsetX, out float handsOffsetY, float pDt) {
		if (canApplyHandsOffset()) {
			
			// Linear interpolation (reset) to normal hands offset value
			if (m_handsOffsetStartupTime < 1) {
				handsOffsetX = Math.Lerp(handsOffsetX, m_aimingModel.getHandsOffset()[0], Easing.EaseInOutSine(m_handsOffsetStartupTime));
				handsOffsetY = Math.Lerp(handsOffsetY, m_aimingModel.getHandsOffset()[1], Easing.EaseInOutSine(m_handsOffsetStartupTime));
				m_handsOffsetStartupTime += 2 * pDt;
			} else {
				handsOffsetX = m_aimingModel.getHandsOffset()[0];
				handsOffsetY = m_aimingModel.getHandsOffset()[1];
			}
			
		} else {
			
			// Smooth interpolation hands offset to 0
			handsOffsetX = Math.SmoothCD(handsOffsetX, 0, m_handsOffsetResetVelX, GunplayConstants.RESET_SPEED_DEADZONE, 1000, pDt);
			handsOffsetY = Math.SmoothCD(handsOffsetY, 0, m_handsOffsetResetVelY, GunplayConstants.RESET_SPEED_DEADZONE, 1000, pDt);
			
			m_handsOffsetStartupTime = 0; //reset time for linear interpolation
		}
	}
	
	
	
	
	////////////////////////////////////////////////////////////////////////
	// CAMERA TRANSFORMATION
	
	/**
	*	@brief Update the camera based with user input
	*/
	protected void updateCamera(float pDt, out DayZPlayerCameraResult pOutResult) {

		float aimChangeX = m_aimingModel.getAimChangeDegree()[0];
		float aimChangeY = m_aimingModel.getAimChangeDegree()[1];
		
		////////////////////////
		// Weapon aiming matrix
		vector weaponAimingTM[4];
		computeWeaponAimingMatrix(weaponAimingTM);
		
		
		////////////////////////
		// Weapon cam point
		vector weaponCameraPointTM[4];
		if (GetCurrentSightEntity()) {
			m_pPlayer.GetItemAccessor().WeaponGetCameraPointBoneRelative(GetCurrentSightEntity(), m_OpticsCamPos, m_OpticsCamDir, m_iBoneIndex, weaponCameraPointTM);
			//m_pPlayer.GetItemAccessor().WeaponGetCameraPointMSTransform(GetCurrentSightEntity(), m_OpticsCamPos, dummyDir, positionTM);
		}
		
		////////////////////////
		// Inspection
		computeInspectAngles(aimChangeX, aimChangeY, m_inspectAngles, pDt);
		vector inspectTM[4];
		Math3D.YawPitchRollMatrix(m_inspectAngles, inspectTM);		
		
		////////////////////////
		// Freelook
		computeFreelookAngles(aimChangeX, aimChangeY, m_freelookAngles, pDt);
		vector freelookTM[4];
		Math3D.YawPitchRollMatrix(m_freelookAngles, freelookTM);	
		
		
		////////////////////////
		// Deadzone
		computeDeadzone(aimChangeX, aimChangeY, m_deadzoneX, m_deadzoneY, pDt);
		
		
		////////////////////////
		// Offset from center (deadzone + hands offset)
		applyOffset(pOutResult.m_CameraTM);

		
		Math3D.MatrixInvMultiply4(inspectTM, weaponCameraPointTM, weaponCameraPointTM);            //apply inspect transformation matrix
		Math3D.MatrixMultiply4(weaponCameraPointTM, freelookTM, weaponCameraPointTM);              //apply freelook transformation matrix
		Math3D.MatrixMultiply4(weaponAimingTM, weaponCameraPointTM, weaponCameraPointTM);          //apply weapon aiming transformation matrix
		Math3D.MatrixMultiply4(weaponCameraPointTM, pOutResult.m_CameraTM, pOutResult.m_CameraTM); //apply result to camera
	}
	
	/**
	*	@brief Update the camera shake values
	*/
	protected void updateCameraShake(float pDt) {
		if (m_CameraShake) {
			float x,y;
			m_CameraShake.Update(pDt, x, y);
			m_player.GetAimingModel().SetCamShakeValues(x, y);
		}
	}
	
	/**
	*	@brief Compute the transformation matrix for the weapon aiming model direction
	*/
	protected void computeWeaponAimingMatrix(out vector aimingTM[4]) {
		m_pPlayer.GetItemAccessor().WeaponGetAimingModelDirTm(aimingTM);
	}
	
	
	/**
	*	@brief Compute the angles of the camera when inspecting the weapon
	*	 @param x \p float -
	*	 @param y \p float -
	*	 @param angles \p vector - Result angles
	*/
	protected void computeInspectAngles(float x, float y, out vector angles, float pDt) {
		if (canInspectWeapon()) {
			angles[0] = Math.Clamp(angles[0] - y, GunplayConstants.ANGLES_CONSTRAINT_WEAPON_INSPECT[3], GunplayConstants.ANGLES_CONSTRAINT_WEAPON_INSPECT[0]);
			angles[2] = Math.Clamp(angles[2] + x, GunplayConstants.ANGLES_CONSTRAINT_WEAPON_INSPECT[1], GunplayConstants.ANGLES_CONSTRAINT_WEAPON_INSPECT[2]);
		} else {
			angles[0] = Math.SmoothCD(angles[0], 0, m_inspectVelX, GunplayConstants.RESET_SPEED_INSPECTION, 1000, pDt);
			angles[2] = Math.SmoothCD(angles[2], 0, m_inspectVelY, GunplayConstants.RESET_SPEED_INSPECTION, 1000, pDt);
		}
	}
	
	/**
	*	@brief Compute the angles of the camera when freelook
	*	 @param x \p float -
	*	 @param y \p float -
	*	 @param angles \p vector - Result angles	
	*/
	protected void computeFreelookAngles(float x, float y, out vector angles, float pDt) {
		if (canFreelook()) {
			angles[0] = Math.Clamp(angles[0] + x, GunplayConstants.ANGLES_CONSTRAINT_FREELOOK[3], GunplayConstants.ANGLES_CONSTRAINT_FREELOOK[0]);
			angles[1] = Math.Clamp(angles[1] + y, GunplayConstants.ANGLES_CONSTRAINT_FREELOOK[1], GunplayConstants.ANGLES_CONSTRAINT_FREELOOK[2]);
		} else {
			angles[0] = Math.SmoothCD(angles[0], 0, m_freelookVelX, GunplayConstants.RESET_SPEED_FREELOOK, 1000, pDt);
			angles[1] = Math.SmoothCD(angles[1], 0, m_freelookVelY, GunplayConstants.RESET_SPEED_FREELOOK, 1000, pDt);
		}
	}
	
		
	/**
	*	@brief Compute the angles of the camera for the deadzone
	*	 @param aimChangeX \p float -
	*	 @param aimChangeX \p float -
	*	 @param deadzoneX \p float - Result deadzone X
	*	 @param deadzoneX \p float - Result deadzone Y	
	*/
	protected void computeDeadzone(float aimChangeX, float aimChangeY, out float deadzoneX, out float deadzoneY, float pDt) {
		if (canApplyDeadzone()) {
			TFloatArray deadzoneLimits = getDeadzoneLimits();
			deadzoneX = Math.Clamp(deadzoneX + aimChangeX, deadzoneLimits[3] * -20, deadzoneLimits[1] * 20);
			deadzoneY = Math.Clamp(deadzoneY + aimChangeY, deadzoneLimits[2] * -20, deadzoneLimits[0] * 20);
		} else {
			deadzoneX = Math.SmoothCD(deadzoneX, 0, m_offsetXResetVel, GunplayConstants.RESET_SPEED_DEADZONE, 1000, pDt);
			deadzoneY = Math.SmoothCD(deadzoneY, 0, m_offsetYResetVel, GunplayConstants.RESET_SPEED_DEADZONE, 1000, pDt);
		}
	}
	
	
	/**
	*	@brief Apply final offset to matrix 
	*	 @param matrix \p vector[4] - Matrix to apply offset to
	*/	
	protected void applyOffset(out vector matrix[4]) {
		vector angles = Math3D.MatrixToAngles(matrix);
		
		angles[0] = angles[0] - m_deadzoneX - m_handsOffsetX;
		angles[1] = angles[1] - m_deadzoneY - m_handsOffsetY;
		
		Math3D.YawPitchRollMatrix(angles, matrix);
		
	}
	
	
	
	////////////////////////////////////////////////////////////////////////
	// CAMERA PARAMETERS
	
	/**
	*	@brief Adjust camera result parameters. Called by vanilla
	*/
	override void AdjustCameraParameters(float pDt, inout DayZPlayerCameraResult pOutResult) {	
		m_iBoneIndex = m_pPlayer.GetBoneIndexByName("RightHand_Dummy");
		pOutResult.m_iDirectBone 			= m_iBoneIndex;
		pOutResult.m_iDirectBoneMode 		= 3;
	
		pOutResult.m_fFovAbsolute = m_fFovAbsolute;
		pOutResult.m_fFovMultiplier = 1.0;
		
		pOutResult.m_bUpdateWhenBlendOut	= false;
		pOutResult.m_fDistance 				= 0;
		pOutResult.m_fUseHeading 			= 0.0;
		pOutResult.m_fInsideCamera 			= 1.0;
		pOutResult.m_fShootFromCamera		= 0.0;
		pOutResult.m_fIgnoreParentRoll      = 0.0;
		pOutResult.m_fNearPlane = 0.01; //0.07 default
	}
	
	
	/**
	*	@brief Update the FoV
	*	@param delta time
	*	@param camera result
	*/	
	protected void updateFOVFocus(float pDt, out DayZPlayerCameraResult pOutResult) {
		computeFOVFocusValues(m_focusTargetFOV, m_focusSpeed);
		m_fFovAbsolute = Math.SmoothCD(m_fFovAbsolute, m_focusTargetFOV, m_focusVel, m_focusSpeed, 1000, pDt);
	}
	
	
	/**
	*	@brief Update the focus camera overlay
	*	@param delta time
	*	@param camera result
	*/
	protected void updateFocusingOverlay(float pDt, DayZPlayerCameraResult pOutResult) {
		m_scoFocusing.setRestingFOV(getRestingFOV());
		m_scoFocusing.setFocusingFOV(m_focusTargetFOV);
	}
	
	/**
	*	@brief Get FoV value at resting state
	*	@return fov
	*/
	protected float getRestingFOV() {
		return Math.Max(GetDayZGame().GetUserFOV() * userCfgGunplay.getAdsFOVMultiplier(), GameConstants.DZPLAYER_CAMERA_FOV_IRONSIGHTS);
	}
	
	
	/**
	*	@brief Compute the targeted FOV and focusing speed
	*	 @param targetFOV \p float - fov computed
	*	 @param speed \p float - speed computed
	*/
	protected void computeFOVFocusValues(out float targetFOV, out float speed) {
		if (canZoom()) {
			targetFOV = GameConstants.DZPLAYER_CAMERA_FOV_IRONSIGHTS;
			speed = getFocusSpeedStance() * GunplayConstants.FOCUS_SPEED_IRONSIGHT_MULTIPLIER;
		} else {
			targetFOV = getRestingFOV();
			speed = GunplayConstants.FOCUS_RESET_SPEED;
		}
		
	}
			
	/**
	* @brief Get the focus speed based on the stance at which the player will reach maximum focus
	* 	@return \p float - focus speed
	*/
	protected float getFocusSpeedStance() {
		if (m_pPlayer.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDERECT | DayZPlayerConstants.STANCEMASK_ERECT)) {
			return GunplayConstants.FOCUS_SPEED_ERECT;
		} else if (m_pPlayer.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDCROUCH | DayZPlayerConstants.STANCEMASK_CROUCH)) {
			return GunplayConstants.FOCUS_SPEED_CROUCHED;
		} else if (m_pPlayer.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE | DayZPlayerConstants.STANCEMASK_PRONE)) {
			return GunplayConstants.FOCUS_SPEED_PRONE;
		} else {
			return 0.2;
		}
	}
	
	
	
	////////////////////////////////////////////////////////////////////////
	// CAMERA POST PROCESSING
	
	/**
	*	@brief Set camera Post Processing stuff, called by vanilla
	*/
	override void SetCameraPP(bool state, DayZPlayerCamera launchedFrom) {
		if (needPPEReset(state, launchedFrom)) {
			resetPPE();
			return;
		}
		
		SPPEManager.resetMask();
		SPPEManager.resetOpticLens();
		setNonMagnifyingOpticDOF();
		checkForNVGoggles();
		hideWeaponBarrel(false);
		
	}
	
	protected void resetPPE() {
		SPPEManager.resetMask();
		SPPEManager.resetOpticLens();
		SPPEManager.resetWeaponDOF();
		checkForNVGoggles();
		hideWeaponBarrel(false);
	}
	
	
	/**
	*	@brief Check if camera post processing effect has to be reset
	*/
	protected bool needPPEReset(bool state, DayZPlayerCamera launchedFrom) {
		return !state || !m_weaponUsed || m_player && launchedFrom != m_player.GetCurrentPlayerCamera());
	}
		

	/**
	*	@brief Set the depth of field based on current sight (optic or ironsight)
	*/
	protected void setNonMagnifyingOpticDOF() {

		// No weapon used (handeld optic?)
		if (!m_weaponUsed || !isAdsDOFEnabled()) {
			SPPEManager.resetWeaponDOF();
			return;
		}
		
		DoFPreset dof = getCurrentSightDOF();
		if (dof) {
			SPPEManager.requestWeaponDOF(dof);
		}
	}
	
	/**
	*	@brief Update the night vision based on the optics
	*	 @param allowNightVisionGoggles \p bool - if night vision should be applied if no optic is used (ironsight)
	*/
	protected void updateNightVision(bool allowsNVGoggles) {
		if (!m_opticsUsed.IsNVOptic()) {
			if (allowsNVGoggles) {
				checkForNVGoggles();
			} else {
				SetNVPostprocess(NVTypes.NONE);
			}
			return;
		}
		
		if (m_opticsUsed.IsWorking()) {
			SetCameraNV(true);
			SetNVPostprocess(m_opticsUsed.GetCurrentNVType());
		} else {
			SetCameraNV(false);
			SetNVPostprocess(NVTypes.NV_OPTICS_OFF);
		}
		
	}
	
	/**
	*	@brief Check if the current camera is night vision (night vision goggles)
	*/
	protected void checkForNVGoggles() {
		if (IsCameraNV()) {
			SetNVPostprocess(GetCameraNVType());
		} else {
			SetNVPostprocess(NVTypes.NONE);
		}
	}
	
	/**
	*	@brief Toggle the weapon barrel visibility
	*	 @param hidden \p bool - visibility of the weapon barrel
	*/
	protected void hideWeaponBarrel(bool hidden) {
		if (m_weaponUsed) {
			m_weaponUsed.HideWeaponBarrel(hidden);
		}
	}
	
	/**
	*	@brief Get the current sight (weapon, optic or backup ironsigh) Depth of Field
	*	 @return dof \p DoFPreset - Result Depth of field, null if not enabled or can't load it from cfg
	*/
	protected DoFPreset getCurrentSightDOF() {
		DoFPreset dof = new DoFPreset();
		temp_array = {};
		if (m_opticsUsed && m_opticsUsed.GetOpticsDOF().Count() == 6) {
			temp_array = m_opticsUsed.GetOpticsDOF();
		} else {
			temp_array = m_weaponUsed.GetWeaponDOF();
		}
		
		//@todo find a proper way to reduce the ads dof
		if (temp_array.Count() == 6 && temp_array[0]) {//correctly got the array from config and DOF is enabled (0 or 1)
			//                   blur,         focus distance, focuse length, fLength near,  fDepthOffset,  fMinDistance, fMaxDistance
			dof.initPreset(temp_array[4] * getAdsDOFIntensity(), temp_array[1], temp_array[2], temp_array[3] * getAdsDOFIntensity(), temp_array[5], 1, 100);
			return dof;
		}
		return null; 
	}
	
	
	
	float getCurrentDeadzoneX() {
		return m_deadzoneX;
	}
	
	float getCurrentDeadzoneY() {
		return m_deadzoneY;
	}

	
	protected bool playerIsFocusing() {
		return m_pPlayer.IsHoldingBreath();
	}
	
	protected bool canApplyDeadzone() {
		return !m_pInput.CameraIsFreeLook() && !m_player.isInspectingWeapon() && !isNVOptic() && !(playerIsFocusing() && isResetDeadzoneOnFocusEnabled());
	}
	
	protected bool canApplyHandsOffset() {
		return !isSniperOptic() && !isNVOptic();
	}
	
	protected bool canZoom() {
		return playerIsFocusing() && !m_pInput.CameraIsFreeLook() && !m_player.isInspectingWeapon();
	}
	
	protected bool canFreelook() {
		return m_pInput.CameraIsFreeLook() && !m_player.isInspectingWeapon();
	}
	
	protected bool canInspectWeapon() {
		return m_player.isInspectingWeapon();
	}
	
	protected bool isMagnifyingOptic() {
		return false;
	}
	
	protected bool isSniperOptic() {
		return false;
	}
	
	protected bool isNVOptic() {
		return m_opticsUsed && m_opticsUsed.IsNVOptic();
	}
	
	protected bool isHandHeldOptic() {
		return !m_weaponUsed && m_opticsUsed;
	}
	
}
