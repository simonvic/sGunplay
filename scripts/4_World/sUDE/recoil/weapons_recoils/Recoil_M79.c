modded class M79Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.165,  3.285,  6.755,  7.255};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.700;

		misalignIntensity  = { 0.250,  0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = {-0.215,  0.215,  1.750,  2.775};
		mouseTime          = 0.200;
	
		kick               = 0.045;
		kickResetTime      = 3.250;
	}
}