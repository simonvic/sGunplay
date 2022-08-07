class AimingModelFilterRecoil : AimingModelFilterBase {
	
	override bool isActive(){
		if (RecoilBase.legacyMode) return getAimingModel().getRecoil() != null;
		return true;
	}
	
	static SDebugUI dui;
	static bool debugMonitor = true;
	
	protected float m_time;
		
	protected float m_velHandsAccumX[1];
	protected float m_velHandsAccumY[1];
	protected float m_velHandsResetX[1];
	protected float m_velHandsResetY[1];
	
	protected float m_velMisalignAccumX[1];
	protected float m_velMisalignAccumY[1];
	protected float m_velMisalignResetX[1];
	protected float m_velMisalignResetY[1];
	
	protected float m_handsAccum[2];
	protected float m_misalignAccum[2];
	protected float m_mouseAccum[2];
	protected float m_kickAccum;
	
	protected ref RecoilBase m_recoil;
	
	static float mouseMultiplier[2]    = {1,1};
	static float handsMultiplier[2]    = {1,1};
	static float misalignMultiplier[2] = {1,1};
	static float kickMultiplier        = 1;
	
	protected void accumulateRecoil(notnull RecoilBase r) {
		m_time = 0;
		m_handsAccum = {m_handsAccum[0] + r.hands[0], m_handsAccum[1] + r.hands[1]};
		//m_mouseAccum = {r.mouse[0], r.mouse[1]};
		m_mouseAccum = {0,0};
		if (GetGame().IsClient()) {
			m_kickAccum = r.kick;
			m_misalignAccum = {m_misalignAccum[0] + r.hands[0], m_misalignAccum[1] + r.hands[1]};
		}
	}
	
	protected void applyMouseOffset(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		// compute delta values of mouse shift so we spread the movement on multiple frames
		if (m_mouseAccum[1] < r.mouse[1]) {
			float relativeDelta = pDt / r.mouseTime;
			float deltaMouseX = r.mouse[0] * relativeDelta;
			float deltaMouseY = r.mouse[1] * relativeDelta;
			if ((m_mouseAccum[1] + deltaMouseY) > r.mouse[1]) {
				deltaMouseX = r.mouse[0] - m_mouseAccum[0];
				deltaMouseY = r.mouse[1] - m_mouseAccum[1];
			}
			m_mouseAccum[0] = m_mouseAccum[0] + deltaMouseX;
			m_mouseAccum[1] = m_mouseAccum[1] + deltaMouseY;
		}
		
		pModel.m_fAimXMouseShift -= deltaMouseX * mouseMultiplier[0]; //@todo should the multiplier be added to the r.mouse?
		pModel.m_fAimYMouseShift += deltaMouseY * mouseMultiplier[1];
		
	}
	
	protected void applyKick(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		//float timeNormalized = Math.Clamp(Math.InverseLerp(0, r.kickResetTime, m_time), 0, 1);
		float timeNormalized = SMath.normalizeClamp(m_time, 0, r.kickResetTime);
		float easing = 1 - Easing.EaseOutElastic(timeNormalized, 0.45);
		pModel.m_fCamPosOffsetZ	+= Math.Lerp(0, m_kickAccum * kickMultiplier, easing);
	}
	
	protected void applyHandsOffset(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		pModel.m_fAimXHandsOffset += Math.SmoothCD(
			0,
			m_handsAccum[0] * handsMultiplier[0],
			m_velHandsAccumX,
			1 - r.handsAccumSpeed,
			1000, pDt);
		
		pModel.m_fAimYHandsOffset += Math.SmoothCD(
			0,
			m_handsAccum[1] * handsMultiplier[1],
			m_velHandsAccumY,
			1 - r.handsAccumSpeed,
			1000, pDt);
	}
	
	protected void applyMisalignment(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		float smoothTime = 1 - r.misalignAccumSpeed;
		pModel.m_fAimXCamOffset -= Math.SmoothCD(
			0,
			m_misalignAccum[0] * r.misalignIntensity[0] * misalignMultiplier[0],
			m_velMisalignAccumX,
			smoothTime,
			1000, pDt);
		
		pModel.m_fAimYCamOffset -= Math.SmoothCD(
			0,
			m_misalignAccum[1] * r.misalignIntensity[1] * misalignMultiplier[1],
			m_velMisalignAccumY,
			smoothTime,
			1000, pDt);
	}
	
	protected void reset(float pDt, notnull RecoilBase r) {
		float handsSmoothTime = 1 - r.handsResetSpeed;
		m_handsAccum[0] = Math.SmoothCD(m_handsAccum[0], 0, m_velHandsResetX, handsSmoothTime, 1000, pDt);
		m_handsAccum[1] = Math.SmoothCD(m_handsAccum[1], 0, m_velHandsResetY, handsSmoothTime, 1000, pDt);
		
		if (GetGame().IsClient()) {
			float misalignSmoothTime = 1 - r.misalignResetSpeed;
			m_misalignAccum[0] = Math.SmoothCD(m_misalignAccum[0], 0, m_velMisalignResetX, misalignSmoothTime, 1000, pDt);
			m_misalignAccum[1] = Math.SmoothCD(m_misalignAccum[1], 0, m_velMisalignResetY, misalignSmoothTime, 1000, pDt);
		}
	}
		
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		dui = SDebugUI.of("RecoilBase");
		dui.begin();
		
		bool applyMouseOffset = true;
		bool applyHandsOffset = true;
		bool applyMisalignment = true;
		bool applyKick = true;
		if (debugMonitor) {
			dui.window(ClassName(), {(256+12)*3,1}, {0,0});
			dui.check("Legacy recoils", RecoilBase.legacyMode);
			dui.newline();
			dui.check("applyMouseOffset", applyMouseOffset);
			dui.check("applyHandsOffset", applyHandsOffset);
			dui.check("applyMisalignment", applyMisalignment);
			dui.check("applyKick", applyKick);
			dui.newline();
			float hMultX = 1;
			float hMultY = 1;
			float mMultX = 1;
			float mMultY = 1;
			float misMultX = 1;
			float misMultY = 1;
			float kMult = 1;
			dui.slider("hMultX",   hMultX,   0.01);
			dui.slider("hMultY",   hMultY,   0.01);
			dui.newline();
			dui.slider("mMultX",   mMultX,   0.01);
			dui.slider("mMultY",   mMultY,   0.01);
			dui.newline();
			dui.slider("misMultX", misMultX, 0.01);
			dui.slider("misMultY", misMultY, 0.01);
			dui.newline();
			dui.slider("kMult",    kMult,    0.01);
			handsMultiplier = {hMultX, hMultY};
			mouseMultiplier = {mMultX, mMultY};
			misalignMultiplier = {misMultX, misMultY};
			kickMultiplier = kMult;
			dui.newline();
			if (m_recoil) {
				dui.table(m_recoil.toDebugTable(), {512, 256});
				dui.newline();
			}
		}
		
		if (RecoilBase.legacyMode && getAimingModel().getRecoil() != null) {
			float recoilOffsetMouseX;
			float recoilOffsetMouseY;
			float recoilOffsetHandsX;
			float recoilOffsetHandsY;
			getAimingModel().getRecoil().Update(pModel, recoilOffsetMouseX, recoilOffsetMouseY, recoilOffsetHandsX, recoilOffsetHandsY, pDt);
			pModel.m_fAimXHandsOffset += recoilOffsetHandsX;
			pModel.m_fAimYHandsOffset += recoilOffsetHandsY;
			pModel.m_fAimXCamOffset   -= recoilOffsetHandsX;
			pModel.m_fAimYCamOffset	  -= recoilOffsetHandsY;
			pModel.m_fAimXMouseShift  += recoilOffsetMouseX;
			pModel.m_fAimYMouseShift  += recoilOffsetMouseY;
		} else {
			
			m_time += pDt;
			RecoilBase r = getAimingModel().getRecoil();
			if (r != null && m_recoil != r) {
				// new recoil has been generated
				delete m_recoil;
				m_recoil = r;
				accumulateRecoil(m_recoil);
			}
			
			if (m_recoil) {
				if (applyMouseOffset) applyMouseOffset(pDt, pModel, m_recoil);
				if (applyHandsOffset) applyHandsOffset(pDt, pModel, m_recoil);
				if (GetGame().IsClient()) {
					if (applyMisalignment) applyMisalignment(pDt, pModel, m_recoil);
					if (applyKick) applyKick(pDt, pModel, m_recoil);
				}
				reset(pDt, m_recoil);
			}
		}
		
		if (debugMonitor) {
			array<int> plotSize = {128,128};
			int historySize = 25;
			dui.newline();
			float plotSizeX = 128;
			float plotSizeY = 128;
			dui.slider("plot size X", plotSizeX, 128, 0, 1024);
			dui.slider("plot size Y", plotSizeY, 128, 0, 1024);
			plotSize = {plotSizeX, plotSizeY};
			dui.newline();
			dui.plotlive("hands X",        pModel.m_fAimXHandsOffset,  -20.00, 20.00, plotSize, historySize);
			dui.plotlive("misalignment X", pModel.m_fAimXCamOffset,    20.00, -20.00, plotSize, historySize);
			dui.plotlive("mouse X",        pModel.m_fAimXMouseShift,   -2.00, 2.00, plotSize, historySize);
			dui.newline();
			dui.plotlive("hands Y",        pModel.m_fAimYHandsOffset,  -20.00, 20.00, plotSize, historySize);
			dui.plotlive("misalignment Y", pModel.m_fAimYCamOffset,    20.00, -20.00, plotSize, historySize);
			dui.plotlive("mouse Y",        pModel.m_fAimYMouseShift,   -2.00, 2.00, plotSize, historySize);
			dui.newline();
			dui.plotlive("kick",           pModel.m_fCamPosOffsetZ,    -0.25, 0.25, plotSize, historySize);
		}
		dui.end();
	}
}