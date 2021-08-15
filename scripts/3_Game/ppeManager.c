modded class PPEManager {

	//@todo temp-fix until sVisual will preload preprocessor defines
	override static void requestOpticLens(TFloatArray lens){
		requestOpticLens(lens[0],lens[1],lens[2],lens[3]);
	}
	
	override static void requestOpticLens(float intensity, float centerX, float centerY, float chromAberIntensity){
		PPEffects.SetLensEffect(intensity, chromAberIntensity, centerX, centerY);
	}
	
	override static void resetOpticLens(){
		PPEffects.ResetLensEffect();
	}
}