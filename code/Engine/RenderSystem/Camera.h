#ifndef  _Camera__H__
#define  _Camera__H__

#include "Engine/RenderSystem/RenderThread.h"

namespace ma
{
	class ENGINE_API Camera : public Component
	{
		DECL_OBJECT(Camera)

	public:
		//enum {NUM_PSSM = 4};

		Camera(GameObject* pGameObj);
	
		~Camera();

		virtual	void		UpdateTransform();

		void				LookAt(const Vector3& vEye,const Vector3& vAt,const Vector3& vUp);

		void				SetPerspective(float fFOV,float fAspect,float fNear,float fFar);

		NodeTransform		GetTransform() const;

		void				SetTransform(const NodeTransform& tsfCamra);

		const Matrix4x4&	GetViewMatrix() const {return m_matView;}

                                                                                                                                            		const Matrix4x4&	GetProjMatrix() const {return m_matProj;}
		
		Matrix4x4			GetViewProjMatrix() const {return GetViewMatrix() * GetProjMatrix();}
		
		float				GetNearClip() {return m_fNear;}

		float				GetFarClip() {return m_fFar;}

		float				GetFov() {return m_fFOV;}

		float				GetAspect() {return m_fAspect;}

		void				FitAABB(const AABB& aabb, float fMargin);

		Vector3				ProjToWorldNormal(const Vector2* pVec) const;

		Vector3				GetLookAtPos() {return m_vLookAtPt;}

		void				GetWorldRayCast(const Vector2& clientSize,const Vector2& mousePos, Vector3& worldOrig, Vector3& worldDir);

	protected:

		Vector2				GetNearPlaneSize() const;

	private:
		Matrix4x4		m_matView;
		Matrix4x4		m_matProj;

		float			m_fAspect;
		float			m_fFOV;	
		float			m_fNear;
		float			m_fFar;

		Vector3			m_vLookAtPt;
		Vector3			m_vEyePt;
		Vector3			m_vUpVector;

		//bool			m_bProjDirty;

		//bool			m_bOrtho;
		float			m_fHeight;
	};
}

#endif