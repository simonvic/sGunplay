class OptionsMenuSGunplay extends ScriptedWidgetEventHandler{
	
	static const string LENSZOOM_WIDGET_NAME = "sude_lensZoom_setting_";
	
	//============DEBUG===============
	static const string DEBUG_BODYCLIP_ALLCONTACT_WIDGET_NAME = "sude_body_clip_all_contact_setting_";
	static const string DEBUG_BODYCLIP_CONTACTPOS_WIDGET_NAME = "sude_body_clip_contact_pos_setting_";
	static const string DEBUG_CROSSHAIR_WIDGET_NAME = "sude_crosshair_setting_";

	//================================
	
	protected Widget						m_Root;
	
	protected Widget						m_DetailsRoot;
	protected TextWidget					m_DetailsLabel;
	protected RichTextWidget				m_DetailsText;
	
	protected Widget						m_SettingsRoot;
		
	
	//==============DEBUG=============
		
	protected ref CheckBoxWidget			m_bodyClipAllContact;
	protected ref CheckBoxWidget			m_bodyClipContactPos;
	protected ref CheckBoxWidget			m_debugCrosshair;

	//================================
	
	protected OptionsMenu					m_Menu;
	
	protected ref map<int, ref Param2<string, string>> m_TextMap;
	
	void OptionsMenuSGunplay( Widget parent, Widget details_root, OptionsMenu menu ){
		
		m_Root = GetGame().GetWorkspace().CreateWidgets( GetLayoutName(), parent );			
		
		m_DetailsRoot				= details_root;
		m_DetailsLabel				= TextWidget.Cast( m_DetailsRoot.FindAnyWidget( "details_label" ) );
		m_DetailsText				= RichTextWidget.Cast( m_DetailsRoot.FindAnyWidget( "details_content" ) );
		
		m_Menu = menu;

		
		
		//==============DEBUG=============
		m_bodyClipAllContact = CheckBoxWidget.Cast(m_Root.FindAnyWidget( DEBUG_BODYCLIP_ALLCONTACT_WIDGET_NAME+"option" ));
		m_bodyClipAllContact.SetChecked(PluginSDebug.bodyClipAllContact_enabled);
		
		m_bodyClipContactPos = CheckBoxWidget.Cast(m_Root.FindAnyWidget( DEBUG_BODYCLIP_CONTACTPOS_WIDGET_NAME+"option" ));
		m_bodyClipContactPos.SetChecked(PluginSDebug.bodyClipContactPos_enabled);
		
		m_debugCrosshair = CheckBoxWidget.Cast(m_Root.FindAnyWidget( DEBUG_CROSSHAIR_WIDGET_NAME+"option" ));
		m_debugCrosshair.SetChecked(PluginSDebug.crosshair_enabled);		
		//================================
		
		
		FillTextMap();	
		
		//============DEBUG===============
		m_bodyClipAllContact.SetHandler(this);
		m_bodyClipContactPos.SetHandler(this);
		
		m_Root.SetHandler( this );
		
	}
	
	void ~OptionsMenuSGunplay(){
		
	}
	
	string GetLayoutName(){
		return "MyMODS/sGunplay/scripts/5_Mission/gui/newui/options/sGunplay_tab.layout";
	}
	
	
	override bool OnChange(Widget w, int x, int y, bool finished){
		
		if(w && w.IsInherited( SliderWidget )){
			SliderWidget s = SliderWidget.Cast(w);
			
			switch(s.GetName()){
				default: SLog.w("No slider widget name found.","OnChange");
			}
				
		}
		
		if(w && w.IsInherited( CheckBoxWidget )){
			CheckBoxWidget c = CheckBoxWidget.Cast(w);
			
			switch(c.GetName()){
				case LENSZOOM_WIDGET_NAME+"option":{
					UpdateLensZoomOption(c.IsChecked());
					break;
				}
				case DEBUG_BODYCLIP_ALLCONTACT_WIDGET_NAME+"option":{
					UpdateBodyClipAllContactOption(c.IsChecked());
					break;
				}
				case DEBUG_BODYCLIP_CONTACTPOS_WIDGET_NAME+"option":{
					UpdateBodyClipContactPosOption(c.IsChecked());
					break;
				}
				case DEBUG_CROSSHAIR_WIDGET_NAME+"option":{
					UpdateDebugCrosshairOption(c.IsChecked());
					break;
				}
				default: SLog.w("No checkbox  widget name found.","OnChange");
			}
				
		}
		return true;
		
	}
	
		
	void UpdateLensZoomOption( bool enabled){
		//LensZoomParams.enabled = enabled;
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
		
	override bool OnFocus( Widget w, int x, int y ){		
		if( m_Menu ){
			m_Menu.OnFocus( w, x, y );
		}
		
		if( w ){
			if ( TextMapUpdateWidget( w.GetUserID() ) ) {
				return true;
			}		
		}
		m_DetailsRoot.Show( false );
		return ( w != null );
	}
	
	bool TextMapUpdateWidget(int key){
		Param2<string, string> p = m_TextMap.Get( key );
		if( p ){
			m_DetailsRoot.Show( true );
			m_DetailsLabel.SetText( p.param1 );
			m_DetailsText.SetText( p.param2 );
			
			//float lines = m_DetailsText.GetContentHeight();
			//m_DetailsText.SetSize( 1, lines );
			
			m_DetailsText.Update();
			m_DetailsLabel.Update();
			m_DetailsRoot.Update();
			return true;
		}
		return false;
	}
	
	void FillTextMap(){ //to-do finish option description
		m_TextMap = new map<int, ref Param2<string, string>>;
		m_TextMap.Insert( 1, new Param2<string, string>( "Title", "description" ) );
		m_TextMap.Insert( 2, new Param2<string, string>( "Title", "description" ) );
		m_TextMap.Insert( 3, new Param2<string, string>( "Title", "description" ) );
		m_TextMap.Insert( 4, new Param2<string, string>( "Title", "description" ) );
	}

}