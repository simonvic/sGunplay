modded class CZ527Recoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -1.12;
		m_handsMaxHorizontalRecoil = 1.24;
		
		m_handsMinVerticalRecoil = 1.55;
		m_handsMaxVerticalRecoil = 1.64;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 1.2;
		
		m_relativeReloadTime = 1.2;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 4.5;
		m_MouseOffsetRelativeTime = 0.125;
	
		m_CamOffsetDistance = 0.051;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}