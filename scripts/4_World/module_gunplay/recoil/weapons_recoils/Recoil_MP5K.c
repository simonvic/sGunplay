modded class Mp5kRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.050, 2.250,  2.450 ,  3.785};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.550;
		
		misalignIntensity  = {0.250, 0.125};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.600;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.075;
		kickResetTime      = 1.450;
	}
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.015;
		m_handsMaxHorizontalRecoil = 0.025;
		
		m_handsMinVerticalRecoil = 0.425;
		m_handsMaxVerticalRecoil = 0.785;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 60;
		m_MouseOffsetRangeMax = 120;
		m_MouseOffsetDistance = 2.85;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.025;
		m_CamOffsetRelativeTime = 0.95;
		
		createHandRecoilPoints();
	}
}