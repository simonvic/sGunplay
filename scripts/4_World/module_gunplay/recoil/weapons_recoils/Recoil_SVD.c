modded class SvdRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.82;
		m_handsMaxHorizontalRecoil = 0.64;
		
		m_handsMinVerticalRecoil = 1.15;
		m_handsMaxVerticalRecoil = 1.24;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 3.5;
		
		m_relativeReloadTime = 3.5;
		
		m_MouseOffsetRangeMin = 45;
		m_MouseOffsetRangeMax = 110;
		m_MouseOffsetDistance = 5.95;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.065;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}