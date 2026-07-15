modded class SCARHRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-2.565,  2.665,  8.065,  8.395};
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.730;

		misalignIntensity  = { 1.650,  0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.870;

		mouseRanges        = {-0.215,  0.215,  1.650,  1.955};
		mouseTime          = 0.200;

		kick               = 0.070;
		kickResetTime      = 3.150;
	}
}
