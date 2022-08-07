modded class DEagleRecoil{
	override void initRecoilParameters() {
		handsRanges        = {-1.750, 2.550,  6.250,  8.300};	
		handsAccumSpeed    = 0.985;
		handsResetSpeed    = 0.550;
		
		misalignIntensity  = {0.525, 0.525};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.550;
		
		mouseRanges        = { 0.775, 1.150,  1.250,  1.750};
		mouseTime          = 0.300;
	
		kick               = 0.080;
		kickResetTime      = 2.250;
	}

	override void Init(){
		m_handsMinHorizontalRecoil = -0.75;
		m_handsMaxHorizontalRecoil = 1.23;
		
		m_handsMinVerticalRecoil = 1.670;
		m_handsMaxVerticalRecoil = 1.978;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2.55;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 70;
		m_MouseOffsetRangeMax = 110;
		m_MouseOffsetDistance = 3.45;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.08;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}