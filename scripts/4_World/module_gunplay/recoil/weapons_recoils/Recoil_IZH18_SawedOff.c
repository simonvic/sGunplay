modded class Izh18SawedOffRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.765, 3.585,  8.765,  10.295};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.500;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  3.750,  3.775};
		mouseTime          = 0.200;
	
		kick               = 0.065;
		kickResetTime      = 3.550;
	}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -1.25;
		m_handsMaxHorizontalRecoil = 1.38;
		
		m_handsMinVerticalRecoil = 1.59;
		m_handsMaxVerticalRecoil = 1.70;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.75;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 4.3;
		m_MouseOffsetRelativeTime = 0.0925;
	
		m_CamOffsetDistance = 0.055;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
}