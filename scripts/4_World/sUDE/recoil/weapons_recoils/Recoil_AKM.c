modded class AkmRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.500, 2.075,  2.750,  3.985};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.550;
		
		misalignIntensity  = {0.550, 0.750};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.550;
	
		mouseRanges        = { 0.175, 0.250,  2.250,  2.750};
		mouseTime          = 0.200;
	
		kick               = 0.074;
		kickResetTime      = 2.250;
	}
}