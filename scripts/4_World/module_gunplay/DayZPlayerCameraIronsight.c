//////////////////////////////////////////
// IRONSIGHT
modded class DayZPlayerCameraIronsights{
	
	protected float m_focusVel[1];
	protected float m_focusTargetFOV;
	protected float m_focusSpeed;
	protected DayZPlayer m_player;
	
	protected vector m_inspectAngles;
	protected float m_inspectVelX[1];
	protected float m_inspectVelY[1];
	
	protected vector m_freelookAngles;
	protected float m_freelookVelX[1];
	protected float m_freelookVelY[1];
	
	protected float m_deadzoneX;
	protected float m_deadzoneY;
	static float m_weaponDeadzoneX;
	static float m_weaponDeadzoneY;
	
	protected float m_prevCameraTM[4];
	
	protected float m_offsetXResetVel[1];
	protected float m_offsetYResetVel[1];	
	
	protected float m_deadzoneXVel[1];
	protected float m_deadzoneYVel[1];
	
	
	
	void DayZPlayerCameraIronsights(DayZPlayer pPlayer, HumanInputController pInput){
		m_player = pPlayer;	
	}
		
	override void AdjustCameraParameters(float pDt, inout DayZPlayerCameraResult pOutResult){	
		m_iBoneIndex = m_pPlayer.GetBoneIndexByName("RightHand_Dummy");
		if(m_iBoneIndex == -1 ) m_iBoneIndex = m_pPlayer.GetBoneIndexByName("Head");
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
	
	override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult){		
		
		updateAimAngle(m_fLeftRightAngle, m_CurrentCameraPitch, pDt);
		
		////////////////////////////////////////////////

		float aimChangeX = m_pInput.GetAimChange()[0] * Math.RAD2DEG;
		float aimChangeY = m_pInput.GetAimChange()[1] * Math.RAD2DEG;
		
		
		////////////////////////
		// Weapon aiming matrix
		vector aimingTM[4];
		computeWeaponAimingMatrix(aimingTM);
		
		
		////////////////////////
		// Weapon cam point
		vector boneTM[4];
		if(GetCurrentSightEntity()){
			m_pPlayer.GetItemAccessor().WeaponGetCameraPointBoneRelative(GetCurrentSightEntity(), m_OpticsCamPos, m_OpticsCamDir, m_iBoneIndex, boneTM);
			//m_pPlayer.GetItemAccessor().WeaponGetCameraPointMSTransform(GetCurrentSightEntity(), m_OpticsCamPos, dummyDir, positionTM);
		}
		
		
		////////////////////////
		// Inspection
		computeInspectAngles(aimChangeX, aimChangeY, m_inspectAngles, pDt);
		vector inspectTM[4];
		toMatrix(m_inspectAngles, inspectTM);
		
		////////////////////////
		// Freelook
		computeFreelookAngles(aimChangeX, aimChangeY, m_freelookAngles, pDt);
		vector freelookTM[4];
		toMatrix(m_freelookAngles, freelookTM);
		
		
		
		////////////////////////
		// Deadzone
		computeDeadzone(aimChangeX, aimChangeY, pDt, m_deadzoneX, m_deadzoneY);
		applyDeadzone(m_deadzoneX, m_deadzoneY, boneTM);


		float speed;
		vector localDirection;
		m_pInput.GetMovement(speed, localDirection);
		if(!playerIsFocusing()){
			Math3D.MatrixMultiply4(boneTM, freelookTM, boneTM);
		}else{
			Math3D.MatrixInvMultiply4(inspectTM, boneTM, boneTM);			
		}
		Math3D.MatrixMultiply4(aimingTM, boneTM, boneTM);
		Math3D.MatrixMultiply4(boneTM, pOutResult.m_CameraTM, pOutResult.m_CameraTM);

		
		////////////////////////
		// Other
		AdjustCameraParameters(pDt, pOutResult);
		updateFOVFocus(pDt, pOutResult);
	}
	
	
	
	
	protected void updateAimAngle(out float yaw, out float pitch, float pDt){
		float min;
		if (m_player && m_player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE))
			min = CONST_UD_MIN_BACK;
		else
			min = CONST_UD_MIN;
		
		pitch = UpdateUDAngle(m_fUpDownAngle, m_fUpDownAngleAdd, min, CONST_UD_MAX, pDt);
		yaw = UpdateLRAngle(m_fLeftRightAngle, CONST_LR_MIN, CONST_LR_MAX, pDt);
	}
	
	protected void computeInspectAngles(float x, float y, out vector angles, float pDt){
		if( m_pInput.CameraIsFreeLook() ){
			angles[0] = angles[0] - y;
			angles[2] = angles[2] + x;
		}else{
			if(m_pInput.IsFireModeChange() || m_pInput.IsZeroingUp() || m_pInput.IsZeroingDown()){
				angles[0] = angles[0] + 5;
				angles[2] = angles[2] + 5;
			}
			angles[0] = Math.SmoothCD(angles[0], 0, m_inspectVelX, 0.1, 1000, pDt);
			angles[2] = Math.SmoothCD(angles[2], 0, m_inspectVelY, 0.1, 1000, pDt);
		}
	}
	
	protected void computeFreelookAngles(float x, float y, out vector angles, float pDt){
		if( m_pInput.CameraIsFreeLook() ){
			angles[0] = angles[0] + x;
			angles[1] = angles[1] + y;
		}else{
			angles[0] = Math.SmoothCD(angles[0], 0, m_freelookVelX, 0.1, 1000, pDt);
			angles[1] = Math.SmoothCD(angles[1], 0, m_freelookVelY, 0.1, 1000, pDt);
		}
	}
	
	protected void computeWeaponAimingMatrix(out vector aimingTM[4]){
		m_pPlayer.GetItemAccessor().WeaponGetAimingModelDirTm(aimingTM);
	}
	
	protected void computeDeadzone(float aimChangeX, float aimChangeY, float pDt, out float deadzoneX, out float deadzoneY){
		
		TFloatArray deadzoneLimits = m_camManager.getDeadzoneLimits();

		if( m_pInput.CameraIsFreeLook() || (playerIsFocusing() && m_camManager.isResetDeadzoneOnFocusEnabled())){
			deadzoneX = Math.SmoothCD(deadzoneX, 0, m_offsetXResetVel, 0.3, 1000, pDt);
			deadzoneY = Math.SmoothCD(deadzoneY, 0, m_offsetYResetVel, 0.3, 1000, pDt);
		}else{
			deadzoneX = Math.Clamp(deadzoneX + aimChangeX, deadzoneLimits[3] * -20, deadzoneLimits[1] * 20);
			deadzoneY = Math.Clamp(deadzoneY + aimChangeY, deadzoneLimits[2] * -20, deadzoneLimits[0] * 20);
		}
	}
	
	protected vector toAngles(vector matrix[4]){
		return Math3D.MatrixToAngles(matrix);
	}
	
	protected void toMatrix(vector angles, out vector matrix[4]){
		Math3D.YawPitchRollMatrix(angles, matrix);
	}
	
	protected void applyDeadzone(float deadzoneX, float deadzoneY, out vector matrix[4]){
		vector angles = toAngles(matrix);
		
		//angles[0] = Math.SmoothCD(angles[0], angles[0] - deadzoneY, m_deadzoneYVel, 0.01, 1000, pDt);
		//angles[1] = Math.SmoothCD(angles[1], angles[1] + deadzoneX, m_deadzoneXVel, 0.01, 1000, pDt);		
		angles[0] = angles[0] - deadzoneY;
		angles[1] = angles[1] + deadzoneX;
		angles[2] = angles[2] + DayZPlayerImplement.Cast(m_player).m_MovementState.m_fLeaning * m_camManager.getHeadLeanAngle();
		
		toMatrix(angles, matrix);
		
	}
	
	
	
	
	
	
	
	
	
	
		
	protected void updateFOVFocus(float pDt, out DayZPlayerCameraResult pOutResult){
		m_focusTargetFOV = GetDayZGame().GetUserFOV(); //@todo a 10% more (less) fov perhaps?
		m_focusSpeed = GunplayConstants.FOCUS_RESET_SPEED;
	
		if(playerIsFocusing() && !m_pInput.CameraIsFreeLook()){
			m_focusTargetFOV = GameConstants.DZPLAYER_CAMERA_FOV_IRONSIGHTS;
			m_focusSpeed = getFocusSpeed();
		}
		m_fFovAbsolute = Math.SmoothCD(m_fFovAbsolute, m_focusTargetFOV, m_focusVel, m_focusSpeed, 1000, pDt);
	}
	
	protected bool playerIsFocusing(){
		return m_pPlayer.IsHoldingBreath();
	}
	
	/**
	* @brief Get the speed at which the player will reach maximum focus
	* 	@return \p float - focus spead
	*/
	protected float getFocusSpeed() {
		if(m_pPlayer.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDERECT | DayZPlayerConstants.STANCEMASK_ERECT)){
			return GunplayConstants.ERECT_FOCUS_SPEED;
		} else if(m_pPlayer.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDCROUCH | DayZPlayerConstants.STANCEMASK_CROUCH)){
			return GunplayConstants.CROUCH_FOCUS_SPEED;
		} else if(m_pPlayer.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE | DayZPlayerConstants.STANCEMASK_PRONE)){
			return GunplayConstants.PRONE_FOCUS_SPEED;
		} else {
			return 0.2;
		}
	}
	
	float getCurrentDeadzoneX(){
		return m_deadzoneX;
	}
	
	float getCurrentDeadzoneY(){
		return m_deadzoneY;
	}
	
	
}
