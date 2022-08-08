modded class Aks74uRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-1.050, 1.550,  2.250 ,  3.285};	
		handsAccumSpeed    = 0.975;
		handsResetSpeed    = 0.550;
		
		misalignIntensity  = {0.075, 0.075};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.500;
	
		mouseRanges        = { 0.175, 0.250,  1.250,  1.750};
		mouseTime          = 0.150;
	
		kick               = 0.080;
		kickResetTime      = 2.250;
	}
}