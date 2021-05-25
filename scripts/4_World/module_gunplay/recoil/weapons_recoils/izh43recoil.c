modded class Izh43Recoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -1.75;
		m_handsMaxHorizontalRecoil = 1.75;
		
		m_handsMinVerticalRecoil = 2.775;
		m_handsMaxVerticalRecoil = 3.225;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 0.725;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 70;//in degrees min
		m_MouseOffsetRangeMax = 110;//in degrees max
		m_MouseOffsetDistance = 5.95;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.0525; //0.03;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
				
		m_CamOffsetDistance = 0.1;
		m_CamOffsetRelativeTime = 0.125;
		
		createHandRecoilPoints();
	}
}