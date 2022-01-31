modded class Ak101Recoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.105;
		m_handsMaxHorizontalRecoil = 0.142;
				
		m_handsMinVerticalRecoil = 1.290;
		m_handsMaxVerticalRecoil = 1.242;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 75;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 3.5;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.032;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}