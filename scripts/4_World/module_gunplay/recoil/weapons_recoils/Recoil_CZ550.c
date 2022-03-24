modded class CZ550Recoil {
	
	override void Init(){
		m_handsMinHorizontalRecoil = -1.60;
		m_handsMaxHorizontalRecoil = 1.4;
		
		m_handsMinVerticalRecoil = 1.9;
		m_handsMaxVerticalRecoil = 2.0;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 1.010;
		
		m_relativeReloadTime = 2;
		
		m_MouseOffsetRangeMin = 90;
		m_MouseOffsetRangeMax = 95;
		m_MouseOffsetDistance = 5.85;
		m_MouseOffsetRelativeTime = 0.0325;
	
		m_CamOffsetDistance = 0.080;
		m_CamOffsetRelativeTime = 0.255;
		
		createHandRecoilPoints();
	}
}