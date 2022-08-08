modded class Ruger1022Recoil {
	override void initRecoilParameters() {
		handsRanges        = { -0.165, 0.285,  0.775, 1.100};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.550;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.575};
		mouseTime          = 0.100;
	
		kick               = 0.025;
		kickResetTime      = 1.150;
	}
}