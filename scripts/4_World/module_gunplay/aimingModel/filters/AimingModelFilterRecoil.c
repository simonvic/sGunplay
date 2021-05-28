class AimingModelFilterRecoil : AimingModelFilterBase {
	
	override bool isActive(){
		return getAimingModel().getRecoil() != null;
	}
	
	override void onUpdate(float pDt, SDayZPlayerAimingModel pModel, int stanceIndex){
		//@todo what a mess... Either the recoil completely handles the model or just compute the values and apply them here
		float recoilOffsetMouseX;
		float recoilOffsetMouseY;
		float recoilOffsetHandsX;
		float recoilOffsetHandsY;
		getAimingModel().getRecoil().Update(pModel, recoilOffsetMouseX, recoilOffsetMouseY, recoilOffsetHandsX, recoilOffsetHandsY, pDt);
		pModel.m_fAimXHandsOffset += recoilOffsetHandsX;
		pModel.m_fAimYHandsOffset += recoilOffsetHandsY;
		pModel.m_fAimXCamOffset   -= recoilOffsetHandsX;
		pModel.m_fAimYCamOffset	  -= recoilOffsetHandsY;
		pModel.m_fAimXMouseShift  += recoilOffsetMouseX;
		pModel.m_fAimYMouseShift  += recoilOffsetMouseY;
	}
}