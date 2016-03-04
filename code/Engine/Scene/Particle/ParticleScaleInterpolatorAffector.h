#pragma once
#include "ParticleAffector.h"

namespace ma
{

class  ParticleScaleInterpolatorAffector : public ParticleAffector
{
	#define MAX_STAGES 6
public:
	ParticleScaleInterpolatorAffector(void);
	~ParticleScaleInterpolatorAffector(void);

	// ---------------------------------------------------------------------
	// Inherite from ParticleAffector
	// ---------------------------------------------------------------------
public:
	//! Affects a particle.
	virtual void Affect(Real now, Real timediff, LST_PARTICLE& lstParticles);

	// ---------------------------------------------------------------------
	// Self
	// ---------------------------------------------------------------------
    // ��index�׶ε����ţ�����,startSize���Ե�ǰ����ֵ��
	void SetScaleAdjust(size_t index, const Vector2& scale){ASSERT(index < MAX_STAGES); mScaleAdj[index] = scale;}
	const Vector2& GetScaleAdjust(size_t index) const{ASSERT(index < MAX_STAGES); return mScaleAdj[index];}

    // ʱ��ٷֱ�[0.0~1.0]
	void SetTimeAdjust(size_t index, Real time){ASSERT(index < MAX_STAGES); mTimeAdj[index] = time;}
	Real GetTimeAdjust(size_t index) const{ASSERT(index < MAX_STAGES); return mTimeAdj[index];}

    // �������ڷֳɶ��ٸ�ѭ��(>=1)
    void SetCycles(int nCycles) {m_nCycles = nCycles;}
    int GetCycles() const {return m_nCycles;}
private:
    int m_nCycles;
	Real mTimeAdj[MAX_STAGES];
	Vector2 mScaleAdj[MAX_STAGES];
};

 RefPtr<ParticleScaleInterpolatorAffector> CreateScaleInterpolatorAffector();
}