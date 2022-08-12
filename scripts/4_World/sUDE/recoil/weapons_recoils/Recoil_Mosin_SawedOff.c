modded class MosinSawedOffRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.265, 3.585,  9.265,  10.295};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.500;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.550,  2.275};
		mouseTime          = 0.200;
	
		kick               = 0.075;
		kickResetTime      = 3.550;
	}
}