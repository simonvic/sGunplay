modded class M16A2Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.250, 0.550,  2.750,  3.985};	
		handsAccumSpeed    = 0.920;
		handsResetSpeed    = 0.700;
		
		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.750;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.015;
		kickResetTime      = 2.250;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.085;
		m_handsMaxHorizontalRecoil = 0.115;
				
		m_handsMinVerticalRecoil = 0.710;
		m_handsMaxVerticalRecoil = 0.820;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 75;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 3.1;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.017;
		m_CamOffsetRelativeTime = 0.5;
		
		createHandRecoilPoints();
	}
	
}