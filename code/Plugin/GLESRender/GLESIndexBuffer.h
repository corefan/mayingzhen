#ifndef  _GLESIndexBuffer__H__
#define  _GLESIndexBuffer__H__


#include "GLESMapping.h"
#include "Engine/RenderSystem/IndexBuffer.h"

namespace ma
{

	class GLESRENDER_API GLESIndexBuffer : public IndexBuffer
	{

	public:
		GLESIndexBuffer(void* Data = NULL, int size = 0, INDEX_TYPE eIndexType = INDEX_TYPE_U16, USAGE Usgae = USAGE_STATIC);
		
		~GLESIndexBuffer();

		virtual void* Lock(int iOffsetBytes, int uiLockSize, LOCK LockFlags);
		
		virtual void Unlock();

		virtual void	Active();

		GLuint	GetIndexBuffer(){return m_hIndexBuffer;}

	protected:
		GLuint m_hIndexBuffer;
	};

}

#endif