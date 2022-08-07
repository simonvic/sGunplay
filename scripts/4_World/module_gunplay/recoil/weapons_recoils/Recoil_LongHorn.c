modded class LongHornRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 3.285,  7.265,  8.295};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.500;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.650;
	
		mouseRanges        = { 0.175, 0.250,  1.550,  2.275};
		mouseTime          = 0.200;
	
		kick               = 0.080;
		kickResetTime      = 2.250;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.70;
		m_handsMaxHorizontalRecoil = 1.10;
		
		m_handsMinVerticalRecoil = 1.685;
		m_handsMaxVerticalRecoil = 2.000;
		m_handsRecoilsteps = 1;
		
		m_HandsOffsetRelativeTime = 1.0;
		
		m_relativeReloadTime = 1.5;
		
		m_MouseOffsetRangeMin = 70;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 3.25;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.085;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}