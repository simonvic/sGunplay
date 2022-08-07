modded class MkiiRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.150, 0.550,  1.050,  2.200};	
		handsAccumSpeed    = 0.925;
		handsResetSpeed    = 0.750;
		
		misalignIntensity  = {0.150, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
		
		mouseRanges        = { -0.175, 0.500,  0.250,  0.500};
		mouseTime          = 0.050;
	
		kick               = 0.040;
		kickResetTime      = 1.250;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.05;
		m_handsMaxHorizontalRecoil = 0.08;
		
		m_handsMinVerticalRecoil = 0.245;
		m_handsMaxVerticalRecoil = 0.365;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 45;
		m_MouseOffsetRangeMax = 80;
		m_MouseOffsetDistance = 0.75;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.038;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}