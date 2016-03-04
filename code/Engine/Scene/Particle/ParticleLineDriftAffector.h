#pragma once
#include "ParticleAffector.h"

namespace ma
{

class ParticleLineDriftAffector : public ParticleAffector
{
public:
	ParticleLineDriftAffector(void);
	~ParticleLineDriftAffector(void);

	// ---------------------------------------------------------------------
	// Inherite from ParticleAffector
	// ---------------------------------------------------------------------
public:
    virtual void Reset();

	//! Affects a particle.
	virtual void Affect(Real now, Real timediff, LST_PARTICLE& lstParticles);

	// ---------------------------------------------------------------------
	// Self
	// ---------------------------------------------------------------------
public:
    // �����߶ε����ƫ��ֵ,���ֵ���ٳ���ƫ��ǿ��Drift
	void SetMaxDeviation(Real maxDeviation){mMaxDeviation = maxDeviation;}
	Real GetMaxDeviation() const{return mMaxDeviation;}

    // �߶ε��յ�����
	void SetEnd(const Vector3& end){mEnd = end;}
	const Vector3& GetEnd() const{return mEnd;}

    // ���ø���ʱ�������룩,Ĭ��0.1��Ϊ�˽�ԼЧ�ʲ���Ҫÿ֡������
	void SetTimeStep(Real timeStep){mTimeStep = timeStep;}
	Real GetTimeStep() const{return mTimeStep;}

    // ƫ��ǿ��[0.0~1.0]��Ϊ0ʱƫ����Ч
	void SetDrift(Real drift){mDrift = drift;mOneMinusDrift = 1.f - drift;}
	Real GetDrift() const{return mDrift;}
private:
	Real mMaxDeviation;
	Vector3 mEnd;
	Real mTimeStep;
	Real mDrift;

	Real mOneMinusDrift;
	bool mUpdate;
	bool mFirst;
	Real mTimeSinceLastUpdate;
};

RefPtr<ParticleLineDriftAffector> CreateLineDriftAffector();
}
