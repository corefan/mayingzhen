#include "HardwareBuffer.h"


namespace ma
{

	HardwareBuffer::HardwareBuffer()
	{
		m_Stride = 0;
		m_Size = 0;
		m_Usage = HBU_STATIC;
		m_pData = NULL;
		m_bShadowData = false;
		m_pLockedData = NULL;
	}

	HardwareBuffer::~HardwareBuffer()
	{
		FreeData();
	}

	void* HardwareBuffer::Lock(LOCK LockFlags)
	{
		if (m_pLockedData)
			return m_pLockedData;

		if (LockFlags == LOCK_DISCARD)
		{
			ASSERT((m_Usage&HBU_DYNAMIC) != 0);
		}
		m_pLockedData = LockImpl(0, m_Size, LockFlags);
		return m_pLockedData;
	}

	void HardwareBuffer::Unlock()
	{
		if (m_pLockedData)
		{
			UnlockImpl();

			m_pLockedData = NULL;
		}
	}

	void HardwareBuffer::SetData(uint8* pData,UINT nSize,int nStride,HBU_USAGE eUsage,bool bShadowData)
	{
		FreeData();

		m_bShadowData = bShadowData;
		m_Size = nSize;
		m_Stride = nStride;
		m_Usage = eUsage;

		if (pData)
		{
			m_pData = new uint8[nSize];
			memcpy(m_pData,pData,nSize);
		}
	}

	void HardwareBuffer::FreeData()
	{
		SAFE_DELETE_ARRAY(m_pData);
	}

}

