class PluginSDebug extends PluginBase {
	
	protected float m_time;
	
	static bool crosshair_enabled = false;
	static bool bodyClipAllContact_enabled = false;
	static bool bodyClipContactPos_enabled = false;
		
	protected PlayerBase m_player;
	protected ref SRaycast m_crosshairRaycast;
	protected ref SRaycast m_bodyClipRaycast;
	
	void PluginSDebug(){
	}
	
	void ~PluginSDebug(){
	}
	
	override void OnUpdate(float delta_time){
		if(!m_player) m_player = PlayerBase.Cast(GetGame().GetPlayer());
		m_time += delta_time;
		if(crosshair_enabled) updateCrosshair();
		
		if(bodyClipAllContact_enabled || bodyClipContactPos_enabled) updateBodyClip();
		
	}
	
	void updateCrosshair(){
		
		vector start,end, direction;	
		Weapon_Base weapon = Weapon_Base.Cast(PlayerBase.Cast(m_player).GetItemInHands());

		
		//int idx = m_player.GetBoneIndexByName("RightHand");
		//start = m_player.GetBonePositionWS(idx); 
		start = weapon.ModelToWorld(weapon.GetSelectionPositionWS( "trigger" ));
		direction = vector.Direction(start,weapon.ModelToWorld(weapon.GetSelectionPositionLS( "Usti hlavne" )));

		end = start + (direction * 10) + "0 -0.5 0";		
		m_crosshairRaycast = new SRaycast(start, end, 0.05, ObjIntersectView, CollisionFlags.NEARESTCONTACT);
		m_crosshairRaycast.addIgnoredObject(m_player);
		m_crosshairRaycast.launch();
		
		SDebug.spawnDebugDot(m_crosshairRaycast.getContactPos(), 0.005, 0.5);
		SDebug.spawnDebugDot(m_crosshairRaycast.getBegPos(), 0.005, 0.5);
		SDebug.spawnDebugDot(m_crosshairRaycast.getEndPos(), 0.005, 0.5);
		
	}
	
	void updateBodyClip(){		
		
		vector point = m_player.GetPosition() + vector.Forward * 2;
		
		vector from = m_player.GetPosition();
		vector axis = vector.Up;
		float cosAngle = Math.Cos(m_time*Math.PI);
		float sinAngle = Math.Sin(m_time*Math.PI);
		
		
		vector offsetPos = from - point;
		vector result = vector.RotateAroundZero(offsetPos, axis, cosAngle, sinAngle) + from;
		
		m_bodyClipRaycast = new SRaycast(from + "0 1.5 0", result + "0 1.5 0", 0.05, 0, CollisionFlags.FIRSTCONTACT);
		m_bodyClipRaycast.addIgnoredObject(m_player);
		m_bodyClipRaycast.launch();
		if(bodyClipContactPos_enabled && m_bodyClipRaycast.hasHit())
			SDebug.spawnDebugDot(m_bodyClipRaycast.getContactPos(), 0.05, 2);
		
		if(bodyClipAllContact_enabled){
			SDebug.spawnDebugDot(m_bodyClipRaycast.getContactPos(), 0.02, 2);
			SDebug.spawnDebugDot(from, 0.02, 1);
			SDebug.spawnDebugDot(point, 0.02, 1);
		}
		
	}
	
	static void sandbox(){
		SLog.d("Config tests");
		string cfgName = "sude_CfgPPE";
		string stringValue;
		float floatValue;
		vector vectorValue;
		int intValue;
		TStringArray stringValues = new TStringArray;
		TFloatArray floatValues = new TFloatArray;
		TIntArray intValues = new TIntArray;
		
		string baseName;
		
		string pathArray[] = {cfgName,"ClassTest","stringTest"};
		TStringArray pathTest = new TStringArray;
		pathTest.Init(pathArray);
		
		SLog.d(pathTest, "PathTest ", 1);
		SLog.d(GetGame().ConfigPathToString(pathTest), "", 2);
		
		
		if ( GetGame().ConfigIsExisting(cfgName) ){
			GetGame().ConfigGetText(cfgName+" stringTest",stringValue);
			floatValue = GetGame().ConfigGetFloat(cfgName+" floatTest");
			vectorValue = GetGame().ConfigGetVector(cfgName+" vectorTest");
			intValue = GetGame().ConfigGetInt(cfgName+" intTest");
			
			GetGame().ConfigGetTextArray(cfgName+" stringArrayTest", stringValues);
			GetGame().ConfigGetFloatArray(cfgName+" floatArrayTest", floatValues);
			GetGame().ConfigGetIntArray(cfgName+" intArrayTest", intValues);
			GetGame().ConfigGetBaseName(cfgName,baseName);
			
			SLog.d("There are " + GetGame().ConfigGetChildrenCount(cfgName) + " children in " + cfgName, "", 1);
			SLog.d(stringValue, "", 2);
			SLog.d(floatValue, "", 2);
			SLog.d(vectorValue, "", 2);
			SLog.d(intValue, "", 2);
			SLog.d(stringValues, "", 2);
			SLog.d(floatValues, "", 2);
			SLog.d(intValues, "", 2);	
				
			SLog.d(GetGame().ConfigGetTextOut(cfgName+" ClassTest stringTest"), "", 1);
			
			SLog.d(baseName, "BaseName", 1);	
		}
			
		
	}

}