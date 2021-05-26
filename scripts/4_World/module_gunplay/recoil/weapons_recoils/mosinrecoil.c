modded class MosinRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.52;
		m_handsMaxHorizontalRecoil = 0.94;
		
		m_handsMinVerticalRecoil = 2.55;
		m_handsMaxVerticalRecoil = 2.64;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.625;	
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 80;//in degrees min
		m_MouseOffsetRangeMax = 100;//in degrees max
		m_MouseOffsetDistance = 4.65;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.0425;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
			
		m_CamOffsetDistance = 0.051;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
	
	override float getDampedSin(float time){
		return SMath.DampedSin(0.2, 0.8, 0.9, 1.4, 1, time) + 0.051;
	}
}