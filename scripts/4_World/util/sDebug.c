class SDebug {

	static Particle spawnDebugDot(vector position, float lifetime = 0.5, float size = 5){
		//if(!GetGame().IsClient()) return;
		Particle particle = Particle.PlayInWorld(ParticleList.DEBUG_DOT,position);
		particle.ScaleParticleParam(EmitorParam.LIFETIME, lifetime);
		particle.ScaleParticleParam(EmitorParam.SIZE, size);
		return particle;
	}

}