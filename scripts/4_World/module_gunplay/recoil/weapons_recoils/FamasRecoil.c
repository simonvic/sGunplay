//dummy ifdef so the workbench won't complain
#ifdef S_FRAMEWORK
modded class FamasRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.08;
		m_handsMaxHorizontalRecoil = 0.105;
				
		m_handsMinVerticalRecoil = 0.755;
		m_handsMaxVerticalRecoil = 0.985;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 75;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 2.8;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.023;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}
#endif