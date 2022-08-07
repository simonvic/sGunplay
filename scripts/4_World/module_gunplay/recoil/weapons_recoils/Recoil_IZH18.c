modded class Izh18Recoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 3.285,  5.275,  6.050};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.550;

		misalignIntensity  = {0.200, 0.200};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.550;
	
		mouseRanges        = { 0.175, 0.250,  1.550,  2.275};
		mouseTime          = 0.200;
	
		kick               = 0.035;
		kickResetTime      = 3.125;
	}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -1.15;
		m_handsMaxHorizontalRecoil = 1.28;
		
		m_handsMinVerticalRecoil = 1.58;
		m_handsMaxVerticalRecoil = 1.69;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.75;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 4.2;
		m_MouseOffsetRelativeTime = 0.0925;
	
		m_CamOffsetDistance = 0.055;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
}