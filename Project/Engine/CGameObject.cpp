#include "pch.h"
#include "CGameObject.h"

#include "CComponent.h"
#include "CMeshRender.h"

#include "CScript.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"


CGameObject::CGameObject() { }

CGameObject::CGameObject(const CGameObject& _Other)
	: CEntity(_Other)
{
	// Component ����
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (_Other.m_arrCom[i])
		{
			AddComponent(_Other.m_arrCom[i]->Clone());
		}
	}

	// Script ����
	for (size_t i = 0; i < _Other.m_vecScript.size(); ++i)
	{
		AddComponent(_Other.m_vecScript[i]->Clone());
	}

	// �ڽ� ������Ʈ ����
	for (size_t i = 0; i < _Other.m_vecChild.size(); ++i)
	{
		AddChild(_Other.m_vecChild[i]->Clone());
	}
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(m_arrCom);
	Safe_Del_Vec(m_vecScript);
	Safe_Del_Vec(m_vecChild);
}

void CGameObject::begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->begin();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->begin();
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->begin();
	}
}

void CGameObject::tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->tick();
	}

	for (size_t i = 0; i < m_vecScript.size(); ++i)
	{
		m_vecScript[i]->tick();
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->tick();
	}
}

void CGameObject::finaltick()
{
	if (m_isLifeSpan)
	{
		m_curLifeTime += DT;
		if (m_lifeTime < m_curLifeTime)
		{
			DestroyObject(this);
		}
	}


	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::SCRIPT; ++i)
	{
		if (nullptr != m_arrCom[i])
			m_arrCom[i]->finaltick();
	}

	for (size_t i = 0; i < m_vecChild.size(); ++i)
	{
		m_vecChild[i]->finaltick();
	}

	// �Ҽ� ���̾ ���µ� finaltick �� ȣ��Ǿ���.
	assert(-1 != m_layerIdx);

	// ���̾� ���
	CLayer* pCurLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_layerIdx);
	pCurLayer->RegisterObject(this);
}

void CGameObject::render()
{
	if (nullptr != m_renderCom)
		m_renderCom->render();
}

void CGameObject::AddComponent(CComponent* _Component)
{
	_Component->m_owner = this;

	// ������Ʈ�� ��ũ��Ʈ�� ���
	if (COMPONENT_TYPE::SCRIPT == _Component->GetType())
	{
		m_vecScript.push_back((CScript*)_Component);
	}

	// ��ũ��Ʈ�� ������ �Ϲ� ������Ʈ�� ���
	else
	{
		// �̹� �����ϰ� �ִ� ������Ʈ�� ���
		assert(!m_arrCom[(UINT)_Component->GetType()]);

		m_arrCom[(UINT)_Component->GetType()] = _Component;

		// RenderComponent Ȯ��
		if (COMPONENT_TYPE::MESHRENDER <= _Component->GetType()
			&& _Component->GetType() <= COMPONENT_TYPE::DECAL)
		{
			assert(!m_renderCom);
			
			m_renderCom = dynamic_cast<CRenderComp*>(_Component);
		}
	}
}

void CGameObject::AddChild(CGameObject* _Object)
{
	if (_Object->m_parent)
	{
		// ���� �θ� ������ ���� ���� �� ����
		_Object->DisconnectFromParent();
	}

	else
	{
		// ���� �θ� ������, �Ҽ� ���̾�� �ֻ����θ� ��Ͽ��� ���ŵ� �� ����
		_Object->ChangeToChildType();
	}


	// �θ� �ڽ� ����
	_Object->m_parent = this;
	m_vecChild.push_back(_Object);
}


bool CGameObject::IsAncestor(CGameObject* _Target)
{
	CGameObject* pParent = m_parent;
	while (pParent)
	{
		if (pParent == _Target)
		{
			return true;
		}
		pParent = pParent->m_parent;
	}

	return false;
}

void CGameObject::DisconnectFromParent()
{
	if (!m_parent)
		return;

	vector<CGameObject*>::iterator iter = m_parent->m_vecChild.begin();
	for (; iter != m_parent->m_vecChild.end(); ++iter)
	{
		if (this == *iter)
		{
			m_parent->m_vecChild.erase(iter);
			m_parent = nullptr;
			return;
		}
	}

	assert(nullptr);
}

void CGameObject::ChangeToChildType()
{
	assert(-1 <= m_layerIdx && m_layerIdx < MAX_LAYER);

	if (-1 != m_layerIdx)
	{
		CLayer* pLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_layerIdx);
		pLayer->RemoveFromParentList(this);
	}
}

void CGameObject::AddParentList()
{
	CLayer* pLayer = CLevelMgr::GetInst()->GetCurLevel()->GetLayer(m_layerIdx);
	pLayer->AddParentList(this);
}
