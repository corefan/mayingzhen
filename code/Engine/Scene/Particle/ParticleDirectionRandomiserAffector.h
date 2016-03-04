#pragma once
#include "ParticleAffector.h"

namespace ma
{
 /** This class defines a ParticleAffector which applies randomness to the movement of the particles.
	@remarks
		This affector (see ParticleAffector) applies randomness to the movement of the particles by
		changing the direction vectors.
	@par
		The most important parameter to control the effect is randomness. It controls the range in which changes
		are applied to each axis of the direction vector.
		The parameter scope can be used to limit the effect to a certain percentage of the particles.
	*/
class  ParticleDirectionRandomiserAffector : public ParticleAffector
{
public:
	ParticleDirectionRandomiserAffector(void);
	~ParticleDirectionRandomiserAffector(void);

	// ---------------------------------------------------------------------
	// Inherite from ParticleAffector
	// ---------------------------------------------------------------------
public:
	//! Affects a particle.
	virtual void Affect(Real now, Real timediff, LST_PARTICLE& lstParticles);

	// ---------------------------------------------------------------------
	// Self
	// ---------------------------------------------------------------------
	/** Sets the randomness to apply to the particles in a system. */
    // ����������ֵԽ�󣬶�������Խ��
	void SetRandomness(Real force){mRandomness = force;}

	/** Sets the scope (percentage of particles which are randomised). */
    // �������������İٷֱ�[0.0,1.0]��Ϊ0��ʾû�����Ӷ�����Ϊ0.5��ʾ��50%���������ڶ�����Ϊ1��ʾ�������Ӷ���
	void SetScope(Real force){mScope = force;}

    // �ǲ���Ҫ�����ٶ���ֵ���䣬ֻ�Ƿ��򶶶�
	/** Set flag which detemines whether particle speed is changed. */
	void SetKeepVelocity(bool keepVelocity){mKeepVelocity = keepVelocity;}

	/** Gets the randomness to apply to the particles in a system. */
	Real GetRandomness(void) const{return mRandomness;}

	/** Gets the scope (percentage of particles which are randomised). */
	Real GetScope(void) const{return mScope;}

	/** Gets flag which detemines whether particle speed is changed. */
	bool GetKeepVelocity(void) const{return mKeepVelocity;}
protected:
	Real mRandomness;
	Real mScope;
	bool mKeepVelocity;
};

 RefPtr<ParticleDirectionRandomiserAffector> CreateDirectionRandomiserAffector();
}