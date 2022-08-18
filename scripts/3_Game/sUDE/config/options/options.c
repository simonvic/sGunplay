/**
*	@brief Option for ADS field of view multiplier
*/
class SUCOption_ADSFOVMultiplier : SUserConfigOption<float> {
		
	void SUCOption_ADSFOVMultiplier(float value, SConstraintBase constraint = null, SUserConfigOptionInfo info = null) {
		if (!info) {
			m_info = new SUserConfigOptionInfo("#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_ADS_FOV_MULTIPLIER", "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_ADS_FOV_MULTIPLIER_DESCRIPTION")
		}
	}
	
	override void onValueChange(float previousValue, float newValue) {
		SUserConfig.gunplay().setAdsFOVMultiplier(newValue);
	}
}

/**
*	@brief Option for Depth of Field effect while AimingDownSight
*/
class SUCOption_ADSDOFIntensity : SUserConfigOption<float> {
		
	void SUCOption_ADSDOFIntensity(float value, SConstraintBase constraint = null, SUserConfigOptionInfo info = null) {
		if (!info) {
			m_info = new SUserConfigOptionInfo("#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_ADS_DOF_INTENSITY", "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_ADS_DOF_INTENSITY_DESCRIPTION")
		}
	}
	
	override void onValueChange(float previousValue, float newValue) {
		SUserConfig.gunplay().setAdsDOFIntensity(newValue);
	}
}



/**
*	@brief Option for hiding weapon barrel while aiming down sight in an optic
*/
class SUCOption_HideWeaponBarrelInOptic : SUserConfigOption<bool> {
	
	void SUCOption_HideWeaponBarrelInOptic(bool value, SConstraintBase constraint = null, SUserConfigOptionInfo info = null) {
		if (!info) {
			m_info = new SUserConfigOptionInfo("#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_HIDE_BARREL", "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_HIDE_BARREL_DESCRIPTION")
		}
	}
	
	override void onValueChange(bool previousValue, bool newValue) {
		SUserConfig.gunplay().hideWeaponBarrelInOptic(newValue);
	}
}



/**
*	@brief Option for hiding clothing while aiming down sight in an optic
*/
class SUCOption_HideClothingInOptic : SUserConfigOption<bool> {
	
	void SUCOption_HideClothingInOptic(bool value, SConstraintBase constraint = null, SUserConfigOptionInfo info = null) {
		if (!info) {
			m_info = new SUserConfigOptionInfo("#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_HIDE_CLOTHING", "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_HIDE_CLOTHING_DESCRIPTION")
		}
	}
	
	override void onValueChange(bool previousValue, bool newValue) {
		SUserConfig.gunplay().hideClothingInOptic(newValue);
	}
}



/**
*	@brief Option for intensity of lens magnification effect
*/
class SUCOption_LensZoomStrength : SUserConfigOption<float> {
	
	void SUCOption_LensZoomStrength(float value, SConstraintBase constraint = null, SUserConfigOptionInfo info = null) {
		if (!info) {
			m_info = new SUserConfigOptionInfo("#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_LENSZOOM", "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_LENSZOOM_DESCRIPTION");
		}
	}
	
	override void onValueChange(float previousValue, float newValue) {
		SUserConfig.gunplay().setLensZoomStrength(newValue);
	}
}



/**
*	@brief Option for deadzone limits, defined clockwise [UP, RIGHT, DOWN, LEFT]
*/
class SUCOption_DeadzoneLimits : SUserConfigOptionArray<float> {
	
	void SUCOption_DeadzoneLimits(array<float> value, SConstraintBase constraint = null, SUserConfigOptionInfo info = null) {
		if (!info) {
			m_info = new SUserConfigOptionInfo("#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE", "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE_DESCRIPTION");
		}
	}
	
	override void onValueChange(array<float> previousValue, array<float> newValue) {
		SUserConfig.gunplay().setDeadzoneLimits(newValue);
	}
}



/**
*	@brief 
*/
class SUCOption_ResetDeadzonOnFocus : SUserConfigOption<bool> {
	
	void SUCOption_ResetDeadzonOnFocus(bool value, SConstraintBase constraint = null, SUserConfigOptionInfo info = null) {
		if (!info) {
			m_info = new SUserConfigOptionInfo("#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE_RESET_ON_FOCUS", "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE_RESET_ON_FOCUS_DESCRIPTION")
		}
	}
	
	override void onValueChange(bool previousValue, bool newValue) {
		SUserConfig.gunplay().resetDeadzoneOnFocus(newValue);
	}
	
}



/**
*	@brief 
*/
class SUCOption_ShowDynamicCrosshair : SUserConfigOption<bool> {
	
	void SUCOption_ShowDynamicCrosshair(bool value, SConstraintBase constraint = null, SUserConfigOptionInfo info = null) {
		if (!info) {
			m_info = new SUserConfigOptionInfo("#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR", "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_DESCRIPTION")
		}
	}
	
	override void onValueChange(bool previousValue, bool newValue) {
		SUserConfig.gunplay().setDynamicCrosshairEnabled(newValue);
	}
	
}

/**
*	@brief 
*/
class SUCOption_DynamicCrosshairType : SUserConfigOption<int> {
	
	void SUCOption_DynamicCrosshairType(int value, SConstraintBase constraint = null, SUserConfigOptionInfo info = null) {
		if (!info) {
			m_info = new SUserConfigOptionInfo("#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_TYPE", "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_TYPE_DESCRIPTION")
		}
	}
	
	override void onValueChange(int previousValue, int newValue) {
		SUserConfig.gunplay().setDynamicCrosshairType(newValue);
	}
	
}

/**
*	@brief 
*/
class SUCOption_DynamicCrosshairRGBA : SUserConfigOptionArray<float> {
	
	void SUCOption_DynamicCrosshairRGBA(array<float> value, SConstraintBase constraint = null, SUserConfigOptionInfo info = null) {
		if (!info) {
			m_info = new SUserConfigOptionInfo("#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_COLOR", "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR_COLOR_DESCRIPTION")
		}
	}
	
	override void onValueChange(array<float> previousValue, array<float> newValue) {
		SUserConfig.gunplay().setDynamicCrosshairColor(SColor.rgba(newValue[0], newValue[1], newValue[2], newValue[3]));
	}
	
}