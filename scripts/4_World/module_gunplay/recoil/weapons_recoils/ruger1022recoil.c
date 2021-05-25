modded class Ruger1022Recoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.020;
		m_handsMaxHorizontalRecoil = 0.045;
		
		m_handsMinVerticalRecoil = 0.255;
		m_handsMaxVerticalRecoil = 0.285;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 45;//in degrees min
		m_MouseOffsetRangeMax = 80;//in degrees max
		m_MouseOffsetDistance = 1.55;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.2;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
	
		m_CamOffsetDistance = 0.019;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}