class AimingModelFilterRecoil : AimingModelFilterBase {
	
	override bool isActive(){
		//if (RecoilBase.legacyMode) return getAimingModel().getRecoil() != null;
		return true;
	}
	
	static SDebugUI dui;
	static bool debugMonitor = true;
	
	protected float m_time;
		
	protected float m_velHandsAccumX[1];
	protected float m_velHandsAccumY[1];
	
	protected float m_velHandsResetX[1];
	protected float m_velHandsResetY[1];
	
	protected float m_handsAccum[2];
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
		}
	}
	
	protected void applyMouseOffset(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		if (m_mouseAccum[1] < r.mouse[1]) {
			float relativeDelta = pDt / r.mouseResetTime;
			float deltaMouseX = r.mouse[0] * relativeDelta;
			float deltaMouseY = r.mouse[1] * relativeDelta;
			if ((m_mouseAccum[1] + deltaMouseY) > r.mouse[1]) {
				deltaMouseX = r.mouse[0] - m_mouseAccum[0];
				deltaMouseY = r.mouse[1] - m_mouseAccum[1];
			}
			
			m_mouseAccum[0] = m_mouseAccum[0] + deltaMouseX;
			m_mouseAccum[1] = m_mouseAccum[1] + deltaMouseY;
		}
		
		pModel.m_fAimXMouseShift += deltaMouseX * mouseMultiplier[0]; //@todo should the multiplier be added to the r.mouse?
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
			1 - r.handsAccumSpeed, 1000, pDt);
	}
	
	protected void applyMisalignment(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		pModel.m_fAimXCamOffset -= m_handsAccum[0] * r.misalignIntensity * misalignMultiplier[0];
		pModel.m_fAimYCamOffset -= m_handsAccum[1] * r.misalignIntensity * misalignMultiplier[1];
	}
	
	protected void reset(float pDt, notnull RecoilBase r) {
		m_handsAccum = {
			Math.SmoothCD(m_handsAccum[0], 0, m_velHandsResetX, 1 - r.handsResetSpeed, 1000, pDt),
			Math.SmoothCD(m_handsAccum[1], 0, m_velHandsResetY, 1 - r.handsResetSpeed, 1000, pDt)
		};			
		//m_mouseAccum = {0,0};
	}
		
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		dui = SDebugUI.of("RecoilBase");
		dui.begin();
		
		bool applyMouseOffset = true;
		bool applyHandsOffset = true;
		bool applyMisalignment = true;
		bool applyKick = true;
		if (debugMonitor) {
			dui.window(ClassName(), {(256+12)*2,1}, {0,0});
			dui.check("Legacy recoils", RecoilBase.legacyMode);
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
			dui.slider("hMultX",   hMultX,   0.01, 0, 2);
			dui.slider("hMultY",   hMultY,   0.01, 0, 2);
			dui.slider("mMultX",   mMultX,   0.01, 0, 2);
			dui.slider("mMultY",   mMultY,   0.01, 0, 2);
			dui.slider("misMultX", misMultX, 0.01, 0, 2);
			dui.slider("misMultY", misMultY, 0.01, 0, 2);
			dui.slider("kMult",    kMult,    0.01, 0, 2);
			handsMultiplier = {hMultX, hMultY};
			mouseMultiplier = {mMultX, mMultY};
			misalignMultiplier = {misMultX, misMultY};
			kickMultiplier = kMult;
			
			
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
			dui.plotlive("hands X",        pModel.m_fAimXHandsOffset,  -5.00, 5.00, plotSize, historySize);
			dui.plotlive("mouse X",        pModel.m_fAimXMouseShift,   -2.00, 2.00, plotSize, historySize);
			dui.plotlive("misalignment X", pModel.m_fAimXCamOffset,    -0.25, 0.25, plotSize, historySize);
			dui.plotlive("hands Y",        pModel.m_fAimYHandsOffset,  -0.25, 5.00, plotSize, historySize);
			dui.plotlive("mouse Y",        pModel.m_fAimYMouseShift,   -2.00, 2.00, plotSize, historySize);
			dui.plotlive("mouseaccum Y",        m_mouseAccum[1],   -2.00, 2.00, plotSize, historySize);
			dui.plotlive("misalignment Y", pModel.m_fAimYCamOffset,    -5.00, 0.50, plotSize, historySize);
			dui.plotlive("kick",           pModel.m_fCamPosOffsetZ,    -0.25, 0.25, plotSize, historySize);
		}
		dui.end();
	}
}