modded class FALRecoil {
	override void initRecoilParameters() {}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -0.05;
		m_handsMaxHorizontalRecoil = 0.08;
		
		m_handsMinVerticalRecoil = 1.3225;
		m_handsMaxVerticalRecoil = 1.36;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 1.8;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 65;
		m_MouseOffsetRangeMax = 140;
		m_MouseOffsetDistance = 4.15;
		m_MouseOffsetRelativeTime = 0.25;
	
		m_CamOffsetDistance = 0.045;
		m_CamOffsetRelativeTime = 0.85;	
		
		createHandRecoilPoints();
	}
}