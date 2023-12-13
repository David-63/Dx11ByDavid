#include "pch.h"
#include "CComponent.h"

CComponent::CComponent(COMPONENT_TYPE _Type) : m_type(_Type) { }
CComponent::CComponent(const CComponent& _Other)
	: CEntity(_Other) , m_type(_Other.m_type)
{ }

CComponent::~CComponent() { }
