modded class ScoutRecoil {
	override void initRecoilParameters() {}

	override void Init() {
		m_handsMinHorizontalRecoil = -0.08;
		m_handsMaxHorizontalRecoil = 0.105;
				
		m_handsMinVerticalRecoil = 1.235;
		m_handsMaxVerticalRecoil = 1.350;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.3;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 100;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 4.1;
		m_MouseOffsetRelativeTime = 0.01;
	
		m_CamOffsetDistance = 0.047;
		m_CamOffsetRelativeTime = 0.65;
		
		createHandRecoilPoints();
	}
}