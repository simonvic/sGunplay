modded class M16A2Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.250, 0.550,  2.750,  3.985};	
		handsAccumSpeed    = 0.920;
		handsResetSpeed    = 0.800;
		
		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.905;
		misalignResetSpeed = 0.750;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.015;
		kickResetTime      = 2.250;
	}
}