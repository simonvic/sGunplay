modded class DerringerRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.750, 2.550,  5.250,  7.300};	
		handsAccumSpeed    = 0.985;
		handsResetSpeed    = 0.750;
		
		misalignIntensity  = {0.255, 0.250};
		misalignAccumSpeed = 0.985;
		misalignResetSpeed = 0.550;
		
		mouseRanges        = { -0.250, 0.275,  0.500,  0.750};
		mouseTime          = 0.100;
	
		kick               = 0.080;
		kickResetTime      = 2.250;
	}
}