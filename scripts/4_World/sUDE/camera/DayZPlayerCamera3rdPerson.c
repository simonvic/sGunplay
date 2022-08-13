modded class DayZPlayerCamera3rdPerson {
	override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult) {
		super.OnUpdate(pDt, pOutResult);
		pOutResult.m_fShootFromCamera = 0;
	}
}