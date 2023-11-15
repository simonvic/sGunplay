modded class Izh18ShotgunRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-3.165,  3.285, 10.755, 12.850};
		handsAccumSpeed    = 0.990;
		handsResetSpeed    = 0.715;
		
		misalignIntensity  = { 1.750,  0.250};
		misalignAccumSpeed = 0.960;
		misalignResetSpeed = 0.875;
	
		mouseRanges        = {-0.215,  0.215,  1.750,  2.775};
		mouseTime          = 0.075;
	
		kick               = 0.095;
		kickResetTime      = 3.550;
	}
}