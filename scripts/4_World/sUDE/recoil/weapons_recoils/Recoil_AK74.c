modded class Ak74Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.550,  1.550,  2.750,  3.985};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.725;
		
		misalignIntensity  = { 1.755,  0.550};
		misalignAccumSpeed = 0.950;
		misalignResetSpeed = 0.850;
	
		mouseRanges        = {-0.215,  0.215,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.047;
		kickResetTime      = 2.250;
	}
}