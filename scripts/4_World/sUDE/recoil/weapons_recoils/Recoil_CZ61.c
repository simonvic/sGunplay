modded class Cz61Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.750, 1.050,  1.350 ,  1.985};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.720;
		
		misalignIntensity  = {0.125, 0.125};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.600;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.025;
		kickResetTime      = 1.450;
	}
}