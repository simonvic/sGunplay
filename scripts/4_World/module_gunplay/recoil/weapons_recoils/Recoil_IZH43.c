modded class Izh43Recoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 3.285,  7.765,  9.295};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.500;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.750,  2.775};
		mouseTime          = 0.200;
	
		kick               = 0.045;
		kickResetTime      = 3.250;
	}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -1.75;
		m_handsMaxHorizontalRecoil = 1.75;
		
		m_handsMinVerticalRecoil = 2.575;
		m_handsMaxVerticalRecoil = 3.225;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.725;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 70;
		m_MouseOffsetRangeMax = 110;
		m_MouseOffsetDistance = 5.95;
		m_MouseOffsetRelativeTime = 0.0525; //0.03;
				
		m_CamOffsetDistance = 0.1;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
}