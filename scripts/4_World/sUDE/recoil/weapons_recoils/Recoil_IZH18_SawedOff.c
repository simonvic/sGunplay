modded class Izh18SawedOffRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.765, 3.585,  8.765,  10.295};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.500;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  3.750,  3.775};
		mouseTime          = 0.200;
	
		kick               = 0.065;
		kickResetTime      = 3.550;
	}
}