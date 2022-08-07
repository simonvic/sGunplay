modded class RepeaterRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 3.285,  5.275,  6.050};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.550;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.550,  2.275};
		mouseTime          = 0.200;
	
		kick               = 0.045;
		kickResetTime      = 3.250;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -1.45;
		m_handsMaxHorizontalRecoil = 1.56;
		
		m_handsMinVerticalRecoil = 1.65;
		m_handsMaxVerticalRecoil = 1.82;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.5;	
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 4.6;
		m_MouseOffsetRelativeTime = 0.0625;
			
		m_CamOffsetDistance = 0.08;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
}