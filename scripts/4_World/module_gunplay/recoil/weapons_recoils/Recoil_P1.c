modded class P1Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.750, 1.250,  4.050,  5.200};	
		handsAccumSpeed    = 0.925;
		handsResetSpeed    = 0.750;
		
		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
		
		mouseRanges        = { -0.575, 0.700,  0.550,  1.050};
		mouseTime          = 0.050;
	
		kick               = 0.045;
		kickResetTime      = 1.250;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.225;
		m_handsMaxHorizontalRecoil = 0.350;
		
		m_handsMinVerticalRecoil = 0.550;
		m_handsMaxVerticalRecoil = 0.650;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 55;
		m_MouseOffsetRangeMax = 85;
		m_MouseOffsetDistance = 2.7;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.03;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
	
}