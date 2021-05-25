modded class Mp5kRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.050;
		m_handsMaxHorizontalRecoil = 0.065;
		
		m_handsMinVerticalRecoil = 0.725;
		m_handsMaxVerticalRecoil = 1.085;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 60;//in degrees min
		m_MouseOffsetRangeMax = 120;//in degrees max
		m_MouseOffsetDistance = 2.85;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.2;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
	
		m_CamOffsetDistance = 0.020;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}