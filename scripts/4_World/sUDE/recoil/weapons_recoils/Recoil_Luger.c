modded class LugerRecoil {
	override void initRecoilParameters() {
		handsRanges        = {-0.950,  1.220,  4.450,  5.600};
		handsAccumSpeed    = 0.955;
		handsResetSpeed    = 0.750;

		misalignIntensity  = { 0.275,  0.275};
		misalignAccumSpeed = 0.975;
		misalignResetSpeed = 0.650;

		mouseRanges        = {-0.150,  0.150,  0.250,  0.550};
		mouseTime          = 0.050;

		kick               = 0.075;
		kickResetTime      = 1.250;
	}
}

