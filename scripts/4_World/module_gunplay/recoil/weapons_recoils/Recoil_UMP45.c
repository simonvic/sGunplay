modded class Ump45Recoil {
	override void initRecoilParameters() {}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.060;
		m_handsMaxHorizontalRecoil = 0.075;
		
		m_handsMinVerticalRecoil = 0.475;
		m_handsMaxVerticalRecoil = 0.795;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 88;
		m_MouseOffsetRangeMax = 105;
		m_MouseOffsetDistance = 2.28;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.020;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}