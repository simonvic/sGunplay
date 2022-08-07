modded class VSSRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -0.165, 0.585,  2.275,  3.050};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.550;

		misalignIntensity  = {0.125, 0.125};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.650;
	
		mouseRanges        = { 0.175, 0.250,  1.550,  2.275};
		mouseTime          = 0.200;
	
		kick               = 0.030;
		kickResetTime      = 2.250;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.025;
		m_handsMaxHorizontalRecoil = 0.055;
		
		m_handsMinVerticalRecoil = 0.615;
		m_handsMaxVerticalRecoil = 0.845;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 3;	
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 70;
		m_MouseOffsetRangeMax = 90;
		m_MouseOffsetDistance = 1.9;
		m_MouseOffsetRelativeTime = 0.2;
		
		m_CamOffsetDistance = 0.012;
		m_CamOffsetRelativeTime = 0.95;
		
		createHandRecoilPoints();
	}
}