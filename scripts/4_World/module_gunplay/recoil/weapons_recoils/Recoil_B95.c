modded class B95Recoil {
	override void initRecoilParameters() {}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -1.32;
		m_handsMaxHorizontalRecoil = 1.44;
		
		m_handsMinVerticalRecoil = 1.55;
		m_handsMaxVerticalRecoil = 1.74;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 3.5;
		
		m_relativeReloadTime = 3.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 4.7;
		m_MouseOffsetRelativeTime = 0.225;
	
		m_CamOffsetDistance = 0.052;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}