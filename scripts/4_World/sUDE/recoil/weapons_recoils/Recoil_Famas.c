modded class FamasRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.550, 1.550,  2.750,  3.985};	
		handsAccumSpeed    = 0.920;
		handsResetSpeed    = 0.800;
		
		misalignIntensity  = {0.750, 0.750};
		misalignAccumSpeed = 0.925;
		misalignResetSpeed = 0.700;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.045;
		kickResetTime      = 2.250;
	}
}