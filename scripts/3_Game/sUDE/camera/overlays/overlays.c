class SCOOpticMisalignment : SCameraOverlayTimed {

	override void onInit() {
		setDuration(1.0);
		setDeactivateOnStop(true);
		setImage("MyMODS/sFramework/GUI/textures/overlays/black_4x4.edds");
		setMask(SCOMasks.CIRCULAR);
		setMaskTransitionWidth(1);
		setPriority(eSCOPriority.HEADGEAR + 1);
	}
	
	override void onAnimate(float deltaTime) {
		
		setMaskProgress(SMath.mapTo(getRemaining(), 0, getDuration(), 0, 1.0));
		
		setSize(
			SMath.mapTo(getRemaining(), 0, getDuration(), 1, 2.5),
			1.5);
		
		setPosition(
			SMath.mapTo(getRemaining(), 0, getDuration(), 0, 0.75),
		 	0);

	}
}