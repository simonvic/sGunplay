modded class DerringerRecoil {
	override void initRecoilParameters() {}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -0.10;
		m_handsMaxHorizontalRecoil = 0.25;
		
		m_handsMinVerticalRecoil = 2.035;
		m_handsMaxVerticalRecoil = 2.717;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2.8;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 60;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 3.4;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.08;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
	
}