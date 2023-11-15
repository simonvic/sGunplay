modded class MakarovRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.750,  1.250,  4.050,  5.200};	
		handsAccumSpeed    = 0.925;
		handsResetSpeed    = 0.750;
		
		misalignIntensity  = { 0.250,  0.250};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.650;
		
		mouseRanges        = {-0.125,  0.125,  0.250,  0.500};
		mouseTime          = 0.050;
	
		kick               = 0.045;
		kickResetTime      = 1.250;
	}
}