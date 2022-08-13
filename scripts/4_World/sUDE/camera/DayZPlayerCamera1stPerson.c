modded class DayZPlayerCamera1stPerson {
	override void OnUpdate(float pDt, out DayZPlayerCameraResult pOutResult) {
		super.OnUpdate(pDt, pOutResult);
		pOutResult.m_fShootFromCamera = 0;
	}
}