modded class DEagleRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.750, 2.550,  6.250,  8.300};	
		handsAccumSpeed    = 0.985;
		handsResetSpeed    = 0.550;
		
		misalignIntensity  = {0.525, 0.525};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.650;
		
		mouseRanges        = { 0.775, 1.150,  1.250,  1.750};
		mouseTime          = 0.300;
	
		kick               = 0.080;
		kickResetTime      = 2.250;
	}
}