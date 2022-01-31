modded class Mp5kRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.015;
		m_handsMaxHorizontalRecoil = 0.025;
		
		m_handsMinVerticalRecoil = 0.425;
		m_handsMaxVerticalRecoil = 0.785;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 60;
		m_MouseOffsetRangeMax = 120;
		m_MouseOffsetDistance = 2.85;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.025;
		m_CamOffsetRelativeTime = 0.95;
		
		createHandRecoilPoints();
	}
}