modded class Ak101Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.500, 2.075,  2.750,  3.985};	
		handsAccumSpeed    = 0.900;
		handsResetSpeed    = 0.650;
		
		misalignIntensity  = {0.750, 0.750};
		misalignAccumSpeed = 0.900;
		misalignResetSpeed = 0.650;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.047;
		kickResetTime      = 2.250;
	}
}