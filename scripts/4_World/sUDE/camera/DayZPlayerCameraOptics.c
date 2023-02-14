modded class DayZPlayerCameraOptics {
	
	protected ref array<float> m_pipOffset = {0.0, 0.0};
	protected ref array<float> m_pipLensOffset = {0.0, 0.0};
	protected float m_pipRadius;
	protected float m_pipMagnification;
	protected float m_pipBlur;
	protected float m_pipChromAber;
	
	protected bool m_canShowLens = false;
	protected vector m_opticPositionSS;
	
	protected bool m_showEnterMisalignment;
	protected bool m_isFullscreen;
	
	protected bool m_opticOverridesNearPlane;
	protected float m_opticNearPlaneOverride;
	
	protected float m_lensZoomStrength = 1;
	protected float m_adsFovMagnOpticsMultiplier = 1;
	
	void DayZPlayerCameraOptics(DayZPlayer pPlayer, HumanInputController pInput) {
		m_opticOverridesNearPlane = m_opticsUsed.ConfigIsExisting("s_nearPlaneOverride");
		if (m_opticOverridesNearPlane) {
			m_opticNearPlaneOverride = m_opticsUsed.ConfigGetFloat("s_nearPlaneOverride");
		}
		m_showEnterMisalignment = m_opticsUsed.ConfigGetBool("s_showEnterMisalignment");
		m_isFullscreen = m_opticsUsed.ConfigGetBool("s_isFullscreen");
		m_lensZoomStrength = SMath.mapClamp(
			userCfgGunplay.getLensZoomStrength(),
			0, 1,
			GunplayConstants.ADS_LENS_STRENGTH_CONSTRAINTS[0], GunplayConstants.ADS_LENS_STRENGTH_CONSTRAINTS[1]);
		
		initPiP(m_opticsUsed);
	}
	
	override void initADSFOVMultipliers() {
		super.initADSFOVMultipliers();
		m_adsFovMagnOpticsMultiplier = SMath.mapClamp(
			userCfgGunplay.getAdsFOVMagnOpticsMultiplier(),
			0, 1,
			GunplayConstants.ADS_FOV_MULT_OPTICS_CONSTRAINTS[0], GunplayConstants.ADS_FOV_MULT_OPTICS_CONSTRAINTS[1]);
	}
	
	override void initRestingFOV() {
		super.initRestingFOV();
		if (m_opticsUsed && isMagnifyingOptic()) {
			if (isHandHeldOptic()) {
				m_restingFOV = m_opticsUsed.GetCurrentStepFOV();
			} else {
				m_restingFOV = m_opticsUsed.GetCurrentStepFOV() * getADSFOVMagnOpticsMultiplier();
			}
		}
		
	}
	
	override void initFocusingFOV() {
		super.initFocusingFOV();
		if (m_opticsUsed) {
			if (isMagnifyingOptic()) {
				m_focusingFOV = Math.Lerp(getRestingFOV(), m_opticsUsed.GetCurrentStepFOV(), GunplayConstants.FOCUS_INTENSITY_MAGN);
			} else {
				m_focusingFOV = Math.Lerp(getRestingFOV(), m_opticsUsed.GetCurrentStepFOV(), GunplayConstants.FOCUS_INTENSITY_NON_MAGN);
			}
		}
	}
	
	override void OnActivate(DayZPlayerCamera pPrevCamera, DayZPlayerCameraResult pPrevCameraResult) {
		super.OnActivate(pPrevCamera,pPrevCameraResult);
		
		//Show lens when transition is done
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.setShowLens, m_enteringTransitionTime * 1000 + GunplayConstants.ADS_LENS_ACTIVATION_DELAY, false, true);
		
		//Hide player clothing when transition is done
		if (m_player) {
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(m_player.HideClothing);
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(m_player.HideClothing, m_enteringTransitionTime * 1000 + GunplayConstants.ADS_HIDE_CLOTHING_DELAY,false,m_opticsUsed,isHideClothingInOpticEnabled());
		}
		
		if (showEnterMisalignment()) {
			SCameraOverlaysManager.getInstance().activate(m_opticMisalignmentOverlay);
		}
	}
	
	override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult) {
		super.OnUpdate(pDt, pOutResult);
		updateLens(pDt);
	}
	
	protected void initPiP(ItemOptics optic) {
		if (optic.ConfigIsExisting("s_pipOffset")) {
			optic.ConfigGetFloatArray("s_pipOffset", m_pipOffset);
		} else {
			m_pipOffset = {0, 0};
		}
		if (optic.ConfigIsExisting("s_pipLensOffset")) {
			optic.ConfigGetFloatArray("s_pipLensOffset", m_pipLensOffset);
		} else {
			m_pipLensOffset = {0, 0};
		}
		m_pipRadius = optic.ConfigGetFloat("s_pipRadius");
		m_pipMagnification = optic.ConfigGetFloat("s_pipMagnification");
		m_pipBlur = optic.ConfigGetFloat("s_pipBlur");
		m_pipChromAber = optic.ConfigGetFloat("s_pipChromAber");
	}
	
	/**
	*	@brief Update the lens effect position and strength along with the PP mask
	*/
	protected void updateLens(float pDt) {
		
		if (!m_player.IsInOptics() || !isMagnifyingOptic() || !canShowLens() || isHandHeldOptic()) {
			return;
		}

		m_opticPositionSS = GetGame().GetScreenPosRelative(m_aimingModel.getLensPositionWS());
		
		// @todo yikes... are there no alternatives?
		int sX, sY;
		GetScreenSize(sX, sY);
		
		m_opticPositionSS[0] = m_opticPositionSS[0] + SMath.mapTo(m_aimingModel.getMisalignment()[0], 0, 5, 0, 0.15);
		m_opticPositionSS[1] = m_opticPositionSS[1] - SMath.mapTo(m_aimingModel.getMisalignment()[1], 0, 5, 0, 0.15) * (sX / sY);
		
		applyPiP();
	}
	
	/**
	*	@brief Apply the PiP (mask and lens)
	*/
	protected void applyPiP() {
		SPPEManager.requestOpticMask(
			m_opticPositionSS[0] + m_pipOffset[0],
			m_opticPositionSS[1] + m_pipOffset[1],
			m_pipRadius / SMath.PI_SQ / Camera.GetCurrentFOV(),
			m_pipBlur);
		
		SPPEManager.requestOpticLens(
			m_pipMagnification * getLensZoomStrength(),
			(m_opticPositionSS[0] * 2 - 1) + m_pipOffset[0] + m_pipLensOffset[0],
			(m_opticPositionSS[1] * 2 - 1) + m_pipOffset[1] + m_pipLensOffset[1],
			m_pipChromAber);
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
		if (m_opticOverridesNearPlane) {
			pOutResult.m_fNearPlane = m_opticNearPlaneOverride;
		} else {
			pOutResult.m_fNearPlane = 0.03;
		}
		
		/*
		//@todo use this (from 1.13) to allow per-optic near plane
		pOutResult.m_fNearPlane = Math.Clamp(m_opticsUsed.GetNearPlaneValue() - m_RecoilOffsetZ - 0.2, 0.03, 10.0);
		*/
	}

	override void computeFOVFocusValues(out float targetFOV, out float speed) {
		speed = 0.2;
		targetFOV = getRestingFOV();
		
		if (m_isEntering) {
			m_fFovAbsolute = targetFOV;
			m_isEntering = false;
			return;
		}
		
		// No optic
		if (!m_opticsUsed) {
			m_fFovAbsolute = targetFOV; //immediately
			return;
		}
		
		// Handheld optics
		if (isHandHeldOptic()) {
			targetFOV = m_opticsUsed.GetCurrentStepFOV();
			if (isFullscreenOptic()) {
				speed = 0.0001;
			}
			return;
		}
		

		// Non magnifying optic
		if (!isMagnifyingOptic()) {
			if (canZoom()) {
				targetFOV = getFocusingFOV();
				speed = getFocusSpeedStance() * GunplayConstants.FOCUS_SPEED_NON_MAGN_MULTIPLIER;
			}
			return;
		}
		
		// Sniping optic
		if (isFullscreenOptic()) {
			targetFOV = m_opticsUsed.GetCurrentStepFOV();
			speed = 0.0001;
			return;
		}
		
		// magnifying optic
		if (canZoom()) {
			targetFOV = getFocusingFOV();
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
	
	protected float getLensZoomStrength() {
		return m_lensZoomStrength;
	}
		
	protected float getADSFOVMagnOpticsMultiplier() {
		return m_adsFovMagnOpticsMultiplier;
	}
	
	protected bool canShowLens() {
		return m_canShowLens;
	}
	
	protected void setShowLens(bool showable) {
		m_canShowLens = showable;
	}
	
	override bool canApplyDeadzone() {
		return super.canApplyDeadzone() && !isFullscreenOptic();
	}
	
	override bool canApplyHandsOffset() {
		return super.canApplyHandsOffset() && !isFullscreenOptic();
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
	
	override bool isFullscreenOptic() {
		return m_isFullscreen;
		//return m_opticsUsed.GetStepFOVCount() > 0;
	}
	
	bool showEnterMisalignment() {
		return m_showEnterMisalignment;
	}
		
}