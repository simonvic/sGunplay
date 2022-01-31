modded class RepeaterRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -1.45;
		m_handsMaxHorizontalRecoil = 1.56;
		
		m_handsMinVerticalRecoil = 1.65;
		m_handsMaxVerticalRecoil = 1.82;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.5;	
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 4.6;
		m_MouseOffsetRelativeTime = 0.0625;
			
		m_CamOffsetDistance = 0.08;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
}