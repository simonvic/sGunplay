modded class SiagaRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.165, 3.285,  7.265,  8.295};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.675;
		
		misalignIntensity  = {0.05, 0.05};
		misalignAccumSpeed = 0.955;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.750,  2.775};
		mouseTime          = 0.075;
	
		kick               = 0.095;
		kickResetTime      = 3.550;
	}
}