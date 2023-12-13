#include "pch.h"
#include "CStructuredBuffer.h"


#include "CDevice.h"

CStructuredBuffer::CStructuredBuffer() { }
CStructuredBuffer::~CStructuredBuffer() { }

void CStructuredBuffer::Create(UINT _iElementSize, UINT _iElementCount
	, SB_TYPE _Type, bool _bSysAccess, void* _pSysMem)
{
	m_SB = nullptr;
	m_SRV = nullptr;
	m_UAV = nullptr;

	m_SB_CPU_Read = nullptr;
	m_SB_CPU_Write = nullptr;

	m_SBType = _Type;
	m_isSysAccess = _bSysAccess;

	m_elementSize = _iElementSize;
	m_elementCount = _iElementCount;

	UINT iBufferSize = m_elementSize * _iElementCount;

	// 16����Ʈ ���� �޸� ����
	assert(!(iBufferSize % 16));

	// ������� ����
	m_desc.ByteWidth = iBufferSize;				// ���� ũ��
	m_desc.StructureByteStride = m_elementSize;	// ������ ����

	if (SB_TYPE::READ_ONLY == m_SBType)
	{
		m_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// Texture �������Ϳ� ���̵��ϱ� ���� �÷���
	}
	else if (SB_TYPE::READ_WRITE == m_SBType)
	{
		m_desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	}

	m_desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;	// ����ȭ ���� üũ
	m_desc.Usage = D3D11_USAGE_DEFAULT;
	m_desc.CPUAccessFlags = 0;

	if (nullptr == _pSysMem)
	{
		if (FAILED(DEVICE->CreateBuffer(&m_desc, nullptr, m_SB.GetAddressOf())))
		{
			assert(nullptr);
		}
	}
	else
	{
		D3D11_SUBRESOURCE_DATA tSubData = {};
		tSubData.pSysMem = _pSysMem;

		HRESULT hr = DEVICE->CreateBuffer(&m_desc, &tSubData, m_SB.GetAddressOf());
		if (hr)
		{
			assert(nullptr);
		}
	}


	// ShaderResourceView ����
	D3D11_SHADER_RESOURCE_VIEW_DESC	m_SRVDesc = {};

	m_SRVDesc.ViewDimension = D3D_SRV_DIMENSION_BUFFEREX;
	m_SRVDesc.BufferEx.NumElements = m_elementCount;

	if (FAILED(DEVICE->CreateShaderResourceView(m_SB.Get(), &m_SRVDesc, m_SRV.GetAddressOf())))
	{
		assert(nullptr);
	}

	if (SB_TYPE::READ_WRITE == m_SBType)
	{

		D3D11_UNORDERED_ACCESS_VIEW_DESC m_UABDesc = {};
		m_UABDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		m_UABDesc.Buffer.NumElements = m_elementCount;

		if (FAILED(DEVICE->CreateUnorderedAccessView(m_SB.Get(), &m_UABDesc, m_UAV.GetAddressOf())))
		{
			assert(nullptr);
		}
	}

	// CPU Access ���� ����
	if (m_isSysAccess)
	{
		m_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;

		// GPU -> CPU Read
		m_desc.Usage = D3D11_USAGE_DEFAULT;
		m_desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
		if (FAILED(DEVICE->CreateBuffer(&m_desc, nullptr, m_SB_CPU_Read.GetAddressOf())))
		{
			assert(nullptr);
		}

		// CPU -> GPU Write
		m_desc.Usage = D3D11_USAGE_DYNAMIC;
		m_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		if (FAILED(DEVICE->CreateBuffer(&m_desc, nullptr, m_SB_CPU_Write.GetAddressOf())))
		{
			assert(nullptr);
		}
	}
}

void CStructuredBuffer::SetData(void* _pSrc, UINT _iSize)
{
	if (nullptr == _pSrc)
		return;

	UINT iSize = _iSize;
	if (0 == iSize)
	{
		iSize = GetBufferSize();
	}

	// CPU -> CPU WriteBuffer
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(m_SB_CPU_Write.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSub);
	memcpy(tSub.pData, _pSrc, iSize);
	CONTEXT->Unmap(m_SB_CPU_Write.Get(), 0);

	// CPU WriteBuffer -> Main Buffer
	CONTEXT->CopyResource(m_SB.Get(), m_SB_CPU_Write.Get());
}

void CStructuredBuffer::GetData(void* _pDst)
{
	// Main Buffer -> CPU ReadBuffer
	CONTEXT->CopyResource(m_SB_CPU_Read.Get(), m_SB.Get());

	// CPU ReadBuffer -> CPU
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	CONTEXT->Map(m_SB_CPU_Read.Get(), 0, D3D11_MAP::D3D11_MAP_READ, 0, &tSub);
	memcpy(_pDst, tSub.pData, GetBufferSize());
	CONTEXT->Unmap(m_SB_CPU_Read.Get(), 0);
}

void CStructuredBuffer::UpdateData(UINT _iRegisterNum, UINT _iPipeLineStage)
{
	m_recentRegisterNum = _iRegisterNum;

	if (PIPELINE_STAGE::PS_VERTEX & _iPipeLineStage)
	{
		CONTEXT->VSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_HULL & _iPipeLineStage)
	{
		CONTEXT->HSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_DOMAIN & _iPipeLineStage)
	{
		CONTEXT->DSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_GEOMETRY & _iPipeLineStage)
	{
		CONTEXT->GSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}

	if (PIPELINE_STAGE::PS_PIXEL & _iPipeLineStage)
	{
		CONTEXT->PSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}
}

void CStructuredBuffer::UpdateData_CS(UINT _iRegisterNum, bool _IsShaderRes)
{
	m_recentRegisterNum = _iRegisterNum;

	if (_IsShaderRes)
	{
		CONTEXT->CSSetShaderResources(_iRegisterNum, 1, m_SRV.GetAddressOf());
	}
	else
	{
		UINT i = -1;
		CONTEXT->CSSetUnorderedAccessViews(_iRegisterNum, 1, m_UAV.GetAddressOf(), &i);
	}
}

void CStructuredBuffer::Clear()
{
	ID3D11ShaderResourceView* pSRV = nullptr;
	CONTEXT->VSSetShaderResources(m_recentRegisterNum, 1, &pSRV);
	CONTEXT->HSSetShaderResources(m_recentRegisterNum, 1, &pSRV);
	CONTEXT->DSSetShaderResources(m_recentRegisterNum, 1, &pSRV);
	CONTEXT->GSSetShaderResources(m_recentRegisterNum, 1, &pSRV);
	CONTEXT->PSSetShaderResources(m_recentRegisterNum, 1, &pSRV);
	CONTEXT->CSSetShaderResources(m_recentRegisterNum, 1, &pSRV);

}

void CStructuredBuffer::Clear_CS(bool _IsShaderRes)
{
	if (_IsShaderRes)
	{
		ID3D11ShaderResourceView* pSRV = nullptr;
		CONTEXT->CSSetShaderResources(m_recentRegisterNum, 1, &pSRV);
	}
	else
	{
		ID3D11UnorderedAccessView* pUAV = nullptr;
		UINT i = -1;
		CONTEXT->CSSetUnorderedAccessViews(m_recentRegisterNum, 1, &pUAV, &i);
	}
}