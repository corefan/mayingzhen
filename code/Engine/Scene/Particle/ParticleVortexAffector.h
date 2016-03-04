#pragma once
#include "ParticleAffector.h"

namespace ma
{

//! Particle Affector for attracting particles to a point
class  ParticleVortexAffector : public ParticleAffector
{
public:
	ParticleVortexAffector();
	~ParticleVortexAffector(void);

	// ---------------------------------------------------------------------
	// Inherite from ParticleAffector
	// ---------------------------------------------------------------------
public:
	//! Affects a particle.
	virtual void Affect(Real now, Real timediff, LST_PARTICLE& lstParticles);

	// ---------------------------------------------------------------------
	// Self
	// ---------------------------------------------------------------------
    // �����������ת
    virtual void SetRotateVector(const Vector3& vAxis){mRotateVector = vAxis;}
    virtual const Vector3& GetRotateVector() const{return mRotateVector;}

    // ÿ����ת�Ƕ�
    virtual void SetRotateSpeed(float f){mRotateSpeed = Radian(Degree(f));}
	virtual float GetRotateSpeed() const{return mRotateSpeed.valueDegrees();}
private:
	Vector3 mRotateVector;
	Radian mRotateSpeed;
};

 RefPtr<ParticleVortexAffector> CreateVortexAffector();

}