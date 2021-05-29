class SDebug {

	static Particle spawnDebugDot(vector position, float lifetime = 0.05, float size = 1){
		//if(!GetGame().IsClient()) return;
		Particle particle = Particle.PlayInWorld(ParticleList.DEBUG_DOT,position);
		particle.ScaleParticleParam(EmitorParam.LIFETIME, lifetime);
		particle.ScaleParticleParam(EmitorParam.SIZE, size);
		return particle;
	}
	
	static void drawLine(vector from, vector to, SColor color, bool redraw = false, ShapeFlags flags = 0){
		drawLine(from, to, redraw, color, flags);
	}
	
	static void drawLine(vector from, vector to, bool redraw = false,  SColor color = null, ShapeFlags flags = 0){
		if(redraw) destroyShapes();
		if(!color) color = SColor.rgb(0xFF0000);
		Debug.DrawLine(from, to, color.getARGB(), flags);
	}
	
	static void destroyShapes(){
		Debug.DestroyAllShapes();
	}
	
	

}