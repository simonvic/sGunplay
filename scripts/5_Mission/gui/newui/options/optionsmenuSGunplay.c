class OptionsMenuSGunplay extends ScriptedWidgetEventHandler{
	
	protected SUserConfigGunplay m_sUserConfig;
	
	
	///////////////// DEBUG /////////////////
	static const string DEBUG_BODYCLIP_ALLCONTACT_WIDGET_NAME = "sude_body_clip_all_contact_setting_";
	static const string DEBUG_BODYCLIP_CONTACTPOS_WIDGET_NAME = "sude_body_clip_contact_pos_setting_";
	static const string DEBUG_CROSSHAIR_WIDGET_NAME = "sude_crosshair_setting_";
	//////////////////////////////////
	
	static const string WN_LENSZOOM = "sude_lensZoom_setting_";
	static const string WN_ADS_DOF_INTENSITY = "sude_adsDOFIntensity_setting_";
	static const string WN_HIDE_BARREL = "sude_hideBarrel_setting_";
	static const string WN_HIDE_CLOTHING = "sude_hideClothing_setting_";
	static const string WN_DYNAMIC_CROSSHAIR = "sude_dynamicCrosshair_setting_";
	
	static const string WN_RESET_DEADZONE_ON_FOCUS = "sude_resetOnFocus_setting_";
	static const string WN_DEADZONE_UP_DOWN = "sude_deadzone_UpDown_setting_";
	static const string WN_DEADZONE_LEFT_RIGHT = "sude_deadzone_LeftRight_setting_";
	static const string WN_DEADZONE_UP = "sude_deadzoneUp_setting_";
	static const string WN_DEADZONE_RIGHT = "sude_deadzoneRight_setting_";
	static const string WN_DEADZONE_DOWN = "sude_deadzoneDown_setting_";
	static const string WN_DEADZONE_LEFT = "sude_deadzoneLeft_setting_";	
	
	//////////////////////////////////

	protected Widget						m_Root;
	protected Widget						m_DetailsRoot;
	protected TextWidget					m_DetailsLabel;
	protected RichTextWidget				m_DetailsText;	
	protected Widget						m_SettingsRoot;
		
	
	///////////////// DEBUG /////////////////
	protected ref CheckBoxWidget			m_bodyClipAllContact;
	protected ref CheckBoxWidget			m_bodyClipContactPos;
	protected ref CheckBoxWidget			m_debugCrosshair;
	//////////////////////////////////
	
	protected ref SliderWidget              m_lensZoomSlider;
	protected ref TextWidget                m_lensZoomValue;
	
	protected ref SliderWidget              m_adsDOFIntensitySlider;
	protected ref TextWidget                m_adsDOFIntensityValue;
	
	protected ref CheckBoxWidget            m_hideBarrel;
	protected ref CheckBoxWidget            m_hideClothing;
	
	protected ref CheckBoxWidget            m_dynamicCrosshair;
	
	protected ref CheckBoxWidget            m_resetDeadzoneOnFocus;
	
	protected ref SliderWidget              m_deadzoneUpDownSlider;
	protected ref TextWidget                m_deadzoneUpDownValue;
	
	protected ref SliderWidget              m_deadzoneLeftRightSlider;
	protected ref TextWidget                m_deadzoneLeftRightValue;
	
	protected ref SliderWidget              m_deadzoneUpSlider;
	protected ref TextWidget                m_deadzoneUpValue;
	
	protected ref SliderWidget              m_deadzoneRightSlider;
	protected ref TextWidget                m_deadzoneRightValue;
	
	protected ref SliderWidget              m_deadzoneDownSlider;
	protected ref TextWidget                m_deadzoneDownValue;
	
	protected ref SliderWidget              m_deadzoneLeftSlider;
	protected ref TextWidget                m_deadzoneLeftValue;
	
	
	
	protected OptionsMenu					m_Menu;
	
	protected ref map<int, ref Param2<string, string>> m_TextMap;
	
	void OptionsMenuSGunplay( Widget parent, Widget details_root, OptionsMenu menu ){
		
		//////////////// USER CONFIG ///////////////////
		m_sUserConfig = SUserConfig.gunplay();
		
		//////////////// UI ///////////////////
		m_Root = GetGame().GetWorkspace().CreateWidgets( GetLayoutName(), parent );			
		
		m_DetailsRoot				= details_root;
		m_DetailsLabel				= TextWidget.Cast( m_DetailsRoot.FindAnyWidget( "details_label" ) );
		m_DetailsText				= RichTextWidget.Cast( m_DetailsRoot.FindAnyWidget( "details_content" ) );
		
		m_Menu = menu;

		
		
		////////////////// DEBUG ////////////////////////
		m_bodyClipAllContact = CheckBoxWidget.Cast(m_Root.FindAnyWidget( DEBUG_BODYCLIP_ALLCONTACT_WIDGET_NAME+"option" ));
		m_bodyClipAllContact.SetChecked(PluginSDebug.bodyClipAllContact_enabled);
		
		m_bodyClipContactPos = CheckBoxWidget.Cast(m_Root.FindAnyWidget( DEBUG_BODYCLIP_CONTACTPOS_WIDGET_NAME+"option" ));
		m_bodyClipContactPos.SetChecked(PluginSDebug.bodyClipContactPos_enabled);
		
		m_debugCrosshair = CheckBoxWidget.Cast(m_Root.FindAnyWidget( DEBUG_CROSSHAIR_WIDGET_NAME+"option" ));
		m_debugCrosshair.SetChecked(PluginSDebug.crosshair_enabled);		
		////////////////////////////////////
		
		
		m_lensZoomSlider = SliderWidget.Cast(m_Root.FindAnyWidget(WN_LENSZOOM+"option"));
		m_lensZoomSlider.SetCurrent(m_sUserConfig.getLensZoomStrength());
		m_lensZoomValue = TextWidget.Cast(m_Root.FindAnyWidget(WN_LENSZOOM+"value"));
		m_lensZoomValue.SetText(m_lensZoomSlider.GetCurrent().ToString());
		
		m_adsDOFIntensitySlider = SliderWidget.Cast(m_Root.FindAnyWidget(WN_ADS_DOF_INTENSITY+"option"));
		m_adsDOFIntensitySlider.SetCurrent(m_sUserConfig.getAdsDOFIntensity());
		m_adsDOFIntensityValue = TextWidget.Cast(m_Root.FindAnyWidget(WN_ADS_DOF_INTENSITY+"value"));
		m_adsDOFIntensityValue.SetText(m_adsDOFIntensitySlider.GetCurrent().ToString());
		
		m_hideBarrel = CheckBoxWidget.Cast(m_Root.FindAnyWidget(WN_HIDE_BARREL+"option"));
		m_hideBarrel.SetChecked(m_sUserConfig.isHideWeaponBarrelInOpticEnabled());
		
		m_hideClothing = CheckBoxWidget.Cast(m_Root.FindAnyWidget(WN_HIDE_CLOTHING+"option"));
		m_hideClothing.SetChecked(m_sUserConfig.isHideClothingInOpticEnabled());
		
		m_dynamicCrosshair = CheckBoxWidget.Cast(m_Root.FindAnyWidget(WN_DYNAMIC_CROSSHAIR+"option"));
		m_dynamicCrosshair.SetChecked(m_sUserConfig.isDynamicCrosshairEnabled());
		
		m_resetDeadzoneOnFocus = CheckBoxWidget.Cast(m_Root.FindAnyWidget(WN_RESET_DEADZONE_ON_FOCUS+"option"));
		m_resetDeadzoneOnFocus.SetChecked(m_sUserConfig.isResetDeadzoneOnFocusEnabled());
		
		
		TFloatArray deadzoneLimits = m_sUserConfig.getDeadzoneLimits();
		
		m_deadzoneUpDownSlider = SliderWidget.Cast(m_Root.FindAnyWidget(WN_DEADZONE_UP_DOWN+"option"));
		m_deadzoneUpDownSlider.SetCurrent(deadzoneLimits[0]);
		m_deadzoneUpDownValue = TextWidget.Cast(m_Root.FindAnyWidget(WN_DEADZONE_UP_DOWN+"value"));
		m_deadzoneUpDownValue.SetText(m_deadzoneUpDownSlider.GetCurrent().ToString());
		
		m_deadzoneLeftRightSlider = SliderWidget.Cast(m_Root.FindAnyWidget(WN_DEADZONE_LEFT_RIGHT+"option"));
		m_deadzoneLeftRightSlider.SetCurrent(deadzoneLimits[1]);
		m_deadzoneLeftRightValue = TextWidget.Cast(m_Root.FindAnyWidget(WN_DEADZONE_LEFT_RIGHT+"value"));
		m_deadzoneLeftRightValue.SetText(m_deadzoneLeftRightSlider.GetCurrent().ToString());
		
		m_deadzoneUpSlider = SliderWidget.Cast(m_Root.FindAnyWidget(WN_DEADZONE_UP+"option"));
		m_deadzoneUpSlider.SetCurrent(deadzoneLimits[0]);
		m_deadzoneUpValue = TextWidget.Cast(m_Root.FindAnyWidget(WN_DEADZONE_UP+"value"));
		m_deadzoneUpValue.SetText(m_deadzoneUpSlider.GetCurrent().ToString());
		
		m_deadzoneRightSlider = SliderWidget.Cast(m_Root.FindAnyWidget(WN_DEADZONE_RIGHT+"option"));
		m_deadzoneRightSlider.SetCurrent(deadzoneLimits[1]);
		m_deadzoneRightValue = TextWidget.Cast(m_Root.FindAnyWidget(WN_DEADZONE_RIGHT+"value"));
		m_deadzoneRightValue.SetText(m_deadzoneRightSlider.GetCurrent().ToString());
		
		m_deadzoneDownSlider = SliderWidget.Cast(m_Root.FindAnyWidget(WN_DEADZONE_DOWN+"option"));
		m_deadzoneDownSlider.SetCurrent(deadzoneLimits[2]);
		m_deadzoneDownValue = TextWidget.Cast(m_Root.FindAnyWidget(WN_DEADZONE_DOWN+"value"));
		m_deadzoneDownValue.SetText("-"+m_deadzoneDownSlider.GetCurrent().ToString());
		
		m_deadzoneLeftSlider = SliderWidget.Cast(m_Root.FindAnyWidget(WN_DEADZONE_LEFT+"option"));
		m_deadzoneLeftSlider.SetCurrent(deadzoneLimits[3]);
		m_deadzoneLeftValue = TextWidget.Cast(m_Root.FindAnyWidget(WN_DEADZONE_LEFT+"value"));
		m_deadzoneLeftValue.SetText("-"+m_deadzoneLeftSlider.GetCurrent().ToString());
		
		
		////////////////// TOOLTIP ////////////////////////
		m_TextMap = new map<int, ref Param2<string, string>>;
		int uid = -1;
		addDescriptionTooltip(m_lensZoomSlider,          uid++, "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_LENSZOOM","#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_LENSZOOM_DESCRIPTION");
		addDescriptionTooltip(m_adsDOFIntensitySlider,   uid++, "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_ADS_DOF_INTENSITY","#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_ADS_DOF_INTENSITY_DESCRIPTION");
		addDescriptionTooltip(m_hideBarrel,              uid++, "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_HIDE_BARREL","#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_HIDE_BARREL_DESCRIPTION");
		addDescriptionTooltip(m_hideClothing,            uid++, "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_HIDE_CLOTHING","#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_HIDE_CLOTHING_DESCRIPTION");
		addDescriptionTooltip(m_dynamicCrosshair,        uid++, "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR","#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DYNAMIC_CROSSHAIR");
		addDescriptionTooltip(m_resetDeadzoneOnFocus,    uid++, "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE","#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE_RESET_ON_FOCUS_DESCRIPTION");
		addDescriptionTooltip(m_deadzoneUpDownSlider,    uid++, "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE","#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE_UPDOWN_DESCRIPTION");
		addDescriptionTooltip(m_deadzoneLeftRightSlider, uid++, "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE","#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE_LEFTRIGHT_DESCRIPTION");
		addDescriptionTooltip(m_deadzoneUpSlider,        uid++, "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE","#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE_UP_DESCRIPTION");
		addDescriptionTooltip(m_deadzoneRightSlider,     uid++, "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE","#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE_RIGHT_DESCRIPTION");		
		addDescriptionTooltip(m_deadzoneDownSlider,      uid++, "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE","#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE_DOWN_DESCRIPTION");		
		addDescriptionTooltip(m_deadzoneLeftSlider,      uid++, "#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE","#STR_SUDE_LAYOUT_OPTIONS_GUNPLAY_DEADZONE_LEFT_DESCRIPTION");		
		
		
		////////////////// DEBUG ////////////////////////
		m_bodyClipAllContact.SetHandler(this);
		m_bodyClipContactPos.SetHandler(this);
		////////////////////////////////////
		
		m_lensZoomSlider.SetHandler(this);
		m_adsDOFIntensitySlider.SetHandler(this);
		m_hideBarrel.SetHandler(this);
		m_hideClothing.SetHandler(this);
		m_dynamicCrosshair.SetHandler(this);
		m_resetDeadzoneOnFocus.SetHandler(this);
		m_deadzoneUpDownSlider.SetHandler(this);
		m_deadzoneLeftRightSlider.SetHandler(this);
		m_deadzoneUpSlider.SetHandler(this);
		m_deadzoneRightSlider.SetHandler(this);
		m_deadzoneDownSlider.SetHandler(this);
		m_deadzoneLeftSlider.SetHandler(this);
		
		m_Root.SetHandler( this );
		
	}
	
	void ~OptionsMenuSGunplay(){
		
	}
	
	string GetLayoutName(){
		return "MyMODS/sGunplay/scripts/5_Mission/gui/newui/options/sGunplay_tab.layout";
	}
	
	
	override bool OnChange(Widget w, int x, int y, bool finished){
		
		if(w){
			if(w.IsInherited( SliderWidget )){
				SliderWidget s = SliderWidget.Cast(w);
				
				switch(s.GetName()){
					case WN_LENSZOOM+"option":
						updateLensZoomOption(s.GetCurrent());
						break;
					case WN_ADS_DOF_INTENSITY+"option":
						updateAdsDOFIntensity(s.GetCurrent());
						break;
					
					case WN_DEADZONE_UP_DOWN+"option":
						updateDeadzoneOption(0, s.GetCurrent());
						m_deadzoneUpSlider.SetCurrent(s.GetCurrent());
						updateDeadzoneOption(2, s.GetCurrent());
						m_deadzoneDownSlider.SetCurrent(s.GetCurrent());
						m_deadzoneUpDownValue.SetText(s.GetCurrent().ToString());
						break;
					case WN_DEADZONE_LEFT_RIGHT+"option":
						updateDeadzoneOption(1, s.GetCurrent());
						m_deadzoneLeftSlider.SetCurrent(s.GetCurrent());
						updateDeadzoneOption(3, s.GetCurrent());
						m_deadzoneRightSlider.SetCurrent(s.GetCurrent());
						m_deadzoneLeftRightValue.SetText(s.GetCurrent().ToString());
						break;				
					case WN_DEADZONE_UP+"option":
						updateDeadzoneOption(0, s.GetCurrent());
						break;
					case WN_DEADZONE_RIGHT+"option":
						updateDeadzoneOption(1, s.GetCurrent());
						break;
					case WN_DEADZONE_DOWN+"option":
						updateDeadzoneOption(2, s.GetCurrent());
						break;
					case WN_DEADZONE_LEFT+"option":
						updateDeadzoneOption(3, s.GetCurrent());
						break;
					
					default: SLog.w("No slider widget name found.","OptionsMenuSGunplay::OnChange");
				}
					
			}else if(w.IsInherited( CheckBoxWidget )){
				CheckBoxWidget c = CheckBoxWidget.Cast(w);
				
				switch(c.GetName()){
					case WN_HIDE_BARREL+"option":
						updateHideParrelOption(c.IsChecked());
						break;
					case WN_HIDE_CLOTHING+"option":
						updateHideClothingOption(c.IsChecked());
						break;
					case WN_DYNAMIC_CROSSHAIR+"option":
						updateDynamicCrosshairOption(c.IsChecked());
						break;
					case WN_RESET_DEADZONE_ON_FOCUS+"option":
						updateResetDeadzoneOnFocus(c.IsChecked());
						break;
					default: SLog.w("No checkbox  widget name found.","OptionsMenuSGunplay::OnChange");
				}
					
			}
		}
		return true;
		
	}
	
	
		
	void updateLensZoomOption( float newValue){
		m_lensZoomValue.SetText(newValue.ToString());
		m_sUserConfig.setLensZoomStrength(newValue);
		onConfigChange();
	}
	
	void updateAdsDOFIntensity(float newValue){
		m_adsDOFIntensityValue.SetText(newValue.ToString());
		m_sUserConfig.setAdsDOFIntensity(newValue);	
		onConfigChange();
	}
	
	void updateResetDeadzoneOnFocus(bool enabled){
		m_sUserConfig.resetDeadzoneOnFocus(enabled);
		onConfigChange();
	}
	
	void updateDeadzoneOption(int i, float newValue){
		switch(i){
			case 0 :
				m_deadzoneUpValue.SetText(newValue.ToString());
				break;
			case 1 :
				m_deadzoneRightValue.SetText(newValue.ToString());
				break;
			case 2 :
				m_deadzoneDownValue.SetText("-"+newValue.ToString());
				break;
			case 3 :
				m_deadzoneLeftValue.SetText("-"+newValue.ToString());
				break;
			default: SLog.w("Wrong deadzone");
		}
		m_sUserConfig.setDeadzoneLimit(i, newValue);
		onConfigChange();
	}
		
	void updateHideParrelOption(bool enabled){
		m_sUserConfig.hideWeaponBarrelInOptic(enabled);
		onConfigChange();
	}
	
	void updateHideClothingOption(bool enabled){
		m_sUserConfig.hideClothingInOptic(enabled);
		onConfigChange();
	}
	
	void updateDynamicCrosshairOption(bool enabled){
		m_sUserConfig.setDynamicCrosshairEnabled(enabled);
		onConfigChange();
	}
	
	void UpdateBodyClipAllContactOption( bool enabled){
		PluginSDebug.bodyClipAllContact_enabled = enabled;
	}
	
	void UpdateBodyClipContactPosOption( bool enabled){
		PluginSDebug.bodyClipContactPos_enabled = enabled;
	}
	
	void UpdateDebugCrosshairOption( bool enabled){
		PluginSDebug.crosshair_enabled = enabled;
	}
	
	private void onConfigChange(){ //@todo lol change this shit
		m_sUserConfig.save();
	}
	
	override bool OnFocus( Widget w, int x, int y ){		
		if( w ){
			Param2<string, string> p = m_TextMap.Get( w.GetUserID() );
			if( p ){
				
				m_DetailsRoot.Show( true );
				m_DetailsLabel.SetText( p.param1 );
				m_DetailsText.SetText( p.param2 );
								
				m_DetailsText.Update();
				m_DetailsLabel.Update();
				m_DetailsRoot.Update();
				return true;
			}	
		}
		m_DetailsRoot.Show( false );
		return ( w != null );
	}

	private void addDescriptionTooltip(Widget w, int userID, string title, string description){
		w.SetUserID(userID);
		m_TextMap.Insert(userID, new Param2<string, string>(title, description));
	}
	
}