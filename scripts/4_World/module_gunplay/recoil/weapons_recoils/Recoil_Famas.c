modded class FamasRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.250, 0.550,  2.750,  3.985};	
		handsAccumSpeed    = 0.920;
		handsResetSpeed    = 0.700;
		
		misalignIntensity  = {0.125, 0.125};
		misalignAccumSpeed = 0.925;
		misalignResetSpeed = 0.750;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.015;
		kickResetTime      = 2.250;
	}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -0.08;
		m_handsMaxHorizontalRecoil = 0.105;
				
		m_handsMinVerticalRecoil = 0.755;
		m_handsMaxVerticalRecoil = 0.985;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 75;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 2.8;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.023;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}