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

	// 16바이트 단위 메모리 정렬
	assert(!(iBufferSize % 16));

	// 상수버퍼 생성
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
	// 크기가 지정되지 않은 데이터는 상수버퍼 크기로 본다.
	UINT size = _iSize;
	if (0 == _iSize)
	{
		size = m_elementSize * m_elementCount;
	}

	// 상수버퍼 크기보다 더 큰 데이터가 입력으로 들어온 경우
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