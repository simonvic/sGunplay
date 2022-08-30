class AimingModelFilterWeaponInteraction : AimingModelFilterBase {
	
	protected Weapon_Base m_prevWeapon;
	protected ItemOptics m_prevOptic;
	protected int m_prevFireMode;
	protected int m_prevStepZeroing;
	protected int m_prevStepZoom;
	
	protected float m_animationTime;
	protected bool m_playHandAnimation;
	
	override bool isActive() {
		return GunplayConstants.AIMING_MODEL_USE_FILTER_WEAPON_INTERACTION;
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {

		if (getWeapon() != m_prevWeapon) {
			m_prevWeapon = getWeapon();
			updateStateOptic();
			return;
		}
		
		updateStateOptic();
		
		if (updateStateZoom()) {
			playSounds(GunplayConstants.SOUND_CHANGE_ZOOM);
		}
		
		if (updateStateZeroing()) {
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
	*	@brief Update the current optic
	*	@return true if it has changed, false otherwise
	*/
	protected bool updateStateOptic() {
		ItemOptics currOptic = getWeapon().GetAttachedOptics();
		if (currOptic != m_prevOptic) {
			m_prevOptic = currOptic;
			updateStateZoom();
			updateStateZeroing();
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
		int currStepZeroing = m_prevWeapon.GetStepZeroing();
		if (currStepZeroing != m_prevStepZeroing) {
			m_prevStepZeroing = currStepZeroing;
			return true;
		}
		return false;
	}
	
	/**
	*	@brief Update the current firemode state
	*	@return true if it has changed, false otherwise
	*/
	protected bool updateStateFiremode() {
		//@fixme shooting in double shot firemode triggers a firemodechange
		int currFireMode = m_prevWeapon.GetCurrentMode(m_prevWeapon.GetCurrentMuzzle());
		if (currFireMode != m_prevFireMode) {
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

	
	
}
