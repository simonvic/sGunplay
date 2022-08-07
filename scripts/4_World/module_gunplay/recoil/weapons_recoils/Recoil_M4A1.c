modded class M4a1Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.050, 2.250,  2.750 ,  3.985};	
		handsAccumSpeed    = 0.950;
		handsResetSpeed    = 0.400;
		
		misalignIntensity  = {0.750, 0.750};
		misalignAccumSpeed = 0.905;
		misalignResetSpeed = 0.750;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.045;
		kickResetTime      = 2.250;
	}

	override void Init() {
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