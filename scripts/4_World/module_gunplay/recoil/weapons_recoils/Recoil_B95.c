modded class B95Recoil {
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
		m_handsMinHorizontalRecoil = -1.32;
		m_handsMaxHorizontalRecoil = 1.44;
		
		m_handsMinVerticalRecoil = 1.55;
		m_handsMaxVerticalRecoil = 1.74;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 3.5;
		
		m_relativeReloadTime = 3.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 4.7;
		m_MouseOffsetRelativeTime = 0.225;
	
		m_CamOffsetDistance = 0.052;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}