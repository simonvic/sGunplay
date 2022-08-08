modded class VSSRecoil {
	override void initRecoilParameters() {
		handsRanges        = { -0.165, 0.585,  2.275,  3.050};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.550;

		misalignIntensity  = {0.125, 0.125};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.650;
	
		mouseRanges        = { 0.175, 0.250,  1.550,  2.275};
		mouseTime          = 0.200;
	
		kick               = 0.030;
		kickResetTime      = 2.250;
	}
}