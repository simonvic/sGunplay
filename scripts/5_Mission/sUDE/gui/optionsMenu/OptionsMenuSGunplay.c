class OptionsMenuSGunplay : SOptionsMenuBase {
	
	override string getName() {
		return "sGunplay";
	}
	
	override string getLayout() {
		return "MyMODS/sGunplay/GUI/layouts/optionsMenu/sGunplay_tab.layout";	
	}
	
	override string getInfoBoxRootContainer() {
		return "c_description_box_root";
	}
		
	protected ref SliderWidget    m_adsFOVMultiplier;	
	protected ref SliderWidget    m_adsDOFIntensitySlider;	
	protected ref CheckBoxWidget  m_hideBarrel;
	protected ref CheckBoxWidget  m_hideClothing;	
	protected ref SliderWidget    m_lensZoomSlider;	
	protected ref SliderWidget    m_deadzoneUpDownSlider;	
	protected ref SliderWidget    m_deadzoneLeftRightSlider;
	protected ref CheckBoxWidget  m_resetDeadzoneOnFocus;
	protected ref CheckBoxWidget  m_dynamicCrosshair;	
	protected ref XComboBoxWidget m_dynamicCrosshairType;
	protected ref SliderWidget    m_dynamicCrosshairRed;
	protected ref SliderWidget    m_dynamicCrosshairGreen;
	protected ref SliderWidget    m_dynamicCrosshairBlue;
	protected ref SliderWidget    m_dynamicCrosshairAlpha;
	
	protected static const ref TIntArray INDICES_UP_DOWN = {0, 2};
	protected static const ref TIntArray INDICES_LEFT_RIGHT = {1, 3};
	
	override void onInit() {
		super.onInit();
		setUserConfig(SUserConfig.gunplay());
	}
	
	override void onBuild() {
		super.onBuild();
		
		initOptionWidget(m_adsFOVMultiplier,        "adsFOVMultiplier",        getUserConfig().getOptionFloat("adsFOVMultiplier"));
		initOptionWidget(m_adsDOFIntensitySlider,   "adsDOFIntensity",         getUserConfig().getOptionFloat("adsDOFIntensity"));
		initOptionWidget(m_hideBarrel,              "hideWeaponBarrelInOptic", getUserConfig().getOptionBool("hideWeaponBarrelInOptic"));
		initOptionWidget(m_hideClothing,            "hideClothingInOptic",     getUserConfig().getOptionBool("hideClothingInOptic"));
		initOptionWidget(m_lensZoomSlider,          "lensZoomStrength",        getUserConfig().getOptionFloat("lensZoomStrength"));
		initOptionWidget(m_deadzoneUpDownSlider,    "deadzoneY",               getUserConfig().getOptionArrayFloat("deadzoneLimits"), INDICES_UP_DOWN);
		initOptionWidget(m_deadzoneLeftRightSlider, "deadzoneX",               getUserConfig().getOptionArrayFloat("deadzoneLimits"), INDICES_LEFT_RIGHT);
		initOptionWidget(m_resetDeadzoneOnFocus,    "resetDeadzoneOnFocus",    getUserConfig().getOptionBool("resetDeadzoneOnFocus"));
		initOptionWidget(m_dynamicCrosshair,        "dynCrosshair",            getUserConfig().getOptionBool("showDynamicCrosshair"));
		initOptionWidget(m_dynamicCrosshairType,    "dynCrosshairStyle",       getUserConfig().getOptionInt("dynamicCrosshairType"), SCrosshair.getStyleNames());
		initOptionWidget(m_dynamicCrosshairRed,     "dynCrosshairRed",         getUserConfig().getOptionArrayFloat("dynamicCrosshairRGBA"), 0);
		initOptionWidget(m_dynamicCrosshairGreen,   "dynCrosshairGreen",       getUserConfig().getOptionArrayFloat("dynamicCrosshairRGBA"), 1);
		initOptionWidget(m_dynamicCrosshairBlue,    "dynCrosshairBlue",        getUserConfig().getOptionArrayFloat("dynamicCrosshairRGBA"), 2);
		initOptionWidget(m_dynamicCrosshairAlpha,   "dynCrosshairAlpha",       getUserConfig().getOptionArrayFloat("dynamicCrosshairRGBA"), 3);
	}
	
}