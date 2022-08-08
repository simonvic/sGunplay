modded class Izh18Recoil {
	override void initRecoilParameters() {
		handsRanges        = { -1.165, 3.285,  5.275,  6.050};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.550;

		misalignIntensity  = {0.200, 0.200};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.550;
	
		mouseRanges        = { 0.175, 0.250,  1.550,  2.275};
		mouseTime          = 0.200;
	
		kick               = 0.035;
		kickResetTime      = 3.125;
	}
}