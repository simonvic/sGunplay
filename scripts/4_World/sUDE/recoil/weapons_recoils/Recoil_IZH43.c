modded class Izh43Recoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 3.285,  7.765,  9.295};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.700;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.750,  2.775};
		mouseTime          = 0.075;
	
		kick               = 0.045;
		kickResetTime      = 3.250;
	}
}