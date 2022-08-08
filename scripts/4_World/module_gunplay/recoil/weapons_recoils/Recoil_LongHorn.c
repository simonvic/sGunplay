modded class LongHornRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 3.285,  7.265,  8.295};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.500;

		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.650;
	
		mouseRanges        = { 0.175, 0.250,  1.550,  2.275};
		mouseTime          = 0.200;
	
		kick               = 0.080;
		kickResetTime      = 2.250;
	}
}