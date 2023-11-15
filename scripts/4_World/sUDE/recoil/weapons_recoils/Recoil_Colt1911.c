modded class Colt1911Recoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.750,  1.250,  4.450,  5.600};	
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.750;
		
		misalignIntensity  = { 0.275,  0.275};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.650;
		
		mouseRanges        = {-0.155,  0.155,  0.250,  0.550};
		mouseTime          = 0.050;
	
		kick               = 0.075;
		kickResetTime      = 1.250;
	}
}