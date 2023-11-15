modded class MkiiRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.550,  0.550,  3.050,  4.200};	
		handsAccumSpeed    = 0.905;
		handsResetSpeed    = 0.750;
		
		misalignIntensity  = { 0.250,  0.250};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.850;
		
		mouseRanges        = {-0.120,  0.120,  0.200,  0.350};
		mouseTime          = 0.050;
	
		kick               = 0.040;
		kickResetTime      = 1.250;
	}
}