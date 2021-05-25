modded class VSSRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.025;
		m_handsMaxHorizontalRecoil = 0.055;
		
		m_handsMinVerticalRecoil = 0.615;
		m_handsMaxVerticalRecoil = 0.845;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 3;	
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 60;//in degrees min
		m_MouseOffsetRangeMax = 100;//in degrees max
		m_MouseOffsetDistance = 2.2;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.2;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
		
		m_CamOffsetDistance = 0.02;
		m_CamOffsetRelativeTime = 1;
		
		createHandRecoilPoints();
	}
}