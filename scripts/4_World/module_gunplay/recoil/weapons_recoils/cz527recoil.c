modded class CZ527Recoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -1.12;
		m_handsMaxHorizontalRecoil = 1.24;
		
		m_handsMinVerticalRecoil = 1.55;
		m_handsMaxVerticalRecoil = 1.64;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 1.2;
		
		m_relativeReloadTime = 1.2;
		
		m_MouseOffsetRangeMin = 80;//in degrees min
		m_MouseOffsetRangeMax = 100;//in degrees max
		m_MouseOffsetDistance = 4.5;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.125;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
	
		m_CamOffsetDistance = 0.051;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}