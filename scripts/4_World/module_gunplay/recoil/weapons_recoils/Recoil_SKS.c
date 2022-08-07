modded class SKSRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 3.285,  5.275,  6.050};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.550;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.550,  2.275};
		mouseTime          = 0.200;
	
		kick               = 0.040;
		kickResetTime      = 3.250;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.735;
		m_handsMaxHorizontalRecoil = 0.165;
		
		m_handsMinVerticalRecoil = 1.715;
		m_handsMaxVerticalRecoil = 1.945;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2.5;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 90;
		m_MouseOffsetRangeMax = 120;
		m_MouseOffsetDistance = 4.45;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.045;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}