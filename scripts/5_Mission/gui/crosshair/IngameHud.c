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
		
		if(m_player){
			vector pos = m_player.GetAimingModel().getSCrosshairPosition();
			pos[0] = pos[0] - 0.5;
			pos[1] = pos[1] - 0.5;
			setSCrosshairPosition(pos[0], pos[1]); //@todo center the image
			m_sCrosshair.Show(canShowCrosshair());
		}else{
			m_player = PlayerBase.Cast(GetGame().GetPlayer());
			
		}
		
		/*
		m_sCrosshair.LoadImageFile(0, "set:dayz_crosshairs image:imperfect");
		m_sCrosshair.SetImage(0);	
		m_sCrosshair.SetSize(50, 50);
		*/
	}
	
	protected bool canShowCrosshair(){
		return m_player && (!m_player.IsInIronsights() && !m_player.IsInOptics()) && !GetGame().GetWorld().IsCrosshairDisabled() && SUserConfig.gunplay().isDynamicCrosshairEnabled();
	}

}