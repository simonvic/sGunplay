#ifdef DAYZ_1_21
modded class CrossbowRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -0.575, 0.575,  1.755,  2.255};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.500;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  0.750,  1.000};
		mouseTime          = 0.200;
	
		kick               = 0.025;
		kickResetTime      = 3.250;
	}
}
#endif