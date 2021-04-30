modded class PluginManager{
	
	override void Init(){
		super.Init();
		
		//----------------------------------------------------------------------
		// Register modules
		//----------------------------------------------------------------------
		//				Module Class Name 						Client	Server
		//----------------------------------------------------------------------
				
		//=========== Debug =============
		RegisterPlugin( "PluginSDebug",						true, 	false ); //server false?
	}
}