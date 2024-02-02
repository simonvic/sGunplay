/**
*	Transparent data carrier of random recoil values, to be used from outside
*/
modded class RecoilBase {
	
	void RecoilBase(Weapon_Base weapon) {
		initRecoilParameters();
		compute();
	}
	
	
	protected void initRecoilParameters();
	
	//@todo replace hands and mouse with vector for more precision?
	
	//////////////////////////////////////////////////
	// IN
	float handsRanges[4]       = {-0.350, 0.450,  1.250,  1.300}; // Hands offset random ranges {min horizontal, max horizontal, min vertical, max vertical}
	float handsAccumSpeed      = 0.925;                           // speed of hands offset accumulation
	float handsResetSpeed      = 0.400;                           // speed of hands offset reset
	
	float misalignIntensity[2] = {0.150, 0.150};                  // Misalignment intensity compared to handsRanges {intensity horizontal, intensity vertical}
	float misalignAccumSpeed   = 0.600;                           // speed of misalignment accumulation
	float misalignResetSpeed   = 0.200;                           // speed of misalignment reset
	
	float mouseRanges[4]       = {-0.050, 0.100,  1.500,  1.600}; // Mouse offset random ranges {min horizontal, max horizontal, min vertical, max vertical}
	float mouseTime            = 0.250;                           // speed of mouse movement
	
	float kick                 = 0.0314;                          // Back kick intensity
	float kickResetTime        = 1.000;                           // speed of back kick reset
	//////////////////////////////////////////////////
	
	
	//////////////////////////////////////////////////
	// OUT
	float hands[2];
	float mouse[2];
	//////////////////////////////////////////////////
	
	protected void compute() {
		computeOffsetHands();
		computeOffsetMouse();
	}
	
	protected void computeOffsetHands() {
		hands[0] = getSyncedRandom(handsRanges[0], handsRanges[1]);
		hands[1] = getSyncedRandom(handsRanges[2], handsRanges[3]);
	}
	
	protected void computeOffsetMouse() {
		mouse[0] = getSyncedRandom(mouseRanges[0], mouseRanges[1]);
		mouse[1] = getSyncedRandom(mouseRanges[2], mouseRanges[3]);
	}
	
	protected float getSyncedRandom(float min = 0, float max = 1) {
		return m_Player.GetRandomGeneratorSyncManager().GetRandomInRange(RandomGeneratorSyncUsage.RGSRecoil, min, max);
	}
	
}
