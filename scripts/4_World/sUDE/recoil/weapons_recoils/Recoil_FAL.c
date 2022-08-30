modded class FALRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 2.285,  7.565,  8.795};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.750;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.925;
		misalignResetSpeed = 0.850;
	
		mouseRanges        = { 0.175, 0.250,  1.750,  2.575};
		mouseTime          = 0.200;
	
		kick               = 0.085;
		kickResetTime      = 3.150;
	}
}