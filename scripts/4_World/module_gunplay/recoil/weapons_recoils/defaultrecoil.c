modded class DefaultRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -0.75;
		m_handsMaxHorizontalRecoil = 1;
		
		m_handsMinVerticalRecoil = 1.775;
		m_handsMaxVerticalRecoil = 2.225;
		m_handsRecoilsteps = 2;
		
		m_MouseOffsetRangeMin = 60;//in degrees min
		m_MouseOffsetRangeMax = 120;//in degrees max
		m_MouseOffsetDistance = 1;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
		
		createHandRecoilPoints();
	}
}