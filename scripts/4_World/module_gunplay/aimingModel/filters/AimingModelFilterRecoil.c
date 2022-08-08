class AimingModelFilterRecoil : AimingModelFilterBase {
	
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
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex) {
		m_time += pDt;
		dui = SDebugUI.of("RecoilBase");
		dui.begin();
		if (debugMonitor) {
			dui.window(ClassName(), {(256+12)*3,1}, {0,0});
			createDebugRecoilMonitor(pDt, pModel);
		}
		RecoilBase r = getAimingModel().getRecoil();
		if (r != null && m_recoil != r) {
			// new recoil has been generated
			delete m_recoil;
			m_recoil = r;
			accumulateRecoil(m_recoil);
		}
		
		if (m_recoil) {
			applyMouseOffset(pDt, pModel, m_recoil);
			applyHandsOffset(pDt, pModel, m_recoil);
			if (GetGame().IsClient()) {
				applyMisalignment(pDt, pModel, m_recoil);
				applyKick(pDt, pModel, m_recoil);
			}
			reset(pDt, m_recoil);
		}
		
		if (debugMonitor) {
			createDebugRecoilPlots(pDt, pModel);
		}
		dui.end();
	}
	
	/**
	*	@brief Called when a new recoil has been produced. Accumulate the recoil parameters
	*	@param recoil to accumulate
	*/
	protected void accumulateRecoil(notnull RecoilBase r) {
		m_time = 0;
		m_handsAccum[0] = m_handsAccum[0] + r.hands[0];
		m_handsAccum[1] = m_handsAccum[1] + r.hands[1];
		m_mouseAccum[0] = 0;
		m_mouseAccum[1] = 0;
		if (GetGame().IsClient()) {
			m_kickAccum = r.kick;
			m_misalignAccum[0] = m_misalignAccum[0] + r.hands[0];
			m_misalignAccum[1] = m_misalignAccum[1] + r.hands[1];
		}
	}
	
	
	/**
	*	@brief Apply mouse offset to aiming model
	*	@param delta time
	*	@param aiming model
	*	@param recoil to apply
	*/
	protected void applyMouseOffset(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		if (!applyMouseOffset) return;
		// compute delta values of mouse shift so we spread the movement on multiple frames while not making harsh movements
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
		
		PropertyModifiers modifiers = getWeapon().GetPropertyModifierObject();
		pModel.m_fAimXMouseShift -= deltaMouseX * mouseMultiplier[0] * modifiers.recoilOffsetMouse[0];
		pModel.m_fAimYMouseShift += deltaMouseY * mouseMultiplier[1] * modifiers.recoilOffsetMouse[1];
		
	}
	
	/**
	*	@brief Apply kick (camera Z-axis offset) to aiming model
	*	@param delta time
	*	@param aiming model
	*	@param recoil to apply
	*/
	protected void applyKick(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		if (!applyKick) return;
		float timeNormalized = SMath.normalizeClamp(m_time, 0, r.kickResetTime);
		float easing = 1 - Easing.EaseOutElastic(timeNormalized, 0.45);
		pModel.m_fCamPosOffsetZ	+= Math.Lerp(0, m_kickAccum * kickMultiplier * getWeapon().GetPropertyModifierObject().recoilKick, easing);
	}
	
	/**
	*	@brief Apply hands offset to aiming model
	*	@param delta time
	*	@param aiming model
	*	@param recoil to apply
	*/
	protected void applyHandsOffset(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		if (!applyHandsOffset) return;
		PropertyModifiers modifiers = getWeapon().GetPropertyModifierObject();
		pModel.m_fAimXHandsOffset += Math.SmoothCD(
			0,
			m_handsAccum[0] * handsMultiplier[0] * modifiers.recoilOffsetHands[0],
			m_velHandsAccumX,
			1 - r.handsAccumSpeed,
			1000, pDt);
		
		pModel.m_fAimYHandsOffset += Math.SmoothCD(
			0,
			m_handsAccum[1] * handsMultiplier[1] * modifiers.recoilOffsetHands[1],
			m_velHandsAccumY,
			1 - r.handsAccumSpeed,
			1000, pDt);
	}
	
	/**
	*	@brief Apply misalignment (camera rotation) to aiming model
	*	@param delta time
	*	@param aiming model
	*	@param recoil to apply
	*/
	protected void applyMisalignment(float pDt, SDayZPlayerAimingModel pModel, notnull RecoilBase r) {
		if (!applyMisalignment) return;
		float smoothTime = 1 - r.misalignAccumSpeed;
		PropertyModifiers modifiers = getWeapon().GetPropertyModifierObject();
		pModel.m_fAimXCamOffset -= Math.SmoothCD(
			0,
			m_misalignAccum[0] * r.misalignIntensity[0] * misalignMultiplier[0] * modifiers.recoilMisalignment[0],
			m_velMisalignAccumX,
			smoothTime,
			1000, pDt);
		
		pModel.m_fAimYCamOffset -= Math.SmoothCD(
			0,
			m_misalignAccum[1] * r.misalignIntensity[1] * misalignMultiplier[1] * modifiers.recoilMisalignment[1],
			m_velMisalignAccumY,
			smoothTime,
			1000, pDt);
	}
	
	/**
	*	@brief Reset the recoil
	*	@param delta time
	*	@param recoil to apply
	*/
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
	
	
	
	
	
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// DEBUG
	static SDebugUI dui;
	static bool debugMonitor = true;
	static float mouseMultiplier[2]    = {1,1};
	static float handsMultiplier[2]    = {1,1};
	static float misalignMultiplier[2] = {1,1};
	static float kickMultiplier        = 1;
	
	static bool applyMouseOffset = true;
	static bool applyHandsOffset = true;
	static bool applyMisalignment = true;
	static bool applyKick = true;
	
	protected void createDebugRecoilPlots(float pDt, SDayZPlayerAimingModel pModel) {
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
	
	protected void createDebugRecoilMonitor(float pDt, SDayZPlayerAimingModel pModel) {
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
		array<ref array<string>> recoilTable = {{"No data available."}, {"Shoot once to show recoil stats"}};
		if (m_recoil) {
			recoilTable = m_recoil.toDebugTable();
		}
		dui.table(recoilTable, {400, 256});
		auto attachHands = getWeapon().GetPropertyModifierObject().recoilOffsetHands;
		auto attachMisalign = getWeapon().GetPropertyModifierObject().recoilMisalignment;
		auto attachMouse = getWeapon().GetPropertyModifierObject().recoilOffsetMouse;
		auto attachKick = getWeapon().GetPropertyModifierObject().recoilKick;
		dui.table({
			{"Attachments modifiers"}
			{"recoilOffsetHands",  string.Format("-%1%% -%2%%", (1-attachHands[0])*100,    (1-attachHands[1])*100)}
			{"recoilMisalignment", string.Format("-%1%% -%2%%", (1-attachMisalign[0])*100, (1-attachMisalign[1])*100)}
			{"recoilOffsetMouse",  string.Format("-%1%% -%2%%", (1-attachMouse[0])*100,    (1-attachMouse[1])*100)}
			{"recoilKick",         string.Format("-%1%%",       (1-attachKick)*100)}
		}, {300, 128});
		dui.newline();
	}
}