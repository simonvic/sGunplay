modded class ScoutRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-2.565,  2.585,  8.550,  9.250};
		handsAccumSpeed    = 0.980;
		handsResetSpeed    = 0.720;

		misalignIntensity  = { 1.750,  0.400};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.870;
	
		mouseRanges        = {-0.215,  0.215,  1.750,  2.575};
		mouseTime          = 0.200;
	
		kick               = 0.085;
		kickResetTime      = 3.150;
	}
}