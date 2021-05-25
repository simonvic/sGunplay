modded class B95Recoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -1.32;
		m_handsMaxHorizontalRecoil = 1.44;
		
		m_handsMinVerticalRecoil = 1.55;
		m_handsMaxVerticalRecoil = 1.74;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 3.5;
		
		m_relativeReloadTime = 3.5;
		
		m_MouseOffsetRangeMin = 80;//in degrees min
		m_MouseOffsetRangeMax = 100;//in degrees max
		m_MouseOffsetDistance = 4.7;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.225;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
	
		m_CamOffsetDistance = 0.052;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}