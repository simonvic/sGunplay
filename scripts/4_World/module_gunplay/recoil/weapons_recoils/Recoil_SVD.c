modded class SvdRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 3.285,  7.565,  8.795};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.500;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.750,  2.575};
		mouseTime          = 0.200;
	
		kick               = 0.055;
		kickResetTime      = 3.550;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.82;
		m_handsMaxHorizontalRecoil = 0.64;
		
		m_handsMinVerticalRecoil = 1.15;
		m_handsMaxVerticalRecoil = 1.24;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 3.5;
		
		m_relativeReloadTime = 3.5;
		
		m_MouseOffsetRangeMin = 45;
		m_MouseOffsetRangeMax = 110;
		m_MouseOffsetDistance = 5.95;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.065;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}