#pragma once

class CGameObjectEx;
class CEditorMgr : public CSingleton<CEditorMgr>
{
	SINGLE(CEditorMgr);
private:
	vector<CGameObjectEx*>	m_vecEditorObj;

	CGameObjectEx* m_DebugShape[(UINT)SHAPE_TYPE::END];
	vector<tDebugShapeInfo> m_DebugShapeInfo;

public:
	void init();
	void progress();

private:
	void tick();
	void render();
};

