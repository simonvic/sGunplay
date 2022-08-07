modded class Winchester70Recoil {
	override void initRecoilParameters() {}

	override void Init() {
		m_handsMinHorizontalRecoil = -1.52;
		m_handsMaxHorizontalRecoil = 1.34;
		
		m_handsMinVerticalRecoil = 1.85;
		m_handsMaxVerticalRecoil = 1.94;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 1.525;
		
		m_relativeReloadTime = 2;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 5.65;
		m_MouseOffsetRelativeTime = 0.0325;
	
		m_CamOffsetDistance = 0.073;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
}