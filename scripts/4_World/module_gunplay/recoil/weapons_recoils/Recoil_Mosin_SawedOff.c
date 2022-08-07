modded class MosinSawedOffRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.265, 3.585,  9.265,  10.295};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.500;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.550,  2.275};
		mouseTime          = 0.200;
	
		kick               = 0.075;
		kickResetTime      = 3.550;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.32;
		m_handsMaxHorizontalRecoil = 1.44;
		
		m_handsMinVerticalRecoil = 2.65;
		m_handsMaxVerticalRecoil = 2.74;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.625;	
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 4.75;
		m_MouseOffsetRelativeTime = 0.0625;
	
		m_CamOffsetDistance = 0.051;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
}