modded class Ruger1022Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.055,  1.055,  3.775,  4.100};	
		handsAccumSpeed    = 0.970;
		handsResetSpeed    = 0.800;

		misalignIntensity  = { 1.250,  0.400};
		misalignAccumSpeed = 0.950;
		misalignResetSpeed = 0.750;
	
		mouseRanges        = {-0.200,  0.200,  0.550,  0.675};
		mouseTime          = 0.100;
	
		kick               = 0.035;
		kickResetTime      = 1.150;
	}
}