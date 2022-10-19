modded class MissionServer {
	override void preloadSUserConfigConstraints() {
		super.preloadSUserConfigConstraints();
		SUserConfigConstraints.gunplay();
	}
}