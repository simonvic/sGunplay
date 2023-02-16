enum eADSType {
	UNKNOWN = -1,
	NONE = 0,
	WEAPON = 1,
	OPTIC = 2,
	BUIS = 4
}

class AimingModelFilterWeaponInteraction : AimingModelFilterBase {
	
	override bool isActive() {
		return GunplayConstants.AIMING_MODEL_USE_FILTER_WEAPON_INTERACTION;
	}
	
	// Can't be notified when these properties change,
	// so we have to cache and compare them :shrug:
	
	protected Weapon_Base m_prevWeapon;
	protected eADSType m_prevADSType = eADSType.UNKNOWN;
	protected ItemOptics m_prevOptic;
	protected int m_prevStepZoom;
	//@todo Can't use step zoom, when using backup weapon ironsight, the weapon doesn't report the right Step. Report this.
	protected int m_prevZeroing;
	protected int m_prevFireMode;
	
	protected float m_animationTime;
	protected bool m_playHandAnimation;
		
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {		
		updateStateWeapon();
		updateStateAdsType();
		updateStateOptic();
		
		HumanInputController pInput = getPlayer().GetInputController();
		
		if (updateStateZoom() && pInput && (pInput.IsZoomIn() || pInput.IsZoomOut())) {
			playSounds(GunplayConstants.SOUND_CHANGE_ZOOM);
		}
		
		if (updateStateZeroing() && pInput && (pInput.IsZeroingUp() || pInput.IsZeroingDown())) {
			playSounds(GunplayConstants.SOUND_CHANGE_ZEROING);
		}
		
		if (updateStateFiremode()) {
			m_playHandAnimation = true;
		}
		
		if (m_playHandAnimation) {
			playHandAnimation(pDt, pModel);
		}
	}
	
	/**
	*	@brief Update the current weapon
	*	@return true if it has changed, false otherwise
	*/
	protected bool updateStateWeapon() {
		Weapon_Base currentWeapon = getWeapon();
		if (m_prevWeapon != currentWeapon) {
			m_prevWeapon = currentWeapon;
			return true;
		}
		return false;
	}
	
	/**
	*	@brief Update the current ADS type
	*	@return true if it has changed, false otherwise
	*/
	protected bool updateStateAdsType() {
		eADSType currentADSType = getADSType();
		if (m_prevADSType != currentADSType) {
			m_prevADSType = currentADSType;
			return true;
		}
		return false;
	}
	
	/**
	*	@brief Update the current optic
	*	@return true if it has changed, false otherwise
	*/
	protected bool updateStateOptic() {
		ItemOptics currOptic = getWeapon().GetAttachedOptics();
		if (currOptic != m_prevOptic) {
			m_prevOptic = currOptic;
			return true;
		}
		return false;
	}
	
	/**
	*	@brief Update the current zoom state
	*	@return true if it has changed, false otherwise
	*/
	protected bool updateStateZoom() {
		if (!m_prevOptic) return false;
		int currStepZoom = m_prevOptic.GetStepFOVIndex();
		if (currStepZoom != m_prevStepZoom) {
			m_prevStepZoom = currStepZoom;
			return true;
		}
		return false;
	}
	
	/**
	*	@brief Update the current zeroing state
	*	@return true if it has changed, false otherwise
	*/
	protected bool updateStateZeroing() {
		int currStepZeroing = m_prevWeapon.GetCurrentZeroing();
		if (m_prevZeroing != currStepZeroing) {
			m_prevZeroing = currStepZeroing;
			return true;
		}
		return false;
	}
	
	/**
	*	@brief Update the current firemode state
	*	@return true if it has changed, false otherwise
	*/
	protected bool updateStateFiremode() {
		int currFireMode = m_prevWeapon.GetCurrentMode(m_prevWeapon.GetCurrentMuzzle());
		if (m_prevFireMode != currFireMode) {
			m_prevFireMode = currFireMode;
			return true;
		}
		return false;
	}
	
	/**
	*	@brief Animate hands and camera
	*/
	protected void playHandAnimation(float pDt, SDayZPlayerAimingModel pModel) {
		if (m_animationTime > 1) {
			m_playHandAnimation = false;
			m_animationTime = 0;
		} else {
			m_animationTime += pDt * 2;
			float loopedTime = 1 - Math.AbsFloat(m_animationTime - 0.5) * 2;
			
			pModel.m_fAimXHandsOffset += Easing.EaseInOutSine(loopedTime) * 0.3;
			pModel.m_fAimYHandsOffset -= Easing.EaseInSine(loopedTime) * 0.5;
			
			if (GetGame().IsClient()) {
				pModel.m_fAimXCamOffset -= Easing.EaseInOutBack(loopedTime, 0.69) * 0.2;
				pModel.m_fAimYCamOffset -= Easing.EaseInSine(loopedTime) * 0.1;
				pModel.m_fCamPosOffsetZ += Easing.EaseInOutSine(loopedTime) * 0.005;
			}
		}
	}
	

	/**
	*	@brief Play sounds only on client
	*	@param soundSet \p string - classname of soundset (from DZ/sounds/hpp/config.cpp) to be played
	*/
	protected void playSounds(string soundSet) {
		if (!GetGame().IsClient()) return;
		if (soundSet != string.Empty) {
			SEffectManager.PlaySoundOnObject(soundSet, getWeapon()).SetSoundAutodestroy(true);
		}
	}
	
	/**
	*	@brief Get ADS type
	*	@return UNKNOWN if unkNown, OPTIC if is in optic, BUIS if using backup ironsight, WEAPON if no optic used or weapon backup ironsight
	*/
	protected eADSType getADSType() {
		if (!getPlayer()) return eADSType.UNKNOWN;
		if (getPlayer().IsInOptics()) {
			return eADSType.OPTIC;
		}
		if (m_prevOptic && m_prevOptic.IsUsingWeaponIronsightsOverride()) {
			return eADSType.BUIS;
		}
		return eADSType.WEAPON;
	}

	
	
}
