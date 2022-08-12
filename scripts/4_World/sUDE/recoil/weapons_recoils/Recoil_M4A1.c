modded class M4a1Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.050, 2.250,  2.750 ,  3.985};	
		handsAccumSpeed    = 0.950;
		handsResetSpeed    = 0.400;
		
		misalignIntensity  = {0.750, 0.750};
		misalignAccumSpeed = 0.905;
		misalignResetSpeed = 0.750;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.045;
		kickResetTime      = 2.250;
	}
}