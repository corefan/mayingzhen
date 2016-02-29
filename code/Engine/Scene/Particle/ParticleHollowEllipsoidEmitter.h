#pragma once
#include "ParticleEllipsoidEmitter.h"

namespace ma
{

class  CParticleHollowEllipsoidEmitter : public CParticleEllipsoidEmitter
{
public:
	CParticleHollowEllipsoidEmitter(void);
	~CParticleHollowEllipsoidEmitter(void);

	// ---------------------------------------------------------------------
	// Inherite from CParticleEllipsoidEmitter
	// ---------------------------------------------------------------------
public:
	//! Prepares an array with new particles to emitt into the system
	//! and returns how much new particles there are.
	virtual int Emitt(Real now, Real timeSinceLastCall, SParticle*& outArray, uint32 nFinalMaxParticles);

	//! Get emitter type
	virtual E_PARTICLE_EMITTER_TYPE GetType() const { return EPET_HOLLOW_ELLIPSOID; }

	// ---------------------------------------------------------------------
	// Self
	// ---------------------------------------------------------------------
public:
    // �뾶�İٷֱ�[0.0~1.0],�Ӹ�ֵ��1.0ֱ�ӵİ뾶�Ż��������,����x��ʾx�뾶�ȣ�y��ʾy����İ뾶��,z��ʾz����İ뾶��
	void SetInnerRatio(const Vector3& v){mInnerRatio = v;}
	const Vector3& GetInnerRatio() const{return mInnerRatio;}

protected:
	Vector3 mInnerRatio;
};

 RefPtr<CParticleHollowEllipsoidEmitter> CreateHollowEllipsoidEmitter();

}