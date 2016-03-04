#pragma once
#include "ParticleAffector.h"

namespace ma
{

//! Particle Affector for rotating particles about a point
class  ParticleRotationAffector : public ParticleAffector
{
public:
	ParticleRotationAffector();
	~ParticleRotationAffector(void);

	// ---------------------------------------------------------------------
	// Inherite from ParticleAffector
	// ---------------------------------------------------------------------
public:
	virtual void Init(SParticle* particlearray, uint32 count);

	//! Affects a particle.
	virtual void Affect(Real now, Real timediff, LST_PARTICLE& lstParticles);

	// ---------------------------------------------------------------------
	// Self
	// ---------------------------------------------------------------------
    // ��С����ʼ��תֵ(�Ƕ�)
    void SetMinStart(float minStart){mMinStart = Radian(Degree(minStart));}
    void SetMaxStart(float maxStart){mMaxStart = Radian(Degree(maxStart));}
	float GetMinStart() const{return mMinStart.valueDegrees();}
	float GetMaxStart() const{return mMaxStart.valueDegrees();}

    // ��С���ÿ����ת�ٶ�(�Ƕ�)
    void SetMinSpeed(float min){mMinSpeed = Radian(Degree(min));}
    void SetMaxSpeed(float max){mMaxSpeed = Radian(Degree(max));}
	float GetMinSpeed() const{return mMinSpeed.valueDegrees();}
	float GetMaxSpeed() const{return mMaxSpeed.valueDegrees();}
private:
	Radian mMinStart, mMaxStart;
	Radian mMinSpeed, mMaxSpeed;
};

 RefPtr<ParticleRotationAffector> CreateRotationAffector();
}