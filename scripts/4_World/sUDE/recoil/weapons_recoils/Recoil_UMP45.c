modded class Ump45Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.700, 0.700,  2.450,  3.785};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.650;
		
		misalignIntensity  = {0.250, 0.125};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.600;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.065;
		kickResetTime      = 1.450;
	}
}