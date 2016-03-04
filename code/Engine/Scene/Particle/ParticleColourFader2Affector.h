#pragma once
#include "ParticleAffector.h"

namespace ma
{

class  ParticleColourFader2Affector : public ParticleAffector
{
public:
	ParticleColourFader2Affector(void);
	~ParticleColourFader2Affector(void);

	// ---------------------------------------------------------------------
	// Inherite from ParticleAffector
	// ---------------------------------------------------------------------
public:
	//! Affects a particle.
	virtual void Affect(Real now, Real timediff, LST_PARTICLE& lstParticles);

	// ---------------------------------------------------------------------
	// Self
	// ---------------------------------------------------------------------
public:

	/** Sets the colour adjustment to be made per second to particles. 
    @param red, green, blue, alpha
        Sets the adjustment to be made to each of the colour components per second. These
        values will be added to the colour of all particles every second, scaled over each frame
        for a smooth adjustment.
    */
    // ��0��ÿ�뽥���ٶȣ�RGBA��
	void SetColourAdder0(const Vector4& adder){mColourAdder0 = adder;}
	const Vector4& GetColourAdder0() const{return mColourAdder0;}

    // ��1��ÿ�뽥���ٶȣ�RGBA��
	void SetColourAdder1(const Vector4& adder){mColourAdder1 = adder;}
	const Vector4& GetColourAdder1() const{return mColourAdder1;}

    // ��С�ڸ�ʱ�̣������ٶ�ΪColourAdd0����֮�������ٶ�ΪColourAdd1
	void SetTimeChange(Real NewValue ){mTimeChange = NewValue;}
	Real GetTimeChange(void) const{return mTimeChange;}
private:
	Vector4 mColourAdder0, mColourAdder1;
	Real mTimeChange;
};

 RefPtr<ParticleColourFader2Affector> CreateColourFader2Affector();

}