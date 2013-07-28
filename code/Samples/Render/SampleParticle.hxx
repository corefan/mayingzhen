#include "SampleParticle.h"


namespace ma
{
	SampleParticle::SampleParticle()
	{
		m_pEmitter = NULL;
	}


	void SampleParticle::Init()
	{
		Sample::Init();

		Vector3 vEyePos = Vector3(0, 20, 30);
		Vector3 VAtPos = Vector3(0,0,0); 
		Vector3 vUp = Vector3(0,1,0);
		m_pCamera->LookAt(vEyePos,VAtPos,vUp);

		m_pEmitter = ParticleEmitter::create("Particle/fire.particle");
		m_pEmitter->start();
	}


	void SampleParticle::Update()
	{
		Sample::Update();

		if (m_pEmitter)
		{	
			Matrix4x4 matWorld;
			MatrixTranslation(&matWorld,-20,0,0);

			m_pEmitter->update(GetTimer()->GetFrameDeltaTime(),matWorld);
		}
	}

	void SampleParticle::Render()
	{
		if (m_pEmitter)
		{
			m_pEmitter->draw(m_pCamera);
		}		
	}

}

