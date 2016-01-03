#ifndef __CameraController_H__
#define __CameraController_H__


namespace ma
{

	class CameraController
	{

	public:
		CameraController(Camera* pCamObj);

		void		UpdateInput();		

		void		SetMoveStep(float fMoveStep) {m_fMoveStep = fMoveStep;}

		float		GetMoveStep() const {return m_fMoveStep;}

		void		SetCamera(Camera* pCamera) {m_pCamera = pCamera;}

		void		ResetCamera();

	private:

		void		RotateMoveCamera();

		void		MoveCamera();

		void		RotateCamera();

		void		ZoomCamera(float fDeltaZoom);

		void		UpdateTarget();

		void		UpdateTargetDis();

		Vector2		GetMouseProjVec();

		Vector3		ProjToWorldNormal(const Vector2* pVec,float fDepth); 


	private:
		float			m_fMoveStep;

		Vector3			m_vTarget;	

		float			m_fTargetDis;

		Camera*			m_pCamera;
	};
}

#endif 



