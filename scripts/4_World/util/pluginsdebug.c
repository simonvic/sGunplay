class PluginSDebug extends PluginBase {
	
	protected float m_time;
	
	static bool crosshair_enabled = false;
	static bool bodyClipAllContact_enabled = false;
	static bool bodyClipContactPos_enabled = false;
		
	protected PlayerBase m_player;
	protected Weapon_Base m_weapon;
	protected ref SRaycast m_crosshairRaycast;
	protected ref SRaycast m_bodyClipRaycast;
	
	Shape line = Debug.DrawLine("0 0 0", "0 0 0", 0xFF0000);
	
	void PluginSDebug(){
	}
	
	void ~PluginSDebug(){
	}
	
	override void OnUpdate(float delta_time){
		if(!m_player) m_player = PlayerBase.Cast(GetGame().GetPlayer());
		if(!m_weapon && m_player) m_weapon = Weapon_Base.Cast(m_player.GetItemInHands());
		
		m_time += delta_time;
		if(crosshair_enabled) updateCrosshair();
		
		if(bodyClipAllContact_enabled || bodyClipContactPos_enabled) updateBodyClip();
		
		if(false) updateMouse();
		
	}
	
	void updateMouse(){
			
		vector start = GetGame().GetCurrentCameraPosition();
		vector end = start + "1 0 0";
		
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(Debug.RemoveShape, 50, false, Debug.DrawLine(start, end, 0xFF0000));
	}
	
	void updateCrosshair(){
		Weapon_Base weapon = m_weapon;
		vector usti_hlavne_position = weapon.ModelToWorld(weapon.GetSelectionPositionLS( "usti hlavne" ));//usti hlavne
		vector konec_hlavne_position = weapon.ModelToWorld(weapon.GetSelectionPositionLS( "konec hlavne" ));//konec hlavne	
		vector direction = vector.Direction(konec_hlavne_position, usti_hlavne_position );
		
		//SDebug.spawnDebugDot(m_crosshairRaycast.getContactPos(), 0.005, 0.5);
		//SDebug.spawnDebugDot(m_crosshairRaycast.getBegPos(), 0.005, 0.5);
		//SDebug.spawnDebugDot(m_crosshairRaycast.getEndPos(), 0.005, 0.5);
		//SDebug.spawnDebugDot(usti_hlavne_position, 0.005, 0.5);
		//SDebug.spawnDebugDot(konec_hlavne_position, 0.005, 0.5);
		vector from = usti_hlavne_position;
		vector to = konec_hlavne_position + (direction * 100);
		
		SRaycast ray = new SRaycast("0 0 0", "0 0 0", 0.05, ObjIntersectView, CollisionFlags.NEARESTCONTACT);
		ray.setBegPos(from);
		ray.setEndPos(to);
		ray.launch();
		
		
		Debug.DestroyAllShapes();
		Debug.DrawLine(from, ray.getContactPos(), SColor.rgb(0xF00000).getARGB());
		SDebug.spawnDebugDot(ray.getContactPos(), 0.0, 2);
		
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