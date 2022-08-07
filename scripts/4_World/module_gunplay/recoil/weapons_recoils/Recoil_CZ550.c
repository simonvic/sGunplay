modded class CZ550Recoil {
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
		kickResetTime      = 3.250;
	}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -1.60;
		m_handsMaxHorizontalRecoil = 1.4;
		
		m_handsMinVerticalRecoil = 1.9;
		m_handsMaxVerticalRecoil = 2.0;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 1.010;
		
		m_relativeReloadTime = 2;
		
		m_MouseOffsetRangeMin = 90;
		m_MouseOffsetRangeMax = 95;
		m_MouseOffsetDistance = 5.85;
		m_MouseOffsetRelativeTime = 0.0325;
	
		m_CamOffsetDistance = 0.080;
		m_CamOffsetRelativeTime = 0.255;
		
		createHandRecoilPoints();
	}
}