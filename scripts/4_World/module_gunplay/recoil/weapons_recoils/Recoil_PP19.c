modded class PP19Recoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.080;
		m_handsMaxHorizontalRecoil = 0.085;
		
		m_handsMinVerticalRecoil = 0.365;
		m_handsMaxVerticalRecoil = 0.495;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 1.5;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 95;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 1.5;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.035;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}