modded class OptionsMenu {

	protected ref OptionsMenuSGunplay m_sGunplayTab;
	
	override Widget Init(){
		Widget temp = super.Init();
		
		int newIndex = m_Tabber.GetTabCount(); //make it last so we son't have problem with possible future additions
		m_Tabber.AddTab(newIndex.ToString()); 
				
		TextWidget.Cast( layoutRoot.FindAnyWidget( "Tab_Control_"+newIndex+"_Title" )).SetText("sGunplay");
		m_sGunplayTab	= new OptionsMenuSGunplay( layoutRoot.FindAnyWidget( "Tab_" + newIndex ), m_Details, this );
		
		return temp;
		
	}	
}
