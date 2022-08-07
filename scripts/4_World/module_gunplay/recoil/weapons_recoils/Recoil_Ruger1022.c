modded class Ruger1022Recoil {
	override void initRecoilParameters() {
		handsRanges        = { -0.165, 0.285,  0.775, 1.100};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.550;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.575};
		mouseTime          = 0.100;
	
		kick               = 0.025;
		kickResetTime      = 1.150;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.020;
		m_handsMaxHorizontalRecoil = 0.045;
		
		m_handsMinVerticalRecoil = 0.255;
		m_handsMaxVerticalRecoil = 0.285;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 45;
		m_MouseOffsetRangeMax = 80;
		m_MouseOffsetDistance = 1.55;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.019;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}