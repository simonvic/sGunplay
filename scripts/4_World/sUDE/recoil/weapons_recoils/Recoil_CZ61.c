modded class Cz61Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.900,  0.900,  2.450,  3.700};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.725;
		
		misalignIntensity  = { 1.750,  0.225};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.850;
	
		mouseRanges        = {-0.215,  0.215,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.065;
		kickResetTime      = 1.450;
	}
}