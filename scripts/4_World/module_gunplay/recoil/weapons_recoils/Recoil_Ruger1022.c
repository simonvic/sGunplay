modded class Ruger1022Recoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.020;
		m_handsMaxHorizontalRecoil = 0.045;
		
		m_handsMinVerticalRecoil = 0.255;
		m_handsMaxVerticalRecoil = 0.285;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 45;
		m_MouseOffsetRangeMax = 80;
		m_MouseOffsetDistance = 1.55;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.019;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}