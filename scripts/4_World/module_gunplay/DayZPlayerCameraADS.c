modded class DayZPlayerCameraIronsights{
	
	protected float m_focusVel[1];
	protected float m_focusTargetFOV;
	protected float m_focusSpeed;
	protected DayZPlayer m_player;
	
	protected vector m_inspectAngles;
	protected float m_inspectVel[1];
	
	void DayZPlayerCameraIronsights(DayZPlayer pPlayer, HumanInputController pInput){
		m_player = pPlayer;	
	}
	
	override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult){		
		float min;
		if (m_player && m_player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_RAISEDPRONE))
			min = CONST_UD_MIN_BACK;
		else
			min = CONST_UD_MIN;
		
		//m_CurrentCameraPitch = UpdateUDAngle(m_fUpDownAngle, m_fUpDownAngleAdd, min, CONST_UD_MAX, pDt);
		//m_fLeftRightAngle = UpdateLRAngle(m_fLeftRightAngle, CONST_LR_MIN, CONST_LR_MAX, pDt);
		////////////////////////////////////////////////

		float aimChangeX = m_pInput.GetAimChange()[0] * Math.RAD2DEG;
		float aimChangeY = m_pInput.GetAimChange()[1] * Math.RAD2DEG;
						
		vector aimChangeYPR;
		aimChangeYPR[0] = aimChangeX; // Math.SmoothCD(aimChangeYPR[0], aimChangeX, m_velocityYaw, m_dynamicsSmoothTime, 1000, pDt);
		aimChangeYPR[1] = aimChangeY; //Math.SmoothCD(aimChangeYPR[1], aimChangeY, m_velocityPitch, m_dynamicsSmoothTime, 1000, pDt);
		aimChangeYPR[2] = DayZPlayerImplement.Cast(m_player).m_MovementState.m_fLeaning * HeadLeanParams.leanAngle;
		
		if( m_pInput.CameraIsFreeLook() ){
			m_inspectAngles[0] = m_inspectAngles[0] - aimChangeY;
			//m_inspectAngles[1] = m_inspectAngles[1] + aimChangeY;
			m_inspectAngles[2] = m_inspectAngles[2] + aimChangeX;
		}else{
			m_inspectAngles[0] = Math.SmoothCD(m_inspectAngles[0], 0, m_inspectVel, 0.05, 1000, pDt);
			m_inspectAngles[2] = Math.SmoothCD(m_inspectAngles[2], 0, m_inspectVel, 0.05, 1000, pDt);
		}
		
		vector inspectMat[4];
		Math3D.YawPitchRollMatrix(m_inspectAngles, inspectMat);
		inspectMat[3] = vector.Zero;
		
		vector yprMat[4];
		Math3D.YawPitchRollMatrix(aimChangeYPR, yprMat);
		yprMat[3] = vector.Zero;

		vector aimingTM[4];
		m_pPlayer.GetItemAccessor().WeaponGetAimingModelDirTm(aimingTM);
		
		vector boneTM[4];
		if(GetCurrentSightEntity()){
			m_pPlayer.GetItemAccessor().WeaponGetCameraPointBoneRelative(GetCurrentSightEntity(), m_OpticsCamPos, m_OpticsCamDir, m_iBoneIndex, boneTM);
		}
		
		vector scaleMat[3];
		Math3D.ScaleMatrix(10, scaleMat);
		
		//Math3D.MatrixMultiply4(yprMat, boneTM, boneTM);
		Math3D.MatrixInvMultiply4(inspectMat, boneTM, pOutResult.m_CameraTM);
		
		AdjustCameraParameters(pDt, pOutResult);
		updateFOVFocus(pDt, pOutResult);
	}
	
	override void AdjustCameraParameters(float pDt, inout DayZPlayerCameraResult pOutResult){	
		m_iBoneIndex = m_pPlayer.GetBoneIndexByName("RightHand_Dummy");
		if(m_iBoneIndex == -1 ) m_iBoneIndex = m_pPlayer.GetBoneIndexByName("Head");
		pOutResult.m_iDirectBone 			= m_iBoneIndex;
		pOutResult.m_iDirectBoneMode 		= 3;
	
		pOutResult.m_fFovAbsolute = m_fFovAbsolute;
		
		pOutResult.m_bUpdateWhenBlendOut	= false;
		pOutResult.m_fDistance 				= 0;
		pOutResult.m_fUseHeading 			= 0.0;
		pOutResult.m_fInsideCamera 			= 1.0;
		pOutResult.m_fShootFromCamera		= 0.0;
		pOutResult.m_fIgnoreParentRoll      = 0.0;
		pOutResult.m_fNearPlane = 0.01; //0.07 default
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
	
}