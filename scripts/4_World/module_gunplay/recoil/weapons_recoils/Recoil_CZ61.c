modded class Cz61Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.750, 1.050,  1.350 ,  1.985};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.550;
		
		misalignIntensity  = {0.125, 0.125};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.600;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.025;
		kickResetTime      = 1.450;
	}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -0.060;
		m_handsMaxHorizontalRecoil = 0.075;
		
		m_handsMinVerticalRecoil = 0.255;
		m_handsMaxVerticalRecoil = 0.385;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 1.5;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 1.35;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.035;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}