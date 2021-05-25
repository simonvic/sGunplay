modded class SKSRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.735;
		m_handsMaxHorizontalRecoil = 0.165;
		
		m_handsMinVerticalRecoil = 1.715;
		m_handsMaxVerticalRecoil = 1.945;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2.5;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 90;//in degrees min
		m_MouseOffsetRangeMax = 120;//in degrees max
		m_MouseOffsetDistance = 4.45;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.2;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
	
		m_CamOffsetDistance = 0.045;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}