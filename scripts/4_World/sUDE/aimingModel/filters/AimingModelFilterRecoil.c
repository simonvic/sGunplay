class AimingModelFilterRecoil : AimingModelFilterBase {
	
	protected float m_time;
		
	protected float m_velHandsAccumX[1];
	protected float m_velHandsAccumY[1];
	protected float m_velHandsResetX[1];
	protected float m_velHandsResetY[1];
	
	protected float m_velMisalignAccumX[1];
	protected float m_velMisalignAccumY[1];
	protected float m_velMisalignResetX[1];
	protected float m_velMisalignResetY[1];
	
	protected float m_handsAccum[2];
	protected float m_misalignAccum[2];
	protected float m_mouseAccum[2];
	protected float m_kickAccum;
	
	protected ref RecoilBase m_recoil;
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		m_time += pDt;
		
		RecoilBase r = getAimingModel().getRecoil();
		if (r != null && m_recoil != r) {
			onNewRecoil(r);
		}
		
		if (m_recoil) {
			applyMouseOffset(pDt, pModel, m_recoil);
			applyHandsOffset(pDt, pModel, m_recoil);
			if (GetGame().IsClient()) {
				applyMisalignment(pDt, pModel, m_recoil);
				applyKick(pDt, pModel, m_recoil);
			}
			reset(pDt, m_recoil);
		}
		
	}
	
	/**
	*	@brief Called when a new recoil has been generated
	*/
	protected void onNewRecoil(notnull RecoilBase r) {
		delete m_recoil;
		m_recoil = r;
		getPlayer().getRecoilControl().compute();
		accumulateRecoil(m_recoil);
	}
	
	/**
	*	@brief Called when a new recoil has been produced. Accumulate the recoil parameters
	*	@param recoil to accumulate
	*/
	protected void accumulateRecoil(notnull RecoilBase r) {
		m_time = 0;
		m_handsAccum[0] = m_handsAccum[0] + controlRecoil(r.hands[0]);
		m_handsAccum[1] = m_handsAccum[1] + controlRecoil(r.hands[1]);
		m_mouseAccum[0] = 0;
		m_mouseAccum[1] = 0;
		if (GetGame().IsClient()) {
			m_kickAccum = controlRecoil(r.kick);
			m_misalignAccum[0] = m_misalignAccum[0] + controlRecoil(r.hands[0]);
			m_misalignAccum[1] = m_misalignAccum[1] + controlRecoil(r.hands[1]);
		}
	}
	
	/**
	*	@brief Apply recoil control function
	*	@param recoil value to control
	*	@return value controlled
	*/
	protected float controlRecoil(float value) {
		return -value * GunplayConstants.RECOIL_CONTROL_COEFF * Math.Atan(Math.Pow(getPlayer().getRecoilControl().get(), 3) * GunplayConstants.RECOIL_CONTROL_STEEPNESS) + value;
	}
	
	/**
	*	@brief Apply mouse offset to aiming model
	*	@param delta time
	*	@param aiming model
	*	@param recoil to apply
	*/
	protected void applyMouseOffset(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		// compute delta values of mouse shift so we spread the movement on multiple frames while not making harsh movements
		if (m_mouseAccum[1] < r.mouse[1]) {
			float relativeDelta = pDt / r.mouseTime;
			float deltaMouseX = r.mouse[0] * relativeDelta;
			float deltaMouseY = r.mouse[1] * relativeDelta;
			if ((m_mouseAccum[1] + deltaMouseY) > r.mouse[1]) {
				deltaMouseX = r.mouse[0] - m_mouseAccum[0];
				deltaMouseY = r.mouse[1] - m_mouseAccum[1];
			}
			m_mouseAccum[0] = m_mouseAccum[0] + deltaMouseX;
			m_mouseAccum[1] = m_mouseAccum[1] + deltaMouseY;
		}
		
		PropertyModifiers modifiers = getWeapon().GetPropertyModifierObject();
		pModel.m_fAimXMouseShift -= deltaMouseX * modifiers.recoilControlMouseX;
		pModel.m_fAimYMouseShift += deltaMouseY * modifiers.recoilControlMouseY;
		
	}
	
	/**
	*	@brief Apply kick (camera Z-axis offset) to aiming model
	*	@param delta time
	*	@param aiming model
	*	@param recoil to apply
	*/
	protected void applyKick(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		float timeNormalized = SMath.normalizeClamp(m_time, 0, r.kickResetTime);
		float easing = 1 - Easing.EaseOutElastic(timeNormalized, 0.45);
		pModel.m_fCamPosOffsetZ	+= Math.Lerp(0, m_kickAccum * getWeapon().GetPropertyModifierObject().recoilControlKick, easing);
	}
	
	/**
	*	@brief Apply hands offset to aiming model
	*	@param delta time
	*	@param aiming model
	*	@param recoil to apply
	*/
	protected void applyHandsOffset(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		
		PropertyModifiers modifiers = getWeapon().GetPropertyModifierObject();
		pModel.m_fAimXHandsOffset += Math.SmoothCD(
			0,
			m_handsAccum[0] * modifiers.recoilControlHandsX,
			m_velHandsAccumX,
			1 - r.handsAccumSpeed,
			1000, pDt);
		
		pModel.m_fAimYHandsOffset += Math.SmoothCD(
			0,
			m_handsAccum[1] * modifiers.recoilControlHandsY,
			m_velHandsAccumY,
			1 - r.handsAccumSpeed,
			1000, pDt);
	}
	
	/**
	*	@brief Apply misalignment (camera rotation) to aiming model
	*	@param delta time
	*	@param aiming model
	*	@param recoil to apply
	*/
	protected void applyMisalignment(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		float smoothTime = 1 - r.misalignAccumSpeed;
		PropertyModifiers modifiers = getWeapon().GetPropertyModifierObject();
		pModel.m_fAimXCamOffset -= Math.SmoothCD(
			0,
			m_misalignAccum[0] * r.misalignIntensity[0] * modifiers.recoilControlMisalignmentX,
			m_velMisalignAccumX,
			smoothTime,
			1000, pDt);
		
		pModel.m_fAimYCamOffset -= Math.SmoothCD(
			0,
			m_misalignAccum[1] * r.misalignIntensity[1] * modifiers.recoilControlMisalignmentY,
			m_velMisalignAccumY,
			smoothTime,
			1000, pDt);
	}
	
	/**
	*	@brief Reset the recoil
	*	@param delta time
	*	@param recoil to apply
	*/
	protected void reset(float pDt, notnull RecoilBase r) {
		float handsSmoothTime = 1 - r.handsResetSpeed;
		m_handsAccum[0] = Math.SmoothCD(m_handsAccum[0], 0, m_velHandsResetX, handsSmoothTime, 1000, pDt);
		m_handsAccum[1] = Math.SmoothCD(m_handsAccum[1], 0, m_velHandsResetY, handsSmoothTime, 1000, pDt);
		
		if (GetGame().IsClient()) {
			float misalignSmoothTime = 1 - r.misalignResetSpeed;
			m_misalignAccum[0] = Math.SmoothCD(m_misalignAccum[0], 0, m_velMisalignResetX, misalignSmoothTime, 1000, pDt);
			m_misalignAccum[1] = Math.SmoothCD(m_misalignAccum[1], 0, m_velMisalignResetY, misalignSmoothTime, 1000, pDt);
		}
	}
	
}