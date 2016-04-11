#pragma once
#include "ParticleAreaEmitter.h"

namespace ma
{

class  ParticleRingEmitter : public ParticleAreaEmitter
{
public:
	ParticleRingEmitter();
	~ParticleRingEmitter(void);

	//! Prepares an array with new particles to emitt into the system
	//! and returns how much new particles there are.
	virtual int Emitt(Real now, Real timeSinceLastCall, SParticle*& outArray, uint32 nFinalMaxParticles);


public:
	//! Set the innerRadio of the ring
    // �뾶�İٷֱ�[0.0~1.0],�Ӹ�ֵ��1.0ֱ�ӵİ뾶�Ż��������,����x��ʾx�뾶�ȣ�y��ʾy����İ뾶��
	virtual void SetInnerRatio( const Vector2& v ){mInnerRatio = v;}

	//! Get the innerRadio of the ring
	virtual const Vector2& GetInnerRatio() const{return mInnerRatio;}

private:
	Vector2 mInnerRatio;
};

//! Creates a ring particle emitter.
 RefPtr<ParticleRingEmitter> CreateRingEmitter();
}