modded class P1Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.750, 1.250,  4.050,  5.200};	
		handsAccumSpeed    = 0.925;
		handsResetSpeed    = 0.750;
		
		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
		
		mouseRanges        = { -0.575, 0.700,  0.550,  1.050};
		mouseTime          = 0.050;
	
		kick               = 0.045;
		kickResetTime      = 1.250;
	}
}