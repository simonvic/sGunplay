typedef array<ref SSpawnable> TSSpawnableAttachments;

class SSpawnable {
	
	protected string name;
	protected ref TSSpawnableAttachments attachments = new TSSpawnableAttachments;
	protected EntityAI entity = null;
	
	void SSpawnable(string itemName){
		name = itemName;
	}
	
	/**
	*	@brief Get an instance of a SSpawnable
	*	 @return new instance
	*/
	static SSpawnable build(string itemName){
		return new SSpawnable(itemName);
	}
	
	/**
	*	@brief Add attachments
	*	 @param attachmentsName \p array<string> - List of attachments names
	*	 @code 
	*	 	SSpawnable.build("M4A1").withAttachments({
	*	 		"M4_Suppressor",
	*	 		"M4_OEBttstck",
	*	 		"M4_RISHndgrd"
	*	 	})
	*/
	SSpawnable withAttachments(array<string> attachmentsName){
 		foreach(string attachmentName : attachmentsName){
			withAttachment(attachmentName);
		}
		return this;
	}
	
	/**
	*	@brief Add attachment
	*	 @param attachmentName \p string - Name of attachment
	*	 @code 
	*	 	SSpawnable.build("M4A1").withAttachments("M4_Suppressor");
	*/
	SSpawnable withAttachment(string attachmentName){
		attachments.Insert(new SSpawnable(attachmentName));
		return this;
	}	
	
	/**
	*	@brief Add SSpawnable attachments
	*	 @param newAttachments \p TSSpawnableAttachments - List of SSpawnable attachments
	*/
	SSpawnable withSpawnableAttachments(TSSpawnableAttachments newAttachments){
		foreach(SSpawnable attachment : newAttachments){
			withSpawnableAttachment(attachment);
		}
		return this;
	}
	
	/**
	*	@brief Add SSpawnable attachments
	*	 @param newAttachments \p TSSpawnableAttachments - List of SSpawnable attachments
	*	 @code 
	*	 	SSpawnable.build("MP5K").withAttachments({
	*	 		"MP5_Compensator",
	*	 		"MP5k_StockBttstck",
	*	 		"MP5_RailHndgrd"
	*	 	}).withSpawnableAttachments(
	*	 		(new SSpawnable("ReflexOptic")).withAttachment("Battery9V"),
	*	 		(new SSpawnable("UniversalLight")).withAttachment("Battery9V")));
	*/
	SSpawnable withSpawnableAttachments(SSpawnable a0, SSpawnable a1 = null, SSpawnable a2 = null, SSpawnable a3 = null, SSpawnable a4 = null, SSpawnable a5 = null, SSpawnable a6 = null, SSpawnable a7 = null, SSpawnable a8 = null, SSpawnable a9 = null){
		withSpawnableAttachment(a0);
		withSpawnableAttachment(a1);
		withSpawnableAttachment(a2);
		withSpawnableAttachment(a3);
		withSpawnableAttachment(a4);
		withSpawnableAttachment(a5);
		withSpawnableAttachment(a6);
		withSpawnableAttachment(a7);
		withSpawnableAttachment(a8);
		withSpawnableAttachment(a9);
		return this;
	}
	
	/**
	*	@brief Add SSpawnable attachment
	*	 @param newAttachment \p SSpawnable - SSpawnable attachment
	*/
	SSpawnable withSpawnableAttachment(SSpawnable newAttachment){
		if(newAttachment != null) attachments.Insert(newAttachment);
		return this;
	}
	
	/**
	*	@brief Spawn the SSpawnable at the given world coordinates
	*	 @param worldPosition \p vector - World Position coordinates
	*/
	SSpawnable spawn(vector worldPosition){
		entity = SSpawner.spawn(name, worldPosition);
		foreach(SSpawnable attachment : attachments){
			attachment.spawn(entity.GetInventory());
		}
		return this;
	}

	/**
	*	@brief Spawn the SSpawnable in the given inventory
	*	 @param inventory \p GameInventory - Inventory to spawn the spawnables in
	*/
	SSpawnable spawn(GameInventory inventory){
		entity = SSpawner.spawn(name, inventory);
		foreach(SSpawnable attachment : attachments){
			attachment.spawn(entity.GetInventory());
		}
		return this;
	}

	/**
	*	@brief Collect the spawned entity
	*	 @return EntityAI - spawned entity (null, if not spawned)
	*/
	EntityAI collect(){
		return entity;
	}
	
	/**
	*	@brief Collect the spawned entity
	*	 @param EntityAI [out] - spawned entity (null, if not spawned)
	*/
	SSpawnable collect(EntityAI outEntity){
		outEntity = entity;
		return this;
	}
	
	string getName(){
		return name;
	}
	
	TSSpawnableAttachments getAttachments(){
		return attachments;
	}
	
	string toString(){
		return string.Format("%1 = { name=%2 | attachments=%3 | entity=%4}",
			this, getName(), attachmentsToString(), entity);
	}
	
	private string attachmentsToString(){
		string output = "[";
		
		foreach(SSpawnable a : attachments){
			output += a.toString() + " , \n";
		}
		
		return output + "]";
	}
	
	void debugPrint(int level = 0){
		SLog.d(this, getName(), level);
		debugPrintAttachments(level + 2);		
	}
	
	void debugPrintAttachments(int level = 2){
		foreach(SSpawnable a : attachments){
			a.debugPrint(level);
		}
	}
	
}

class SSpawner{
	
	/**
	*	@brief Spawn the item in the world
	*	 @param itemName \p string - Name of the item
	*	 @param worldPosition \p vector - World Position coordinates
	*	 @return object created (null if not created)
	*/
	static EntityAI spawn(string itemName, vector worldPosition){
		return EntityAI.Cast(GetGame().CreateObject(itemName, worldPosition));
	}
	
	/**
	*	@brief Spawn the item in the given inventory
	*	 @param itemName \p string - Name of the item
	*	 @param inventory \p GameInvenory - inventory to spawn the object in
	*	 @return object created (null if not created)
	*/
	static EntityAI spawn(string itemName, GameInventory inventory){
		return inventory.CreateInInventory(itemName));
	}

}
