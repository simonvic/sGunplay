modded class IngameHud {

	protected ref ImageWidget m_sCrosshair;
	

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
		
		vector pos = DayZPlayerImplementAiming.m_sCrosshairPosition;
		setSCrosshairPosition(pos[0] - 0.5, pos[1] - 0.5);
		m_sCrosshair.Show(DayZPlayerImplementAiming.m_isSCrosshairVisible);
		//m_sCrosshair.LoadImageFile(0, "set:dayz_crosshairs image:cross_32x32");
		//m_sCrosshair.SetImage(0);
		
	}

}