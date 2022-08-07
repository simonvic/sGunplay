modded class Ak74Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.065, 0.085,  1.265,  1.495};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.550;
		misalignIntensity  = 0.250;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseResetTime     = 0.2;
	
		kick               = 0.054;
		kickResetTime      = 2.25;
	}
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.065;
		m_handsMaxHorizontalRecoil = 0.085;
				
		m_handsMinVerticalRecoil = 1.265;
		m_handsMaxVerticalRecoil = 1.295;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 70;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 3.4;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.0265;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}