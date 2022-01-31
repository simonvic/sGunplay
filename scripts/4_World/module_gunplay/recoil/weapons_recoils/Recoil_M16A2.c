modded class M16A2Recoil{

	override void Init(){
		m_handsMinHorizontalRecoil = -0.085;
		m_handsMaxHorizontalRecoil = 0.115;
				
		m_handsMinVerticalRecoil = 0.710;
		m_handsMaxVerticalRecoil = 0.820;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 75;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 3.1;
		m_MouseOffsetRelativeTime = 0.2;
	
		m_CamOffsetDistance = 0.017;
		m_CamOffsetRelativeTime = 0.5;
		
		createHandRecoilPoints();
	}
	
}