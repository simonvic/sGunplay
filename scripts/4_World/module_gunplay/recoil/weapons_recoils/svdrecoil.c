modded class SvdRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.82;
		m_handsMaxHorizontalRecoil = 0.64;
		
		m_handsMinVerticalRecoil = 2.15;
		m_handsMaxVerticalRecoil = 2.24;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 3.5;
		
		m_relativeReloadTime = 3.5;
		
		m_MouseOffsetRangeMin = 45;//in degrees min
		m_MouseOffsetRangeMax = 110;//in degrees max
		m_MouseOffsetDistance = 5.95;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.2;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
	
		m_CamOffsetDistance = 0.065;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}