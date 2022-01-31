modded class Cz61Recoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.060;
		m_handsMaxHorizontalRecoil = 0.075;
		
		m_handsMinVerticalRecoil = 0.255;
		m_handsMaxVerticalRecoil = 0.385;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 1.5;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 1.35;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.035;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}