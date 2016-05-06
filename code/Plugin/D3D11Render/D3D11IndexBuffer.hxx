#include "D3D11IndexBuffer.h"

namespace ma
{


D3D11IndexBuffer::D3D11IndexBuffer()
{
	mD3D11IndexBuffer = NULL;
}

D3D11IndexBuffer::~D3D11IndexBuffer()
{
    SAFE_RELEASE(mD3D11IndexBuffer);
}


void* D3D11IndexBuffer::LockImpl(int iOffsetBytes, int iLockSize, LOCK LockFlag)
{
	D3D11_MAP D3DLock;

	if (LockFlag & LOCK_WRITE)
		D3DLock = D3D11_MAP_WRITE;

	if (LockFlag & LOCK_READONLY)
		D3DLock = D3D11_MAP_READ;

	if ((LockFlag & LOCK_DISCARD) && (m_Usage & USAGE_DYNAMIC))
		D3DLock = D3D11_MAP_WRITE_DISCARD;

	if (LockFlag & LOCK_NOOVERWRITE)
		D3DLock = D3D11_MAP_WRITE_NO_OVERWRITE;


	D3D11_MAPPED_SUBRESOURCE mappedData;
	mappedData.pData = 0;

	GetD3D11DxDeviveContext()->Map(mD3D11IndexBuffer, 0, D3DLock, 0,&mappedData);
	ASSERT(mappedData.pData);
	if (mappedData.pData == NULL)
	{
		LogError("Failed to map vertex buffer");
	}

	return mappedData.pData;
}

void D3D11IndexBuffer::UnlockImpl()
{
	GetD3D11DxDeviveContext()->Unmap(mD3D11IndexBuffer, 0);
}

void D3D11IndexBuffer::RT_StreamComplete()
{
	ASSERT(m_Size);

	D3D11_BUFFER_DESC bufferDesc;
	memset(&bufferDesc, 0, sizeof bufferDesc);
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = m_Usage & HBU_DYNAMIC ? D3D11_CPU_ACCESS_WRITE : 0;
	bufferDesc.Usage = m_Usage & HBU_DYNAMIC ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = (UINT)(m_Size);

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = m_pData;

	GetD3D11DxDevive()->CreateBuffer(&bufferDesc, m_pData ? &InitData : NULL, &mD3D11IndexBuffer);
	ASSERT(mD3D11IndexBuffer);
	if (mD3D11IndexBuffer == NULL)
	{
		LogError("CreateVertexBuffer failed");
		return;
	}

	if (0/*m_pData*/)
	{
		D3D11_BOX destBox;
		destBox.left = 0;
		destBox.right = m_Size;
		destBox.top = 0;
		destBox.bottom = 1;
		destBox.front = 0;
		destBox.back = 1;

		GetD3D11DxDeviveContext()->UpdateSubresource(mD3D11IndexBuffer, 0, &destBox, m_pData, 0, 0);

// 		void* pLockData = this->Lock(0,0,LOCK_WRITE);
// 
// 		memcpy(pLockData,m_pData,m_Size);
// 
// 		this->Unlock();

		if (m_bNeedFreeData)
		{
			FreeData();
		}
	}
}

ID3D11Buffer* D3D11IndexBuffer::GetD3DIndexBuffer() 
{
    return mD3D11IndexBuffer;
}

}
