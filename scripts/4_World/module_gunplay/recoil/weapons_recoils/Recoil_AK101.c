modded class Ak101Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.065, 0.085,  1.265,  1.495};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.550;
		
		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.550;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.200;
	
		kick               = 0.054;
		kickResetTime      = 2.250;
	}
}