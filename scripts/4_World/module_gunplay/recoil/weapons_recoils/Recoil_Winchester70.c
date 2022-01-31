modded class Winchester70Recoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -1.52;
		m_handsMaxHorizontalRecoil = 1.34;
		
		m_handsMinVerticalRecoil = 1.85;
		m_handsMaxVerticalRecoil = 1.94;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 1.525;
		
		m_relativeReloadTime = 2;
		
		m_MouseOffsetRangeMin = 80;//in degrees min
		m_MouseOffsetRangeMax = 100;//in degrees max
		m_MouseOffsetDistance = 5.65;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.0325;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
	
		m_CamOffsetDistance = 0.073;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
}