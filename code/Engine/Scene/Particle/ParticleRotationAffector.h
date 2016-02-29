#pragma once
#include "ParticleAffector.h"

namespace ma
{

//! Particle Affector for rotating particles about a point
class  CParticleRotationAffector : public CParticleAffector
{
public:
	CParticleRotationAffector();
	~CParticleRotationAffector(void);

	// ---------------------------------------------------------------------
	// Inherite from CParticleAffector
	// ---------------------------------------------------------------------
public:
	virtual void Init(SParticle* particlearray, uint32 count);

	//! Affects a particle.
	virtual void Affect(Real now, Real timediff, LST_PARTICLE& lstParticles);

	//! Get emitter type
	virtual E_PARTICLE_AFFECTOR_TYPE GetType() const { return EPAT_ROTATION; }

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

 RefPtr<CParticleRotationAffector> CreateRotationAffector();
}