modded class IngameHud {

	protected ref Widget m_sCrosshairRoot;
	protected ref ImageWidget m_sCrosshair;
	protected PlayerBase m_player;
	

	void IngameHud(){
		m_sCrosshairRoot = GetGame().GetWorkspace().CreateWidgets( getCrosshairLayoutName(), m_HudPanelWidget );
		m_sCrosshair = ImageWidget.Cast(m_sCrosshairRoot.FindWidget("img_crosshair"));
		
	}
	
	string getCrosshairLayoutName(){
		return "MyMODS/sGunplay/scripts/5_Mission/gui/crosshair/sCrosshair.layout";
	}
	
	override void Update( float timeslice ){
		super.Update( timeslice );
		m_player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!m_player) return; //@todo temp-fix, change this
		
		m_sCrosshairRoot.Unlink();
		m_sCrosshairRoot = GetGame().GetWorkspace().CreateWidgets( getCrosshairLayoutName(), m_HudPanelWidget );
		m_sCrosshair = ImageWidget.Cast(m_sCrosshairRoot.FindWidget("img_crosshair"));
		
		if (!canShowCrosshair()) {
			m_sCrosshair.Show(false);
			return;
		}
		
		vector pos = m_player.GetAimingModel().getSCrosshairPosition();
		m_sCrosshairRoot.SetPos(pos[0], pos[1]);
		
		m_sCrosshair.Show(true);
	
		/*
		m_sCrosshair.LoadImageFile(0, "set:dayz_crosshairs image:imperfect");
		m_sCrosshair.SetImage(0);	
		m_sCrosshair.SetSize(50, 50);
		*/
	}
	
	protected bool canShowCrosshair(){
		return SUserConfig.gunplay().isDynamicCrosshairEnabled() && m_player && m_player.IsFireWeaponRaised() && (!m_player.IsInIronsights() && !m_player.IsInOptics());
	}

}