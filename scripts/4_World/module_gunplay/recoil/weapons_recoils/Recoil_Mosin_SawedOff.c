modded class MosinSawedOffRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.32;
		m_handsMaxHorizontalRecoil = 1.44;
		
		m_handsMinVerticalRecoil = 2.65;
		m_handsMaxVerticalRecoil = 2.74;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.625;	
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 4.75;
		m_MouseOffsetRelativeTime = 0.0625;
	
		m_CamOffsetDistance = 0.051;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
}