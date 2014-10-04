#ifndef  _Camera__H__
#define  _Camera__H__

namespace ma
{
	class RENDER_API Camera : public Component
	{
		DECL_OBJECT(Camera)

	public:

		Camera(SceneNode* pGameObj);
	
		~Camera();

		void				SetPerspective(float fFOV,float fAspect,float fNear,float fFar);

		const Matrix4&		GetMatView();

		const Matrix4&		GetMatProj();

		const Matrix4&		GetMatViewProj();
		
		float				GetNearClip() {return m_fNear;}

		float				GetFarClip() {return m_fFar;}

		float				GetFov() {return m_fFOV;}

		float				GetAspect() {return m_fAspect;}

		void				FitAABB(const AABB& aabb, float fMargin);

		Vector3				ProjToWorldNormal(const Vector2* pVec,float fDepth);

		void				AdjustPlanes(const AABB& aabbWorld);

		void				GetWorldRayCast(const Vector2& clientSize,const Vector2& mousePos, Vector3& worldOrig, Vector3& worldDir);

		const Frustum&		GetFrustum() const {return m_frustum;}

		virtual void		Serialize(Serializer& sl, const char* pszLable = "Camera");

	protected:

		Vector2				GetNearPlaneSize() const;

		void				UpdateMatView();

	private:
		MatViewProj			m_matViewProj;

		bool				m_bMatViewDirty;

		float				m_fAspect;
		float				m_fFOV;	
		float				m_fNear;
		float				m_fFar;

		float				m_fNearMin;		

		Frustum				m_frustum;
	};

	DeclareRefPtr(Camera);
}

#endif