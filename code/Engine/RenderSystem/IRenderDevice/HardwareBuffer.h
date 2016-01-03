#ifndef  _HardwareBuffer__H__
#define  _HardwareBuffer__H__

#include "Engine/RenderSystem/IRenderDevice/RenderDefine.h"

namespace ma
{
	class HardwareBuffer : public Referenced
	{
	public:
		HardwareBuffer();

		virtual ~HardwareBuffer();

		virtual void*	Lock(int iOffsetBytes, int iLockSize, LOCK LockFlags) = 0;

		virtual void    Unlock() = 0;

		virtual void	RT_StreamComplete() = 0;

		int             GetSize() const {return m_Size;} 

		USAGE           GetUsage() const {return m_Usage;}

		int				GetStride() const {return m_Stride;} 

		UINT			GetNumber() const {return m_Size / m_Stride;}

		void*			GetData() const {return m_pData;}

		void			SetData(uint8* pData,UINT nSize,int nStride, USAGE eUsage = USAGE_STATIC);

		void			FreeData();

	protected:
		int				m_Stride;
		UINT            m_Size;
		USAGE           m_Usage;
		uint8*			m_pData;
		bool			m_bNeedFreeData;
	};
}

#endif
