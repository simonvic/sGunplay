modded class Izh18Recoil {
	override void initRecoilParameters() {}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -1.15;
		m_handsMaxHorizontalRecoil = 1.28;
		
		m_handsMinVerticalRecoil = 1.58;
		m_handsMaxVerticalRecoil = 1.69;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.75;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 4.2;
		m_MouseOffsetRelativeTime = 0.0925;
	
		m_CamOffsetDistance = 0.055;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
}