modded class GlockRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.1;
		m_handsMaxHorizontalRecoil = 0.120;
		
		m_handsMinVerticalRecoil = 0.440;
		m_handsMaxVerticalRecoil = 0.560;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 55;
		m_MouseOffsetRangeMax = 90;
		m_MouseOffsetDistance = 2.7;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.02;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}