modded class DEagleRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.75;
		m_handsMaxHorizontalRecoil = 1.23;
		
		m_handsMinVerticalRecoil = 1.670;
		m_handsMaxVerticalRecoil = 1.978;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2.55;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 70;//in degrees min
		m_MouseOffsetRangeMax = 110;//in degrees max
		m_MouseOffsetDistance = 3.45;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.2;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
	
		m_CamOffsetDistance = 0.08;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}