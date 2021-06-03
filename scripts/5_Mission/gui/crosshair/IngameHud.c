modded class IngameHud {

	protected ref ImageWidget m_sCrosshair;
	protected PlayerBase m_player;
	

	void IngameHud(){
		Widget sRoot = GetGame().GetWorkspace().CreateWidgets( getCrosshairLayoutName(), m_HudPanelWidget );
		m_sCrosshair = ImageWidget.Cast(sRoot.FindWidget("img_crosshair"));
		
	}
	
	string getCrosshairLayoutName(){
		return "MyMODS/sGunplay/scripts/5_Mission/gui/crosshair/sCrosshair.layout";
	}
	
	void setSCrosshairPosition(float x, float y){
		m_sCrosshair.SetPos(x,y);
	}
	
	override void Update( float timeslice ){
		super.Update( timeslice );
		m_player = PlayerBase.Cast(GetGame().GetPlayer());
		if(!m_player) return; //@todo temp-fix, change this
		
		if(canShowCrosshair()){
			setSCrosshairPosition(m_player.GetAimingModel().getSCrosshairPosition()[0] - 0.5, m_player.GetAimingModel().getSCrosshairPosition()[1] - 0.5); //@todo center the image
			m_sCrosshair.Show(true);
		}else{
			m_sCrosshair.Show(false);
		}
		
		/*
		m_sCrosshair.LoadImageFile(0, "set:dayz_crosshairs image:imperfect");
		m_sCrosshair.SetImage(0);	
		m_sCrosshair.SetSize(50, 50);
		*/
	}
	
	protected bool canShowCrosshair(){
		return m_player && m_player.IsFireWeaponRaised() && (!m_player.IsInIronsights() && !m_player.IsInOptics()) && !GetGame().GetWorld().IsCrosshairDisabled() && SUserConfig.gunplay().isDynamicCrosshairEnabled();
	}

}