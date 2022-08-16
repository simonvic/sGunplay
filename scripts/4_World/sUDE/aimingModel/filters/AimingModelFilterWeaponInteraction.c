class AimingModelFilterWeaponInteraction : AimingModelFilterBase {
	
	protected Weapon_Base m_prevWeapon;
	protected int m_prevFireMode;
	protected int m_prevStepZeroing;
	protected int m_prevStepZoom;
	
	protected bool m_fireModeChanged;
	protected bool m_zeroingChanged;
	protected bool m_zoomChanged;
	protected bool m_weaponChanged;
	
	protected float m_velX[1];
	protected float m_velY[1];
	
	protected float m_time;
	protected bool reverse;
	protected bool done = true;
	
	override bool isActive() {
		return GunplayConstants.AIMING_MODEL_USE_FILTER_WEAPON_INTERACTION;
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		m_fireModeChanged = false;
		m_zeroingChanged = false;
		m_zoomChanged = false;
		m_weaponChanged = false;
		float offset[] = {0, 0};
		
		updateState();
		
		if (!m_weaponChanged && (m_fireModeChanged || m_zeroingChanged || m_zoomChanged)) {
			offset = GunplayConstants.AIMING_MODEL_USE_FILTER_WEAPON_INTERACTION_OFFSETS;
			offset = {-40, 100};
			done = false;
			if (GetGame().IsClient() || !GetGame().IsMultiplayer()) {
				playSounds(getSoundSet());
			}
		}
		
		
		if (m_time >= 1) reverse = true;
		if (m_time < 0) {
			reverse = false;
			done = true;
		}
		if (done) {
			m_time = 0;
			return;
		}
		if (reverse) {
			m_time -= pDt * 3;
		} else {
			m_time += pDt * 5;
		}
		
		
		pModel.m_fAimXHandsOffset += Easing.EaseInSine(m_time) * 2;
		pModel.m_fAimYHandsOffset -= Easing.EaseOutSine(m_time) * 2;
		pModel.m_fAimXCamOffset -= Easing.EaseInOutSine(m_time) * 3;
		pModel.m_fCamPosOffsetZ += Easing.EaseInOutSine(m_time) * 0.025;


	}
	
	/**
	*	@brief Check if a state has changed. Can't use HumanInputController
	*/
	protected void updateState() {
		Weapon_Base weapon = getWeapon();
		
		if (weapon != m_prevWeapon) {
			m_weaponChanged = true;
			m_prevWeapon = weapon;
		}
		
		//@fixme shooting in double shot firemode triggers a firemodechange
		int fireMode = weapon.GetCurrentMode(weapon.GetCurrentMuzzle());
		if (fireMode != m_prevFireMode) {
			m_prevFireMode = fireMode;
			m_fireModeChanged = true;
		}
		
		int stepZeroing = weapon.GetStepZeroing();
		if (stepZeroing != m_prevStepZeroing) {
			m_prevStepZeroing = stepZeroing;
			m_zeroingChanged = true;
		}
		
		ItemOptics optic = weapon.GetAttachedOptics();
		if (optic) {
			int stepZoom = optic.GetStepFOVIndex();
			if (stepZoom != m_prevStepZoom) {
				m_prevStepZoom = stepZoom;
				m_zoomChanged = true;
			}
		}
	}
	
	/**
	*	@brief Play sounds only on client
	*	 @param soundSet \p string - classname of soundset (from DZ/sounds/hpp/config.cpp) to be played
	*/
	protected void playSounds(string soundSet) {
		if (soundSet != string.Empty) {
			SEffectManager.PlaySoundOnObject( soundSet , getWeapon()).SetSoundAutodestroy( true );
		}
	}
	
	/**
	*	@brief Get soundset to play based on performed interaction
	*	 @return string - soundset classname
	*/
	protected string getSoundSet() {
		if (m_zeroingChanged) {
			return GunplayConstants.SOUND_CHANGE_ZEROING;
		} else if (m_zoomChanged) {
			return GunplayConstants.SOUND_CHANGE_ZOOM;
		}
		return string.Empty;
	}
	
	
}
