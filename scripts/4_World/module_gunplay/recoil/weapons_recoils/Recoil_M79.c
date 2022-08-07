modded class M79Recoil {
	override void initRecoilParameters() {}

	override void Init() {
		m_handsMinHorizontalRecoil = -1.75;
		m_handsMaxHorizontalRecoil = 1.75;
		
		m_handsMinVerticalRecoil = 2.575;
		m_handsMaxVerticalRecoil = 3.225;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.725;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 90;
		m_MouseOffsetRangeMax = 115;
		m_MouseOffsetDistance = 3.2;
		m_MouseOffsetRelativeTime = 0.0625;
				
		m_CamOffsetDistance = 0.1;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
	
	override float getDampedSin(float time){
		return SMath.DampedSin(0.2, 0.8, 0.9, 0.75, 1, time);
	}
}