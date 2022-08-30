modded class Ump45Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.060, 0.750,  1.450 ,  1.785};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.725;
		
		misalignIntensity  = {0.250, 0.250};
		misalignAccumSpeed = 0.855;
		misalignResetSpeed = 0.600;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.025;
		kickResetTime      = 2.250;
	}
}