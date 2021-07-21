class PluginSDebug extends PluginBase {
	
	protected float m_time;
	
	static bool crosshair_enabled = false;
	static bool bodyClipAllContact_enabled = false;
	static bool bodyClipContactPos_enabled = false;
		
	protected static PlayerBase simonvic;
	protected static Weapon_Base m_weapon;
	protected ref SRaycast m_crosshairRaycast;
	protected ref SRaycast m_bodyClipRaycast;
	
	protected static ref array<ref SurvivorBase> theBoris = new array<ref SurvivorBase>;
	
	Shape line = Debug.DrawLine("0 0 0", "0 0 0", 0xFF0000);
	
	void PluginSDebug(){
		m_crosshairRaycast = new SRaycast(vector.Zero, vector.Zero, 0.05, ObjIntersectView, CollisionFlags.NEARESTCONTACT);
		m_bodyClipRaycast = new SRaycast(vector.Zero, vector.Zero, 0.05, 0, CollisionFlags.FIRSTCONTACT);
	}
	
	void ~PluginSDebug(){
	}
	
	override void OnUpdate(float delta_time){
		
		if(GetGame().IsClient() || !GetGame().IsMultiplayer()) {
			simonvic = PlayerBase.Cast(GetGame().GetPlayer());
			onUpdateClient(delta_time);
		}
		
		if(GetGame().IsServer() || !GetGame().IsMultiplayer()) {
			array<Man> players = new array<Man>;
			GetGame().GetPlayers(players);
			simonvic = PlayerBase.Cast(players[0]);
			onUpdateServer(delta_time);
		}
		
		onUpdateBoth(delta_time);
	}
	
	void onUpdateBoth(float delta_time){
	}
	
	void onUpdateClient(float delta_time){
		if(!simonvic) simonvic = PlayerBase.Cast(GetGame().GetPlayer());
		if(simonvic && Weapon_Base.Cast(simonvic.GetItemInHands())) m_weapon = Weapon_Base.Cast(simonvic.GetItemInHands());
		
		m_time += delta_time;
		if(crosshair_enabled) updateCrosshair();
		
		if(bodyClipAllContact_enabled || bodyClipContactPos_enabled) updateBodyClip();
		
		if(false) updateMouse();
	}


	void onUpdateServer(float delta_time){
	}
	
	
	static void setupShootingDebugArea(){
		if(!simonvic){
			array<Man> players = new array<Man>;
			GetGame().GetPlayers(players);
			simonvic = PlayerBase.Cast(players[0]);
		}
		vector startPosition = simonvic.GetPosition();
		vector margin = "0 0 0.2";
		vector verticalMargin = "0 0.2 0";
		
		PluginSDebug.spawnWeaponsSet(startPosition, margin);
		PluginSDebug.spawnAmmoSet(startPosition + "-1 0 0", margin, verticalMargin);
		PluginSDebug.spawnDefaultBorisDummies();
	}
	
	
	static void spawnBorisDummies(vector startPosition, array<float> distances, vector direction){
		foreach(float dis : distances){
			EntityAI boris = null;
			SSpawnable.build("SurvivorM_Boris").spawn(startPosition + direction * dis).collect(boris);
			if(boris != null){
				boris.SetCanBeDestroyed(false);
				theBoris.Insert(SurvivorBase.Cast(boris));
			}
		}
	}
	
	static void spawnDefaultBorisDummies(){
		PluginSDebug.spawnBorisDummies(simonvic.GetPosition(), {
			25,
			50,
			100,
			220,
			400,
			600,
			800,
			1000
		}, simonvic.GetDirection());
	}
	
	static void deleteTheBoris(){
		foreach(SurvivorBase boris : theBoris){
			GetGame().ObjectDelete(boris);
			GetGame().ObjectDeleteOnClient(boris);
		}
	}
	
	static void setTheBorisInvincibility(bool invincible){
		foreach(SurvivorBase boris : theBoris){
			boris.SetCanBeDestroyed(!invincible);
		}
	}
	
	
	
	static void spawnWeaponsSet(vector startPosition, vector margin){
		
		array<ref SSpawnable> spawnables = new array<ref SSpawnable>;
			
		////////////////////////////////////////////////////////////
		// ASSAULT RIFLES
		spawnables.Insert(SSpawnable.build("M4A1").withAttachments({
			"M4_Suppressor",
			"M4_OEBttstck",
			"M4_RISHndgrd"
		}).withSpawnableAttachments(
			(new SSpawnable("ReflexOptic")).withAttachment("Battery9V")));
		
		spawnables.Insert(SSpawnable.build("M16A2"));
		
		spawnables.Insert(SSpawnable.build("AK101").withAttachments({
			"AK_Suppressor",
			"AK_PlasticBttstck",
			"AK_RailHndgrd"
		}).withSpawnableAttachments(
			(new SSpawnable("PSO11Optic")).withAttachment("Battery9V"),
			(new SSpawnable("UniversalLight")).withAttachment("Battery9V")));
		
		spawnables.Insert(SSpawnable.build("AK74").withAttachments({
			"AK_Suppressor",
			"AK_PlasticBttstck",
			"AK_RailHndgrd"
		}).withSpawnableAttachments(
			(new SSpawnable("KobraOptic")).withAttachment("Battery9V"),
			(new SSpawnable("UniversalLight")).withAttachment("Battery9V")));
		
		spawnables.Insert(SSpawnable.build("AKM").withAttachments({
			"AK_Suppressor",
			"AK_WoodBttstck",
			"AK_WoodHndgrd"
		}).withSpawnableAttachments(
			(new SSpawnable("KobraOptic")).withAttachment("Battery9V")));
		
		spawnables.Insert(SSpawnable.build("AKS74U").withAttachments({
			"AK_Suppressor",
			"AKS74U_Bttstck",
			"GhillieAtt_tan"
		}));
		
		spawnables.Insert(SSpawnable.build("FAL").withAttachments({
			"Fal_FoldingBttstck"
		}).withSpawnableAttachments(
			(new SSpawnable("M68Optic")).withAttachment("Battery9V")));
		
		spawnables.Insert(SSpawnable.build("VSS").withAttachments({
			"KashtanOptic"
		}));
		
		spawnables.Insert(SSpawnable.build("ASVAL").withSpawnableAttachments(
			(new SSpawnable("UniversalLight")).withAttachment("Battery9V"),
			(new SSpawnable("ACOGOptic")).withAttachment("Battery9V")));
		
		
		////////////////////////////////////////////////////////////
		// SMG
		spawnables.Insert(SSpawnable.build("MP5K").withAttachments({
			"MP5_Compensator",
			"MP5k_StockBttstck",
			"MP5_RailHndgrd"
		}).withSpawnableAttachments(
			(new SSpawnable("ReflexOptic")).withAttachment("Battery9V"),
			(new SSpawnable("UniversalLight")).withAttachment("Battery9V")));
		
		spawnables.Insert(SSpawnable.build("CZ61"));
		spawnables.Insert(SSpawnable.build("UMP45"));
		
		
		
		////////////////////////////////////////////////////////////
		// RIFLES
		spawnables.Insert(SSpawnable.build("B95").withAttachments({
			"HuntingOptic"
		}));
		
		spawnables.Insert(SSpawnable.build("CZ527").withAttachments({
			"HuntingOptic"
		}));
		
		spawnables.Insert(SSpawnable.build("Winchester70").withAttachments({
			"HuntingOptic"
		}));
		
		spawnables.Insert(SSpawnable.build("Mosin9130").withAttachments({
			"PUScopeOptic",
			"Mosin_Compensator"
		}));
		
		spawnables.Insert(SSpawnable.build("SawedoffMosin9130"));
		spawnables.Insert(SSpawnable.build("Repeater"));
		spawnables.Insert(SSpawnable.build("Ruger1022"));
		spawnables.Insert(SSpawnable.build("SVD"));
		spawnables.Insert(SSpawnable.build("SKS"));
		spawnables.Insert(SSpawnable.build("Izh18"));
		spawnables.Insert(SSpawnable.build("SawedoffIzh18"));
		
		
		////////////////////////////////////////////////////////////
		// SHOTGUNS
		spawnables.Insert(SSpawnable.build("Saiga").withAttachments({
			"Saiga_Bttstck"
		}));
		
		spawnables.Insert(SSpawnable.build("Mp133Shotgun").withSpawnableAttachments(
			(new SSpawnable("FNP45_MRDSOptic")).withAttachment("Battery9V")));
		
		spawnables.Insert(SSpawnable.build("Izh43Shotgun"));
		spawnables.Insert(SSpawnable.build("SawedoffIzh43Shotgun"));
		
		
		
		////////////////////////////////////////////////////////////
		// HANDGUNS
		spawnables.Insert(SSpawnable.build("Magnum"));
		spawnables.Insert(SSpawnable.build("MakarovIJ70"));
		spawnables.Insert(SSpawnable.build("MKII"));
		spawnables.Insert(SSpawnable.build("Colt1911").withAttachments({
			"PistolSuppressor"
		}).withSpawnableAttachments(
			(new SSpawnable("TLRLight")).withAttachment("Battery9V")));
		
		spawnables.Insert(SSpawnable.build("CZ75").withAttachments({
			"PistolSuppressor"
		}).withSpawnableAttachments(
			(new SSpawnable("TLRLight")).withAttachment("Battery9V"),
			(new SSpawnable("FNP45_MRDSOptic")).withAttachment("Battery9V")));
		
		spawnables.Insert(SSpawnable.build("FNX45").withAttachments({
			"PistolSuppressor"
		}).withSpawnableAttachments(
			(new SSpawnable("TLRLight")).withAttachment("Battery9V"),
			(new SSpawnable("FNP45_MRDSOptic")).withAttachment("Battery9V")));
		
		spawnables.Insert(SSpawnable.build("Glock19").withAttachments({
			"PistolSuppressor"
		}).withSpawnableAttachments(
			(new SSpawnable("TLRLight")).withAttachment("Battery9V"),
			(new SSpawnable("FNP45_MRDSOptic")).withAttachment("Battery9V")));
		
		spawnables.Insert(SSpawnable.build("Deagle").withAttachments({
			"PistolSuppressor",
			"PistolOptic"
		}));
		
		vector position = startPosition;
		foreach(SSpawnable s : spawnables){
			s.spawn(position).collect().SetOrientation("0 0 0");
			position = position + margin;
			
		}
	}
	
	static void spawnAmmoSet(vector startPosition, vector margin, vector verticalMargin){
		vector position = startPosition;
		
		SSpawnable.build("Mag_STANAG_30Rnd").spawn(position);
		SSpawnable.build("Mag_STANAGCoupled_30Rnd").spawn(position + verticalMargin );

		position = position + margin;
		
		SSpawnable.build("Mag_AK101_30Rnd").spawn(position);		

		position = position + margin;
		
		SSpawnable.build("Mag_AK74_30Rnd").spawn(position);

		position = position + margin;
		
		SSpawnable.build("Mag_AKM_30Rnd").spawn(position);
		SSpawnable.build("Mag_AKM_Drum75Rnd").spawn(position);

		position = position + margin;
		
		SSpawnable.build("Mag_FAL_20Rnd").spawn(position);

		position = position + margin;
		
		SSpawnable.build("Mag_VSS_10Rnd").spawn(position);

		position = position + margin;
		
		SSpawnable.build("Mag_VAL_20Rnd").spawn(position);

		position = position + margin;
		
		SSpawnable.build("Mag_MP5_15Rnd").spawn(position);
		SSpawnable.build("Mag_MP5_30Rnd").spawn(position + verticalMargin);

		position = position + margin;
		
		Magazine.Cast(SSpawnable.build("Ammo_308Win").spawn(position).collect()).ServerSetAmmoCount(20);

		position = position + margin;
		
		SSpawnable.build("Mag_CZ527_5rnd").spawn(position);

		position = position + margin;
		
		Magazine.Cast(SSpawnable.build("Ammo_308WinTracer").spawn(position).collect()).ServerSetAmmoCount(20);

		position = position + margin;
		
		Magazine.Cast(SSpawnable.build("Ammo_762x54Tracer").spawn(position).collect()).ServerSetAmmoCount(20);

		position = position + margin;
		
		Magazine.Cast(SSpawnable.build("Ammo_357").spawn(position).collect()).ServerSetAmmoCount(20);

		position = position + margin;
		
		SSpawnable.build("Mag_SVD_10Rnd").spawn(position);

		position = position + margin;
		
		Magazine.Cast(SSpawnable.build("Ammo_762x39Tracer").spawn(position).collect()).ServerSetAmmoCount(20);

		position = position + margin;
		
		Magazine.Cast(SSpawnable.build("Ammo_12gaPellets").spawn(position).collect()).ServerSetAmmoCount(20);
		Magazine.Cast(SSpawnable.build("Ammo_12gaSlug").spawn(position + verticalMargin).collect()).ServerSetAmmoCount(20);
		Magazine.Cast(SSpawnable.build("Ammo_12gaRubberSlug").spawn(position).collect()).ServerSetAmmoCount(20);

		position = position + margin;
		
		SSpawnable.build("Mag_Saiga_5Rnd").spawn(position + verticalMargin);
		SSpawnable.build("Mag_Saiga_8Rnd").spawn(position + verticalMargin);
		SSpawnable.build("Mag_Saiga_Drum20Rnd").spawn(position + verticalMargin * 2);

		position = position + margin;
		
		SSpawnable.build("Mag_IJ70_8Rnd").spawn(position + verticalMargin);

		position = position + margin;
		
		SSpawnable.build("Mag_MKII_10Rnd").spawn(position + verticalMargin);

		position = position + margin;
		
		SSpawnable.build("Mag_1911_7Rnd").spawn(position + verticalMargin);

		position = position + margin;
		
		SSpawnable.build("Mag_CZ75_15Rnd").spawn(position + verticalMargin);

		position = position + margin;
		
		SSpawnable.build("Mag_FNX45_15Rnd").spawn(position + verticalMargin);

		position = position + margin;
		
		SSpawnable.build("Mag_Glock_15Rnd").spawn(position + verticalMargin);

		position = position + margin;
		
		SSpawnable.build("Mag_Deagle_9rnd").spawn(position + verticalMargin);

		position = position + margin;
	
	}
	
	static void updateMovementSettings(){
		PlayerBase player;
		if(GetGame().IsClient() || !GetGame().IsMultiplayer()) {
			player = PlayerBase.Cast(GetGame().GetPlayer());



		}
		
		if(GetGame().IsServer() || !GetGame().IsMultiplayer()) {
			array<Man> players = new array<Man>;
			GetGame().GetPlayers(players);
			player = PlayerBase.Cast(players[0]);
		}
		
		SHumanCommandMoveSettings hcm = player.GetDayZPlayerType().CommandMoveSettingsW();

		//! run sprint (SHIFT HOLD) filter 
		hcm.m_fRunSpringTimeout = 0.1;							//!< filter span value		[s]
		hcm.m_fRunSpringMaxChange = 10.0;							//!< filter speed value		[val/s]

		//! WSAD direction filter 
		hcm.m_fDirFilterTimeout = 0.1;						//!< direction filter timeout [s]
		hcm.m_fDirFilterSpeed = Math.DEG2RAD * 360; 		//!< direction filter max rot speed [rad/s]
		hcm.m_fMaxSprintAngle = Math.DEG2RAD * 45.01;		//!< max sprint angle [rad]

		hcm.m_fTurnAngle = 45;						//!< this is when char starts tu turn
		hcm.m_fTurnEndUpdateNTime = 0.7;						//!< this is end norm time (turn amount is not updated after this time)
		hcm.m_fTurnNextNTime = 0.9;						//!< this is norm time when new turn from old turn is evaluated again (turn->turn)


		hcm.m_fHeadingChangeLimiterIdle = 500000; 			//!<
		hcm.m_fHeadingChangeLimiterWalk = 2000;				//!<
		hcm.m_fHeadingChangeLimiterRun = 1500;				//!<		
		hcm.m_fLeaningSpeed = 3.0;
		player.StartCommand_Move();
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
		
		m_crosshairRaycast.init(from,to).launch();
		
		
		Debug.DestroyAllShapes();
		Debug.DrawLine(from, m_crosshairRaycast.getContactPosition(), SColor.rgb(0xF00000).getARGB());
		SDebug.spawnDebugDot(m_crosshairRaycast.getContactPosition(), 0.05, 1);
		
	}
	
	void updateBodyClip(){		
		
		vector point = simonvic.GetPosition() + vector.Forward * 2;
		
		vector from = simonvic.GetPosition();
		vector axis = vector.Up;
		float cosAngle = Math.Cos(m_time*Math.PI);
		float sinAngle = Math.Sin(m_time*Math.PI);
		
		
		vector offsetPos = from - point;
		vector result = vector.RotateAroundZero(offsetPos, axis, cosAngle, sinAngle) + from;
		
		
		m_bodyClipRaycast.from(from + "0 1.5 0").to(result + "0 1.5 0").ignore(simonvic).launch();
		
		
		if(bodyClipContactPos_enabled && m_bodyClipRaycast.hasHit())
			SDebug.spawnDebugDot(m_bodyClipRaycast.getContactPosition(), 0.05, 2);
		
		if(bodyClipAllContact_enabled){
			SDebug.spawnDebugDot(m_bodyClipRaycast.getContactPosition(), 0.02, 2);
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




/*
modded class Weapon_Base{
    override void EEFired(int muzzleType, int mode, string ammoType){
        super.EEFired(muzzleType, mode, ammoType);

        Magazine magazine = GetMagazine(GetCurrentMuzzle());

        if (GetGame().IsServer() || !GetGame().IsMultiplayer())
            SetHealth(GetMaxHealth()); // prevent weapon from deteriorating

        if (magazine){
            if (GetGame().IsServer() || !GetGame().IsMultiplayer())
                magazine.ServerSetAmmoMax(); // unlimited ammo
            
            if (GetGame().IsClient() || !GetGame().IsMultiplayer())
                magazine.LocalSetAmmoMax(); // update client side UI
        }
    }

    override bool IsJammed(){
        return false; // prevent jamming
    }
}
*/