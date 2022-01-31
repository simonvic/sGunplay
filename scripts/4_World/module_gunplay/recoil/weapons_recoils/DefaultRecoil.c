modded class DefaultRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.75;
		m_handsMaxHorizontalRecoil = 1;
		
		m_handsMinVerticalRecoil = 1.775;
		m_handsMaxVerticalRecoil = 2.225;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;

		m_MouseOffsetRangeMin = 60;
		m_MouseOffsetRangeMax = 120;
		m_MouseOffsetDistance = 1;
		m_MouseOffsetRelativeTime = 0;
		
		m_CamOffsetDistance = 0.0265;
		m_CamOffsetRelativeTime = 1;

		createHandRecoilPoints();
	}
}