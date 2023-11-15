modded class VSSRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.950,  0.950,  2.750,  3.575};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.720;
		
		misalignIntensity  = { 1.750,  0.225};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.850;
	
		mouseRanges        = {-0.215,  0.215,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.055;
		kickResetTime      = 2.250;
	}
}