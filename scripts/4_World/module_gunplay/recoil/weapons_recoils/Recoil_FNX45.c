modded class Fnx45Recoil {
	override void initRecoilParameters() {}
	
	override void Init() {
		m_handsMinHorizontalRecoil = -0.1;
		m_handsMaxHorizontalRecoil = 0.125;
		
		m_handsMinVerticalRecoil = 0.570;
		m_handsMaxVerticalRecoil = 0.878;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 3;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 45;
		m_MouseOffsetRangeMax = 105;
		m_MouseOffsetDistance = 2.82;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.021;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}