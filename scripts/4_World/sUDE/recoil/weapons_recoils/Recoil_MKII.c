modded class MkiiRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.150, 0.550,  1.050,  2.200};	
		handsAccumSpeed    = 0.925;
		handsResetSpeed    = 0.750;
		
		misalignIntensity  = {0.150, 0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
		
		mouseRanges        = { -0.175, 0.500,  0.250,  0.500};
		mouseTime          = 0.050;
	
		kick               = 0.040;
		kickResetTime      = 1.250;
	}
}