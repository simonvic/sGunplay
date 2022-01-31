modded class MkiiRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.05;
		m_handsMaxHorizontalRecoil = 0.08;
		
		m_handsMinVerticalRecoil = 0.245;
		m_handsMaxVerticalRecoil = 0.365;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 45;//in degrees min
		m_MouseOffsetRangeMax = 80;//in degrees max
		m_MouseOffsetDistance = 0.75;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.2;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
	
		m_CamOffsetDistance = 0.038;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}