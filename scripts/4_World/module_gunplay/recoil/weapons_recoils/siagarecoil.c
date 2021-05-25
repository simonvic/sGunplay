modded class SiagaRecoil{
	
	override void Init(){
		m_handsMinHorizontalRecoil = -1.35;
		m_handsMaxHorizontalRecoil = 1.45;
		
		m_handsMinVerticalRecoil = 3.475;
		m_handsMaxVerticalRecoil = 4.355;
		m_handsRecoilsteps = 2;
		
		m_HandsOffsetRelativeTime = 2.125;
		
		m_relativeReloadTime = 2.5;
		
		m_MouseOffsetRangeMin = 45;//in degrees min
		m_MouseOffsetRangeMax = 130;//in degrees max
		m_MouseOffsetDistance = 5.9;//how far should the mouse travel
		m_MouseOffsetRelativeTime = 0.15;//[0..1] a time it takes to move the mouse the required distance relative to the reload time of the weapon(firing mode)
	
		m_CamOffsetDistance = 0.085;
		m_CamOffsetRelativeTime = 0.5;
		
		createHandRecoilPoints();
	}
}