modded class PP19Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.060, 0.750,  1.450 ,  1.785};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.550;
		
		misalignIntensity  = {0.250, 0.750};
		misalignAccumSpeed = 0.855;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.035;
		kickResetTime      = 2.250;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.080;
		m_handsMaxHorizontalRecoil = 0.085;
		
		m_handsMinVerticalRecoil = 0.365;
		m_handsMaxVerticalRecoil = 0.495;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 1.5;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 95;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 1.5;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.035;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}