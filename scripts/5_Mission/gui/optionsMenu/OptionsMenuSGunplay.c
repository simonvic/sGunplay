class OptionsMenuSGunplay : SOptionsMenuBase{
	
	override string getName(){
		return "sGunplay";
	}
	
	override string getLayout(){
		return "MyMODS/sGunplay/GUI/layouts/optionsMenu/sGunplay_tab.layout";	
	}
		
	protected ref SSliderWidget   m_lensZoomSlider;	
	protected ref SSliderWidget   m_adsDOFIntensitySlider;	
	protected ref CheckBoxWidget  m_hideBarrel;
	protected ref CheckBoxWidget  m_hideClothing;	
	protected ref CheckBoxWidget  m_dynamicCrosshair;	
	protected ref CheckBoxWidget  m_resetDeadzoneOnFocus;
	protected ref SSliderWidget   m_deadzoneUpDownSlider;	
	protected ref SSliderWidget   m_deadzoneLeftRightSlider;
	protected ref SSliderWidget   m_deadzoneUpSlider;	
	protected ref SSliderWidget   m_deadzoneRightSlider;
	protected ref SSliderWidget   m_deadzoneDownSlider;	
	protected ref SSliderWidget   m_deadzoneLeftSlider;
	
	protected SUserConfigGunplay m_sUserConfig;
	
	void OptionsMenuSGunplay(){
		m_sUserConfig = SUserConfig.gunplay();
	}
	
	override void onBuild(){
		super.onBuild();
		
		initOption(m_lensZoomSlider,          "sude_lensZoom_setting_",                 m_sUserConfig.getLensZoomStrength());
		initOption(m_adsDOFIntensitySlider,   "sude_adsDOFIntensity_setting_",          m_sUserConfig.getAdsDOFIntensity());
		initOption(m_hideBarrel,              "sude_hideBarrel_setting_option",         m_sUserConfig.isHideWeaponBarrelInOpticEnabled());
		initOption(m_hideClothing,            "sude_hideClothing_setting_option",       m_sUserConfig.isHideClothingInOpticEnabled());
		initOption(m_dynamicCrosshair,        "sude_dynamicCrosshair_setting_option",   m_sUserConfig.isDynamicCrosshairEnabled());
		initOption(m_resetDeadzoneOnFocus,    "sude_resetOnFocus_setting_option",       m_sUserConfig.isResetDeadzoneOnFocusEnabled());
		
		TFloatArray deadzoneLimits = m_sUserConfig.getDeadzoneLimits();
		initOption(m_deadzoneUpDownSlider,    "sude_deadzone_UpDown_setting_",          deadzoneLimits[0]);
		initOption(m_deadzoneLeftRightSlider, "sude_deadzone_LeftRight_setting_",       deadzoneLimits[1]);
		initOption(m_deadzoneUpSlider,        "sude_deadzoneUp_setting_",               deadzoneLimits[0]);
		initOption(m_deadzoneRightSlider,     "sude_deadzoneRight_setting_",            deadzoneLimits[1]);
		initOption(m_deadzoneDownSlider,      "sude_deadzoneDown_setting_",             deadzoneLimits[2]);
		initOption(m_deadzoneLeftSlider,      "sude_deadzoneLeft_setting_",             deadzoneLimits[3]);
		
	}
	
	
	
	
	override bool onChange(SliderWidget w){
		switch(w){
			case m_lensZoomSlider.getSliderWidget():          updateLensZoomOption(w.GetCurrent()); break;
			case m_adsDOFIntensitySlider.getSliderWidget():   updateAdsDOFIntensity(w.GetCurrent()); break;
			case m_deadzoneUpDownSlider.getSliderWidget():    updateDeadzoneUpDownOption(w.GetCurrent()); break;
			case m_deadzoneLeftRightSlider.getSliderWidget(): updateDeadzoneLeftRightOption(w.GetCurrent()); break;
			//default: SLog.w("No slider widget name found.","OptionsMenuSGunplay::onChange"); return false;
		}
		return true;
	}
	
	override bool onChange(CheckBoxWidget w){
		switch(w){
			case m_hideBarrel:           updateHideBarrelOption(w.IsChecked()); break;
			case m_hideClothing:         updateHideClothingOption(w.IsChecked()); break;
			case m_dynamicCrosshair:     updateDynamicCrosshairOption(w.IsChecked()); break;
			case m_resetDeadzoneOnFocus: updateResetDeadzoneOnFocus(w.IsChecked()); break;
			//default: SLog.w("No checkbox widget name found.","OptionsMenuSGunplay::onChange"); return false;
		}
		return true;
	}
	
	
	
	
	
	
	protected void updateLensZoomOption( float newValue){
		m_lensZoomSlider.updateTextValue();
		m_sUserConfig.setLensZoomStrength(newValue);
		onConfigChange();
	}
	
	protected void updateAdsDOFIntensity(float newValue){
		m_adsDOFIntensitySlider.updateTextValue();
		m_sUserConfig.setAdsDOFIntensity(newValue);	
		onConfigChange();
	}
	
	protected void updateResetDeadzoneOnFocus(bool enabled){
		m_sUserConfig.resetDeadzoneOnFocus(enabled);
		onConfigChange();
	}
	
	protected void updateDeadzoneUpDownOption(float newValue){
		m_deadzoneUpDownSlider.updateTextValue();
		m_sUserConfig.setDeadzoneLimit(0, newValue);
		m_sUserConfig.setDeadzoneLimit(2, newValue);
		onConfigChange();
	}
	
	protected void updateDeadzoneLeftRightOption(float newValue){
		m_deadzoneLeftRightSlider.updateTextValue();
		m_sUserConfig.setDeadzoneLimit(1, newValue);
		m_sUserConfig.setDeadzoneLimit(3, newValue);
		onConfigChange();
	}
	
	protected void updateDeadzoneOption(int i, float newValue){
		switch(i){
			case 0 : m_deadzoneUpSlider.updateTextValue(); break;
			case 1 : m_deadzoneRightSlider.updateTextValue(); break;
			default: SLog.w("Wrong deadzone");
		}
		m_deadzoneUpDownSlider.updateTextValue();
		m_deadzoneLeftRightSlider.updateTextValue();
		m_sUserConfig.setDeadzoneLimit(i, newValue);
		onConfigChange();
	}
		
	protected void updateHideBarrelOption(bool enabled){
		m_sUserConfig.hideWeaponBarrelInOptic(enabled);
		onConfigChange();
	}
	
	protected void updateHideClothingOption(bool enabled){
		m_sUserConfig.hideClothingInOptic(enabled);
		onConfigChange();
	}
	
	protected void updateDynamicCrosshairOption(bool enabled){
		m_sUserConfig.setDynamicCrosshairEnabled(enabled);
		onConfigChange();
	}
	
	protected void onConfigChange(){ //@todo lol change this shit
		m_sUserConfig.save();
	}
	
}