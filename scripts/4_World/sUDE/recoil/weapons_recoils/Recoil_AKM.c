modded class AkmRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.765, 1.085,  1.765,  2.595};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.550;
		
		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.550;
	
		mouseRanges        = { 0.175, 0.250,  2.250,  2.750};
		mouseTime          = 0.200;
	
		kick               = 0.074;
		kickResetTime      = 2.250;
	}
}