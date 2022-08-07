modded class M4a1Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.350, 0.450,  1.250,  1.300};	
		handsAccumSpeed    = 0.95;
		handsResetSpeed    = 0.400;
		misalignIntensity  = 0.25;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseResetTime     = 0.15;
	
		kick               = 0.045;
		kickResetTime      = 2.25;
	}

	override void Init(){
		m_handsMinHorizontalRecoil = -0.08;
		m_handsMaxHorizontalRecoil = 0.105;
				
		m_handsMinVerticalRecoil = 1.255;
		m_handsMaxVerticalRecoil = 1.385;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 75;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 3.5;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.023;
		m_CamOffsetRelativeTime = 0.5;
		
		createHandRecoilPoints();
	}
}