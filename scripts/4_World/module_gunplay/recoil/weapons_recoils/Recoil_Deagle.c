modded class DEagleRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.75;
		m_handsMaxHorizontalRecoil = 1.23;
		
		m_handsMinVerticalRecoil = 1.670;
		m_handsMaxVerticalRecoil = 1.978;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2.55;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 70;
		m_MouseOffsetRangeMax = 110;
		m_MouseOffsetDistance = 3.45;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.08;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}