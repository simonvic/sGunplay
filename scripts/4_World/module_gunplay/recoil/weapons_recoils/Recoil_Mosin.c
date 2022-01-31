modded class MosinRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.52;
		m_handsMaxHorizontalRecoil = 0.94;
		
		m_handsMinVerticalRecoil = 1.65;
		m_handsMaxVerticalRecoil = 1.74;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.625;	
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 80;
		m_MouseOffsetRangeMax = 100;
		m_MouseOffsetDistance = 4.65;
		m_MouseOffsetRelativeTime = 0.0425;
			
		m_CamOffsetDistance = 0.051;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
	
	override float getDampedSin(float time){
		return SMath.DampedSin(0.2, 0.8, 0.9, 1.4, 1, time) + 0.051;
	}
}