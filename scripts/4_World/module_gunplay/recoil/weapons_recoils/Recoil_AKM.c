modded class AkmRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.765, 1.085,  1.765,  2.595};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.550;
		
		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.550;
	
		mouseRanges        = { 0.175, 0.250,  2.250,  2.750};
		mouseTime          = 0.200;
	
		kick               = 0.074;
		kickResetTime      = 2.250;
	}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -0.075;
		m_handsMaxHorizontalRecoil = 0.1;
		
		m_handsMinVerticalRecoil = 1.2275;
		m_handsMaxVerticalRecoil = 1.3725;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 85;
		m_MouseOffsetRangeMax = 120;
		m_MouseOffsetDistance = 3.55;
		m_MouseOffsetRelativeTime = 0.2;
		
		m_CamOffsetDistance = 0.0355;
		m_CamOffsetRelativeTime = 0.9;
		
		createHandRecoilPoints();
	}
		
}