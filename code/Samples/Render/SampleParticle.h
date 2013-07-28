#ifndef _SampleParticle_H_
#define _SampleParticle_H_

namespace ma
{
	class ParticleEmitter;
	
	class SampleParticle : public Sample
	{
	public:
		SampleParticle();

		virtual void Init();

		virtual void Update();

		virtual void Render();

	private:

		ParticleEmitter* m_pEmitter;
	};
}


#endif
