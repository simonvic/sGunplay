modded class Ak101Recoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.105;
		m_handsMaxHorizontalRecoil = 0.142;
				
		m_handsMinVerticalRecoil = 1.290;
		m_handsMaxVerticalRecoil = 1.242;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 75;//in degrees min
		m_MouseOffsetRangeMax = 115;//in degrees max
		m_MouseOffsetDistance = 3.15;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.2;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
	
		m_CamOffsetDistance = 0.029;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}