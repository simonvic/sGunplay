modded class PPERequester_CameraADS {
	
	/**
	*	normalized 0 - 1
	*/
	protected float m_dofIntensity = 1.0;
	
	void setDofIntensity(float intensity) {
		m_dofIntensity = intensity;
	}
	
	void setMask(float posX, float posY, float radius, float blur) {
		GetGame().ResetPPMask();
		// if mask is not configured, gaussian filter would blur optic too
		if (radius <= 0) {
			SetTargetValueFloatDefault(PostProcessEffectType.GaussFilter, PPEGaussFilter.PARAM_INTENSITY);
		}
		GetGame().AddPPMask(posX, posY, radius, blur);
	}
	
	void setLens(float magnification, float chromAber, float offsetX, float offsetY) {
		SetTargetValueFloat(PostProcessEffectType.Glow, PPEGlow.PARAM_LENSDISTORT,        false, magnification, PPEGlow.L_27_ADS, PPOperators.SET);
		SetTargetValueFloat(PostProcessEffectType.Glow, PPEGlow.PARAM_MAXCHROMABBERATION, false, chromAber,     PPEGlow.L_28_ADS, PPOperators.SET);
		SetTargetValueFloat(PostProcessEffectType.Glow, PPEGlow.PARAM_LENSCENTERX,        false, offsetX,       PPEGlow.L_29_ADS, PPOperators.SET);
		SetTargetValueFloat(PostProcessEffectType.Glow, PPEGlow.PARAM_LENSCENTERY,        false, offsetY,       PPEGlow.L_30_ADS, PPOperators.SET);
	}
	
	//! @deprecated
	void resetMask() {}
	
	//! @deprecated
	void resetLens() {}

	void setDOF(bool enabled, float focusDistance, float focusLength, float focusLengthNear, float focusBlur, float focusDepthOffset) {
		SetTargetValueBool(PPEExceptions.DOF,  PPEDOF.PARAM_ENABLE,                    enabled,          PPEDOF.L_0_ADS, PPOperators.SET);
		SetTargetValueFloat(PPEExceptions.DOF, PPEDOF.PARAM_FOCUS_DIST,         false, focusDistance,    PPEDOF.L_1_ADS, PPOperators.SET);
		SetTargetValueFloat(PPEExceptions.DOF, PPEDOF.PARAM_FOCUS_LEN,          false, focusLength,      PPEDOF.L_2_ADS, PPOperators.SET);
		SetTargetValueFloat(PPEExceptions.DOF, PPEDOF.PARAM_FOCUS_LEN_NEAR,     false, focusLengthNear,  PPEDOF.L_3_ADS, PPOperators.SET);
		SetTargetValueFloat(PPEExceptions.DOF, PPEDOF.PARAM_BLUR,               false, focusBlur,        PPEDOF.L_4_ADS, PPOperators.SET);
		SetTargetValueFloat(PPEExceptions.DOF, PPEDOF.PARAM_FOCUS_DEPTH_OFFSET, false, focusDepthOffset, PPEDOF.L_5_ADS, PPOperators.SET);
	}
	
	void resetDOF() {
		SetTargetValueBoolDefault(PPEExceptions.DOF,PPEDOF.PARAM_ENABLE);
	}
	
	override void SetValuesOptics(out array<float> mask_array, out array<float> lens_array, float gauss = 0.0) {
		super.SetValuesOptics(mask_array, lens_array, gauss * m_dofIntensity);
		GetGame().ResetPPMask();
		SetTargetValueFloatDefault(PostProcessEffectType.Glow, PPEGlow.PARAM_LENSDISTORT);
		SetTargetValueFloatDefault(PostProcessEffectType.Glow, PPEGlow.PARAM_MAXCHROMABBERATION);
		SetTargetValueFloatDefault(PostProcessEffectType.Glow, PPEGlow.PARAM_LENSCENTERX);
		SetTargetValueFloatDefault(PostProcessEffectType.Glow, PPEGlow.PARAM_LENSCENTERY);
	}
	
	override void SetValuesIronsights(out array<float> DOF_array) {
		super.SetValuesIronsights(DOF_array);
		if (m_dofIntensity == 0) {
			SetTargetValueBoolDefault(PPEExceptions.DOF, PPEDOF.PARAM_ENABLE);
		}
		// blur intensity doesn't scale well at low focal lengths
		// so I'm also decreasing the near focal length
		SetTargetValueFloat(PPEExceptions.DOF, PPEDOF.PARAM_FOCUS_LEN_NEAR, false, DOF_array[3] * m_dofIntensity, PPEDOF.L_3_ADS, PPOperators.SET);
		SetTargetValueFloat(PPEExceptions.DOF, PPEDOF.PARAM_BLUR,           false, DOF_array[4] * m_dofIntensity, PPEDOF.L_4_ADS, PPOperators.SET);
	}
}