modded class Cz75Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.750, 1.250,  4.450,  5.600};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.750;
		
		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.500;
		
		mouseRanges        = { -0.575, 0.700,  0.550,  1.050};
		mouseTime          = 0.050;
	
		kick               = 0.075;
		kickResetTime      = 1.250;
	}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -0.1;
		m_handsMaxHorizontalRecoil = 0.120;
		
		m_handsMinVerticalRecoil = 0.445;
		m_handsMaxVerticalRecoil = 0.765;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 60;
		m_MouseOffsetRangeMax = 110;
		m_MouseOffsetDistance = 2.7;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.02;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}