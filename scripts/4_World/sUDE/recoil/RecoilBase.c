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
	
	
	//////////////////////////////////////////////////////////////////
	// DEBUG
	array<ref array<string>> toDebugTable() {
		array<ref array<string>> t = {{ClassName()}};
		t.Insert({"handsRanges",       string.Format("%1 %2 %3 %4", handsRanges[0],    handsRanges[1],     handsRanges[2],    handsRanges[3])});
		t.Insert({"handsAccumSpeed",   ""+handsAccumSpeed});
		t.Insert({"handsResetSpeed",   ""+handsResetSpeed});
		t.Insert({"misalignIntensity", string.Format("%1 %2", misalignIntensity[0],    misalignIntensity[1])});
		t.Insert({"misalignAccumSpeed",""+misalignAccumSpeed});
		t.Insert({"misalignResetSpeed",""+misalignResetSpeed});
		t.Insert({"mouseRanges",       string.Format("%1 %2 %3 %4", mouseRanges[0],    mouseRanges[1],     mouseRanges[2],    mouseRanges[3])});
		t.Insert({"mouseTime",         ""+mouseTime});		
		t.Insert({"kick",              ""+kick});
		t.Insert({"kickResetTime",     ""+kickResetTime});
		return t;
	}
	
	static array<string> getCSVHeader() {
		return {
			"weapon"
			"handsMinX"
			"handsMaxX"
			"handsMinY"
			"handsMaxY"
			"handsAccumSpeed"
			"handsResetSpeed"
			"misalignIntensityX"
			"misalignIntensityY"
			"misalignAccumSpeed"
			"misalignResetSpeed"
			"mouseMinX"
			"mouseMaxX"
			"mouseMinY"
			"mouseMaxY"
			"mouseTime"
			"kick"
			"kickResetTime"
			"handsDelta"
			"handsSpeedDelta"
			"HANDS"
			"MISALIGN"
			"MOUSE"
		};
	}
	array<string> toCSV() {
		float handsDelta = Math.AbsFloat(handsRanges[0] - handsRanges[1]) + Math.AbsFloat(handsRanges[2] - handsRanges[3]);
		float handsSpeedDelta = handsAccumSpeed - handsResetSpeed;
		float hands = handsDelta * (1 - handsSpeedDelta);
		float misalign = misalignIntensity[0] + misalignIntensity[1];
		float mouse = Math.AbsFloat(mouseRanges[0] - mouseRanges[1]) + Math.AbsFloat(mouseRanges[2] - mouseRanges[3]);
		return {
			""+handsRanges[0]
			""+handsRanges[1]
			""+handsRanges[2]
			""+handsRanges[3]
			""+handsAccumSpeed
			""+handsResetSpeed
			""+misalignIntensity[0]
			""+misalignIntensity[1]
			""+misalignAccumSpeed
			""+misalignResetSpeed
			""+mouseRanges[0]
			""+mouseRanges[1]
			""+mouseRanges[2]
			""+mouseRanges[3]
			""+mouseTime
			""+kick
			""+kickResetTime
			""+handsDelta
			""+handsSpeedDelta
			""+hands
			""+misalign
			""+mouse
		};
	}
	
	static array<ref array<string>> toCSV(array<ref RecoilBase> recoils) {
		array<ref array<string>> csv = {getCSVHeader()};
		foreach (RecoilBase r : recoils) {
			csv.Insert(r.toCSV());
		}
		return csv;
	}
	
	static string toCSVStringAll() {
		array<ref RecoilBase> recoils = {
			new Ak101Recoil(null),
			new Ak74Recoil(null),
			new AkmRecoil(null),
			new Aks74uRecoil(null),
			new AUGRecoil(null),
			new B95Recoil(null),
			new Colt1911Recoil(null),
			new CZ527Recoil(null),
			new CZ550Recoil(null),
			new Cz61Recoil(null),
			new Cz75Recoil(null),
			new DEagleRecoil(null),
			new DerringerRecoil(null),
			new FALRecoil(null),
			new FamasRecoil(null),
			new Fnx45Recoil(null),
			new GlockRecoil(null),
			new Izh18Recoil(null),
			new Izh18SawedOffRecoil(null),
			new Izh43Recoil(null),
			new LongHornRecoil(null),
			new M16A2Recoil(null),
			new M4a1Recoil(null),
			new M79Recoil(null),
			new MagnumRecoil(null),
			new MakarovRecoil(null),
			new MkiiRecoil(null),
			new MosinRecoil(null),
			new MosinSawedOffRecoil(null),
			new Mp133Recoil(null),
			new Mp5kRecoil(null),
			new RepeaterRecoil(null),
			new Ruger1022Recoil(null),
			new SiagaRecoil(null),
			new ScoutRecoil(null),
			new SKSRecoil(null),
			new SvdRecoil(null),
			new Ump45Recoil(null),
			new VSSRecoil(null),
			new Winchester70Recoil(null)
		};
		string delimiter = "\"";
		string separator = ",";
		string csv;
		auto header = getCSVHeader();
		foreach (auto column : header) {
			csv += string.Format("%1%2%1%3", delimiter, column, separator);
		}
		csv += "\n";
		foreach (auto recoil : recoils) {
			csv += string.Format("%1%2%1", delimiter, recoil.Type());
			auto values = recoil.toCSV();
			foreach (auto value : values) {
				csv += string.Format("%3%1%2%1", delimiter, value, separator);
			}
			csv += "\n";
		}
		return csv;
	}
}
