class SCOFocusing : SCameraOverlayAnimated {
	
	protected float m_fovResting;
	protected float m_fovFocusing;
	
	protected float m_focus;
	protected float m_vel[1];

	protected static const float MAX_INTENSITY = 0.45;
	
	override void onInit() {
		setImage("MyMODS/sFramework/GUI/textures/overlays/black_4x4.edds");
		setMask(SCOMasks.CIRCULAR);
		setMaskProgress(0);
		setMaskTransitionWidth(1);
		setPriority(eSCOPriority.EYE + 1);
	}
	
	override void onAnimate(float deltaTime) {
		m_focus = Math.SmoothCD(
			m_focus,
			Math.Min(MAX_INTENSITY, Math.InverseLerp(m_fovResting, m_fovFocusing, Camera.GetCurrentFOV()) * MAX_INTENSITY),
			m_vel, 0.1, 1000, deltaTime);
		
		setMaskProgress(m_focus);
	}
	
	void setRestingFOV(float fov) {
		m_fovResting = fov;
	}
	
	void setFocusingFOV(float fov) {
		m_fovFocusing = fov;
	}
	
}