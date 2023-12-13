#include "pch.h"
#include "CConstantBuffer.h"

#include "CDevice.h"

CConstantBuffer::CConstantBuffer(UINT _iRegisterNum) : m_registerNum(_iRegisterNum) { }
CConstantBuffer::~CConstantBuffer() { }

void CConstantBuffer::Create(UINT _iElementSize, UINT _iElementCount)
{
	m_elementSize = _iElementSize;
	m_elementCount = _iElementCount;

	UINT iBufferSize = m_elementSize * _iElementCount;

	// 16����Ʈ ���� �޸� ����
	assert(!(iBufferSize % 16));

	// ������� ����
	m_desc.ByteWidth = iBufferSize;
	m_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	m_desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	m_desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

	if (FAILED(DEVICE->CreateBuffer(&m_desc, nullptr, m_CB.GetAddressOf())))
	{
		assert(nullptr);
	}
}

void CConstantBuffer::SetData(void* _pSrc, UINT _iSize)
{
	// ũ�Ⱑ �������� ���� �����ʹ� ������� ũ��� ����.
	UINT size = _iSize;
	if (0 == _iSize)
	{
		size = m_elementSize * m_elementCount;
	}

	// ������� ũ�⺸�� �� ū �����Ͱ� �Է����� ���� ���
	assert(!(size > m_elementSize * m_elementCount));

	// SysMem -> GPU Mem
	D3D11_MAPPED_SUBRESOURCE tSubRes = {};
	if (!FAILED(CONTEXT->Map(m_CB.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &tSubRes)))
	{
		memcpy(tSubRes.pData, _pSrc, size);
		CONTEXT->Unmap(m_CB.Get(), 0);
	}
}

void CConstantBuffer::UpdateData()
{
	CONTEXT->VSSetConstantBuffers(m_registerNum, 1, m_CB.GetAddressOf());
	CONTEXT->HSSetConstantBuffers(m_registerNum, 1, m_CB.GetAddressOf());
	CONTEXT->DSSetConstantBuffers(m_registerNum, 1, m_CB.GetAddressOf());
	CONTEXT->GSSetConstantBuffers(m_registerNum, 1, m_CB.GetAddressOf());
	CONTEXT->PSSetConstantBuffers(m_registerNum, 1, m_CB.GetAddressOf());
}

void CConstantBuffer::UpdateData_CS()
{
	CONTEXT->CSSetConstantBuffers(m_registerNum, 1, m_CB.GetAddressOf());
}