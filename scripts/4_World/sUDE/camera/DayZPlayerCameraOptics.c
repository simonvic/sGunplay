modded class DayZPlayerCameraOptics {
	
	protected ref TFloatArray m_opticPPMask = new TFloatArray;
	protected ref TFloatArray m_opticPPLens = new TFloatArray;
	protected float m_opticPPBlur;
	
	protected bool m_canShowLens = false;
	protected vector m_lensOffset;
	protected float m_lensOffsetVelX[1];
	protected float m_lensOffsetVelY[1];
	
	override void OnActivate (DayZPlayerCamera pPrevCamera, DayZPlayerCameraResult pPrevCameraResult) {
		super.OnActivate(pPrevCamera,pPrevCameraResult);
		
		m_opticsUsed.InitOpticsPP(m_opticPPMask, m_opticPPLens, m_opticPPBlur);
		
		//Show lens when transition is done
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.setShowLens, m_enteringTransitionTime * 1000 + GunplayConstants.ADS_LENS_ACTIVATION_DELAY, false, true);
		
		//Hide player clothing when transition is done
		if (m_player) {
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(m_player.HideClothing);
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_player.HideClothing, m_enteringTransitionTime * 1000 + GunplayConstants.ADS_HIDE_CLOTHING_DELAY,false,m_opticsUsed,isHideClothingInOpticEnabled());
		}
		
		if (isSniperOptic()) {
			SCameraOverlaysManager.getInstance().activate(m_opticMisalignmentOverlay);
		}
	}
	
	override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult) {
		super.OnUpdate(pDt, pOutResult);
		updateLens(pDt);
	}
	
	/**
	*	@brief Update the lens effect position and strength along with the PP mask
	*/
	protected void updateLens(float pDt) {
		
		if (!m_player.IsInOptics() || !isMagnifyingOptic() || !canShowLens() || isHandHeldOptic()) {
			return;
		}

		m_lensOffset = GetGame().GetScreenPosRelative(m_aimingModel.getLensPositionWS());
		
		
		/*
		auto dui = SDebugUI.of("optic");
		dui.begin();
		dui.window("PiP");
		dui.table({
			{"",     "pos X",               "pos Y",             "radius",            "blur"}
			{"mask", ""+m_opticPPMask[0], ""+m_opticPPMask[1], ""+m_opticPPMask[2], ""+m_opticPPMask[3]}
			{"",     "magnification",       "pos X",             "pos Y",             "chrom aber"}
			{"lens", ""+m_opticPPLens[0], ""+m_opticPPLens[1], ""+m_opticPPLens[2], ""+m_opticPPLens[3]}
		}, {512, 128});
		dui.end();
		*/
		
		// @todo yikes... are there no alternatives?
		int sX, sY;
		GetScreenSize(sX, sY);
		
		m_lensOffset[0] = m_lensOffset[0] + SMath.mapTo(m_aimingModel.getMisalignment()[0], 0, 5, 0, 0.15);
		m_lensOffset[1] = m_lensOffset[1] - SMath.mapTo(m_aimingModel.getMisalignment()[1], 0, 5, 0, 0.15) * (sX / sY);
		
		SPPEManager.requestOpticMask(computeMask(m_opticPPMask, m_lensOffset[0], m_lensOffset[1]));
		SPPEManager.requestOpticLens(computeLens(m_opticPPLens, m_lensOffset[0], m_lensOffset[1]));
		
	}
	
	/**
	*	@brief Compute the mask position, radius, and blur(smooth opacity)
	*	 Mask = {positionX [-1, 1], positionY [-1, 1], radius, blur}
	*	 @param mask \p TFloatArray - Starting mask array
	*	 @param offsetX \p float - arbitrary X offset
	*	 @param offsetY \p float - arbitrary Y offset
	*	 @return TFloatArray - computed mask array
	*/
	protected TFloatArray computeMask(TFloatArray mask, float offsetX, float offsetY) {
		return {
			mask[0] + offsetX,                         //X position
			mask[1] + offsetY,                         //Y position
			mask[2] / 9.8696 / Camera.GetCurrentFOV(), //radius ( current radius / pi^2 / fov )
			mask[3]                                    //blur
		};
	}
	
	/**
	*	@brief Compute the lens intensity, position, and chromatic aberration
	*	 Lens = {intensity [-i, +i], positionX [-1, 1], positionY [-1, 1], chromatic aberration}
	*	 @param lens \p TFloatArray - Starting lens array
	*	 @param offsetX \p float - arbitrary X offset
	*	 @param offsetY \p float - arbitrary Y offset
	*	 @return TFloatArray - computed lens array
	*/
	protected TFloatArray computeLens(TFloatArray lens, float offsetX, float offsetY) {
		return {
			lens[0] * getLensZoomStrength(),  //intensity
			lens[1] + (offsetX * 2 - 1),      //X position
			lens[2] + (offsetY * 2 - 1),      //Y position
			lens[3]                           //chrom aber	
		};
	}
	
	/**
	*	@brief Get the offset based on the zeroing index of the scope
	*	 @param zeroing \p int - zeroing index
	*	 @param decay \p float - 
	*	 @param amplitude \p float - 
	*/
	static float getLensZeroingOffset(ItemOptics optic, float decay, float amplitude) {
		return Math.Pow(optic.GetStepZeroing(), decay) * amplitude;
	}
	
	
	override void AdjustCameraParameters(float pDt, inout DayZPlayerCameraResult pOutResult) {
		pOutResult.m_iDirectBone 			= m_iBoneIndex;
		pOutResult.m_iDirectBoneMode 		= 3;
		
		//m_fFovAbsolute = GetDayZGame().GetUserFOV();
		pOutResult.m_fFovAbsolute = m_fFovAbsolute;
		//pOutResult.m_fFovMultiplier = 1.0;
		
		pOutResult.m_bUpdateWhenBlendOut	= false;
		pOutResult.m_fDistance 				= 0;
		pOutResult.m_fUseHeading 			= 0.0;
		pOutResult.m_fInsideCamera 			= 1.0;
		pOutResult.m_fShootFromCamera		= 0.0;
		pOutResult.m_fIgnoreParentRoll      = 0.0;
		pOutResult.m_fNearPlane = 0.03; //0.07 default
		
		/*
		//@todo use this (from 1.13) to allow per-optic near plane
		pOutResult.m_fNearPlane = Math.Clamp(m_opticsUsed.GetNearPlaneValue() - m_RecoilOffsetZ - 0.2, 0.03, 10.0);
		*/
	}
			
	override float getRestingFOV() {
		return m_opticsUsed.GetCurrentStepFOV() * GunplayConstants.ADS_FOV_REDUCTION_OPTICS;
	}

	override void computeFOVFocusValues(out float targetFOV, out float speed) {
		speed = 0.2;
		targetFOV = GetDayZGame().GetUserFOV() * userCfgGunplay.getAdsFOVMultiplier();
		
		// No optic
		if (!m_opticsUsed) {
			m_fFovAbsolute = targetFOV; //immediately
			return;
		}
		
		// Handheld optics
		if (isHandHeldOptic()) {
			targetFOV = m_opticsUsed.GetCurrentStepFOV();
			if (isSniperOptic()) {
				speed = 0.0001;
			}
			
			return;
		}
		

		// Non magnifying optic
		if (!isMagnifyingOptic()) {
			if (canZoom()) {
				targetFOV = m_opticsUsed.GetCurrentStepFOV();
				speed = getFocusSpeedStance() * GunplayConstants.FOCUS_SPEED_NON_MAGN_MULTIPLIER;
			}
			return;
		}
		
		// Sniping optic
		if (isSniperOptic()) {
			targetFOV = m_opticsUsed.GetCurrentStepFOV();
			speed = 0.0001;
			return;
		}
			
		// Magnifying optic
		targetFOV = getRestingFOV();
			
		if (m_isEntering) {
			m_fFovAbsolute = targetFOV; // immediately set the fov
			m_isEntering = false;
		} else if (canZoom()) {
			targetFOV = m_opticsUsed.GetCurrentStepFOV();
			speed = getFocusSpeedStance();
		}

	}
	
	
	override void SetCameraPP(bool state, DayZPlayerCamera launchedFrom) {	
		if (needPPEReset(state, launchedFrom)) {
			resetPPE();
			return;
		}
			
		if (!isMagnifyingOptic() && !NVGoggles.Cast(m_opticsUsed)) { // 1x scopes only
			setNonMagnifyingOpticDOF();
			updateNightVision(true);
		} else {//magnifying scopes
			
			//lens is updated everyframe
			//blur is disabled
			updateNightVision(false);
		}
		
		hideWeaponBarrel(isHideWeaponBarrelInOpticEnabled());
		
	}
	
	override bool needPPEReset(bool state, DayZPlayerCamera launchedFrom) {
		return !state || !m_opticsUsed || m_player && launchedFrom != m_player.GetCurrentPlayerCamera());
	}
	
	
	protected bool canShowLens() {
		return m_canShowLens;
	}
	
	protected void setShowLens(bool showable) {
		m_canShowLens = showable;
	}
	
	override bool canApplyDeadzone() {
		return super.canApplyDeadzone() && !isSniperOptic();
	}
	
	override bool canApplyHandsOffset() {
		return super.canApplyHandsOffset() && !isSniperOptic();
	}
	
	override bool canZoom() {
		return playerIsFocusing() && !m_player.isInspectingWeapon();
	}
	
	override bool canFreelook() {
		return super.canFreelook() && !isMagnifyingOptic();
	}
	
	override bool canInspectWeapon() {
		return super.canInspectWeapon() && !isMagnifyingOptic();
	}
	
	override bool isMagnifyingOptic() {
		return !m_opticsUsed.AllowsDOF();
	}
	
	override bool isSniperOptic() {
		return m_opticsUsed.GetStepFOVCount() > 0;
	}
		
}