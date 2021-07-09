typedef array<ref SSpawnable> TSSpawnableAttachments;

class SSpawnable {
	
	protected string name;
	protected ref TSSpawnableAttachments attachments = new TSSpawnableAttachments;
	protected EntityAI entity = null;
	
	void SSpawnable(string itemName){
		name = itemName;
	}
	
	
	static SSpawnable build(string itemName){
		return new SSpawnable(itemName);
	}
	
	SSpawnable withAttachments(array<string> attachmentsName){
 		foreach(string attachmentName : attachmentsName){
			withAttachment(attachmentName);
		}
		return this;
	}
	
	SSpawnable withAttachment(string attachmentName){
		attachments.Insert(new SSpawnable(attachmentName));
		return this;
	}	
	
	SSpawnable withSpawnableAttachments(TSSpawnableAttachments newAttachments){
		foreach(SSpawnable attachment : newAttachments){
			withSpawnableAttachment(attachment);
		}
		return this;
	}
	
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
	
	SSpawnable withSpawnableAttachment(SSpawnable newAttachment){
		if(newAttachment != null) attachments.Insert(newAttachment);
		return this;
	}
	
	SSpawnable spawn(vector worldPosition){
		entity = SSpawner.spawn(name, worldPosition);
		foreach(SSpawnable attachment : attachments){
			attachment.spawn(entity.GetInventory());
		}
		return this;
	}
	
	SSpawnable spawn(GameInventory inventory){
		entity = SSpawner.spawn(name, inventory);
		foreach(SSpawnable attachment : attachments){
			attachment.spawn(entity.GetInventory());
		}
		return this;
	}

	EntityAI collect(){
		return entity;
	}
	
	SSpawnable collect(EntityAI entity){
		entity = this.entity;
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
	*	@return object created
	*/
	static EntityAI spawn(string itemName, vector worldPosition){
		return EntityAI.Cast(GetGame().CreateObject(itemName, worldPosition));
	}
	
	/**
	*	@return object created
	*/
	static EntityAI spawn(string itemName, GameInventory inventory){
		return inventory.CreateInInventory(itemName));
	}

}
