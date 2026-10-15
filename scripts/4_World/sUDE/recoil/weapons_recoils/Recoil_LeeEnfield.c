modded class LeeEnfieldRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-2.560,  2.560,  8.600,  9.200};
		handsAccumSpeed    = 0.980;
		handsResetSpeed    = 0.720;

		misalignIntensity  = { 1.720,  0.450};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.870;

		mouseRanges        = {-0.215,  0.215,  1.700,  2.520};
		mouseTime          = 0.200;

		kick               = 0.085;
		kickResetTime      = 3.150;
	}
}
