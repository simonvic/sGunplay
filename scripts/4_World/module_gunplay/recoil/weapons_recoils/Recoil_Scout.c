modded class ScoutRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 3.285,  5.865,  6.995};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.500;

		misalignIntensity  = {0.200, 0.200};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.550,  2.275};
		mouseTime          = 0.200;
	
		kick               = 0.045;
		kickResetTime      = 3.250;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.08;
		m_handsMaxHorizontalRecoil = 0.105;
				
		m_handsMinVerticalRecoil = 1.235;
		m_handsMaxVerticalRecoil = 1.350;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.3;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 100;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 4.1;
		m_MouseOffsetRelativeTime = 0.01;
	
		m_CamOffsetDistance = 0.047;
		m_CamOffsetRelativeTime = 0.65;
		
		createHandRecoilPoints();
	}
}