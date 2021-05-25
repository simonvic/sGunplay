modded class MagnumRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.15;
		m_handsMaxHorizontalRecoil = 0.30;
		
		m_handsMinVerticalRecoil = 2.335;
		m_handsMaxVerticalRecoil = 2.817;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2.8;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 60;//in degrees min
		m_MouseOffsetRangeMax = 100;//in degrees max
		m_MouseOffsetDistance = 3.4;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.2;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
	
		m_CamOffsetDistance = 0.08;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}