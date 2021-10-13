class OptionsMenuSGunplay : SOptionsMenuBase{
	
	override string getName(){
		return "sGunplay";
	}
	
	override string getLayout(){
		return "MyMODS/sGunplay/GUI/layouts/optionsMenu/sGunplay_tab.layout";	
	}
	
	override string getInfoBoxRootContainer() {
		return "c_description_box_root";
	}
		
	protected ref SliderWidget    m_adsDOFIntensitySlider;	
	protected ref CheckBoxWidget  m_hideBarrel;
	protected ref CheckBoxWidget  m_hideClothing;	
	protected ref SliderWidget    m_lensZoomSlider;	
	protected ref SliderWidget    m_deadzoneUpDownSlider;	
	protected ref SliderWidget    m_deadzoneLeftRightSlider;
	protected ref CheckBoxWidget  m_resetDeadzoneOnFocus;
	protected ref CheckBoxWidget  m_dynamicCrosshair;	

	protected static const ref TIntArray INDICES_UP_DOWN = {0, 2};
	protected static const ref TIntArray INDICES_LEFT_RIGHT = {1, 3};
	
	override void onInit(){
		super.onInit();
		setUserConfig(SUserConfig.gunplay());
	}
	
	override void onBuild(){
		super.onBuild();
		
		initOptionWidget(m_adsDOFIntensitySlider,   "sude_adsDOFIntensity_setting_option",    m_sUserConfig.getOptionFloat("adsDOFIntensity"));
		initOptionWidget(m_hideBarrel,              "sude_hideBarrel_setting_option",         m_sUserConfig.getOptionBool("hideWeaponBarrelInOptic"));
		initOptionWidget(m_hideClothing,            "sude_hideClothing_setting_option",       m_sUserConfig.getOptionBool("hideClothingInOptic"));
		initOptionWidget(m_lensZoomSlider,          "sude_lensZoom_setting_option",           m_sUserConfig.getOptionFloat("lensZoomStrength"));
		initOptionWidget(m_deadzoneUpDownSlider,    "sude_deadzone_UpDown_setting_option",    m_sUserConfig.getOptionArrayFloat("deadzoneLimits"), INDICES_UP_DOWN);
		initOptionWidget(m_deadzoneLeftRightSlider, "sude_deadzone_LeftRight_setting_option", m_sUserConfig.getOptionArrayFloat("deadzoneLimits"), INDICES_LEFT_RIGHT);
		initOptionWidget(m_resetDeadzoneOnFocus,    "sude_resetOnFocus_setting_option",       m_sUserConfig.getOptionBool("resetDeadzoneOnFocus"));
		initOptionWidget(m_dynamicCrosshair,        "sude_dynamicCrosshair_setting_option",   m_sUserConfig.getOptionBool("showDynamicCrosshair"));
	}
	
}