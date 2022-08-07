modded class MakarovRecoil {
	override void initRecoilParameters() {}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -0.075;
		m_handsMaxHorizontalRecoil = 0.15;
		
		m_handsMinVerticalRecoil = 0.568;
		m_handsMaxVerticalRecoil = 0.697;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 70;
		m_MouseOffsetRangeMax = 110;
		m_MouseOffsetDistance = 1.25;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.030;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}