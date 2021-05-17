modded class DayZPlayerImplementAiming{
	
	protected float m_dragXVel[1];
	protected float m_dragYVel[1];
	
	override bool ProcessAimFilters(float pDt, SDayZPlayerAimingModel pModel, int stance_index){
		bool result = super.ProcessAimFilters(pDt, pModel, stance_index);
		//pModel.m_fAimXHandsOffset *= 5;
		//pModel.m_fAimYHandsOffset *= 5;
		
		float aimChangeX = m_PlayerDpi.GetInputController().GetAimChange()[0] * Math.RAD2DEG;
		float aimChangeY = m_PlayerDpi.GetInputController().GetAimChange()[1] * Math.RAD2DEG;
		
		float dragMultiplier = 5;
		Weapon_Base weap = Weapon_Base.Cast(m_PlayerPb.GetItemInHands());
		if(weap) dragMultiplier = weap.GetWeight() / 1000;
		aimChangeX *= dragMultiplier ;
		aimChangeY *= dragMultiplier ;
				

		pModel.m_fAimXHandsOffset = Math.SmoothCD(pModel.m_fAimXHandsOffset, pModel.m_fAimXHandsOffset - aimChangeX, m_dragXVel, GunplayConstants.HANDS_DRAG_SMOOTHNESS, 1000, pDt);
		pModel.m_fAimYHandsOffset = Math.SmoothCD(pModel.m_fAimYHandsOffset, pModel.m_fAimYHandsOffset - aimChangeY, m_dragYVel, GunplayConstants.HANDS_DRAG_SMOOTHNESS, 1000, pDt);
		
		DayZPlayerCameraIronsights.m_weaponDeadzoneX = pModel.m_fAimXHandsOffset ;
		DayZPlayerCameraIronsights.m_weaponDeadzoneY = pModel.m_fAimYHandsOffset ;
		
		return result;
	}
}