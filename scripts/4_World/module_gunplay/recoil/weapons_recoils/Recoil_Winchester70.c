modded class Winchester70Recoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 3.285,  7.565,  8.795};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.500;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.750,  2.575};
		mouseTime          = 0.200;
	
		kick               = 0.045;
		kickResetTime      = 1.250;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -1.52;
		m_handsMaxHorizontalRecoil = 1.34;
		
		m_handsMinVerticalRecoil = 1.85;
		m_handsMaxVerticalRecoil = 1.94;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 1.525;
		
		m_relativeReloadTime = 2;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 5.65;
		m_MouseOffsetRelativeTime = 0.0325;
	
		m_CamOffsetDistance = 0.073;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
}