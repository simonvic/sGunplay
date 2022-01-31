modded class SiagaRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -1.35;
		m_handsMaxHorizontalRecoil = 1.45;
		
		m_handsMinVerticalRecoil = 3.275;
		m_handsMaxVerticalRecoil = 3.955;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2.125;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 45;
		m_MouseOffsetRangeMax = 130;
		m_MouseOffsetDistance = 5.9;
		m_MouseOffsetRelativeTime = 0.15;
	
		m_CamOffsetDistance = 0.085;
		m_CamOffsetRelativeTime = 0.75;
		
		createHandRecoilPoints();
	}
}