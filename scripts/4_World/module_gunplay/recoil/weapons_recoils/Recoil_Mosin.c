modded class MosinRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 3.285,  7.265,  8.295};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.500;

		misalignIntensity  = {0.05, 0.05};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.200;
	
		kick               = 0.074;
		kickResetTime      = 2.250;
	}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.52;
		m_handsMaxHorizontalRecoil = 0.94;
		
		m_handsMinVerticalRecoil = 1.65;
		m_handsMaxVerticalRecoil = 1.74;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.625;	
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 4.65;
		m_MouseOffsetRelativeTime = 0.0425;
			
		m_CamOffsetDistance = 0.051;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
	
	override float getDampedSin(float time){
		return SMath.DampedSin(0.2, 0.8, 0.9, 1.4, 1, time) + 0.051;
	}
}