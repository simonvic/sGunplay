modded class Ak101Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.065, 0.085,  1.265,  1.495};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.550;
		
		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.550;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.200;
	
		kick               = 0.054;
		kickResetTime      = 2.250;
	}
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.105;
		m_handsMaxHorizontalRecoil = 0.142;
				
		m_handsMinVerticalRecoil = 1.290;
		m_handsMaxVerticalRecoil = 1.242;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 75;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 3.5;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.032;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}