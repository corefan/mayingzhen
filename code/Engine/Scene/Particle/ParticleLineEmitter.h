#pragma once
#include "ParticleEmitter.h"

namespace ma
{

class  CParticleLineEmitter : public CParticleEmitter
{
public:
	CParticleLineEmitter(void);
	~CParticleLineEmitter(void);

	// ---------------------------------------------------------------------
	// Inherite from CParticleEmitter
	// ---------------------------------------------------------------------
public:
    virtual void Reset();

	//! Prepares an array with new particles to emitt into the system
	//! and returns how much new particles there are.
	virtual int Emitt(Real now, Real timeSinceLastCall, SParticle*& outArray, uint32 nFinalMaxParticles);

	//! Get emitter type
	virtual E_PARTICLE_EMITTER_TYPE GetType() const { return EPET_LINE; }

	// ---------------------------------------------------------------------
	// Self
	// ---------------------------------------------------------------------
public:
    // �߶ε���ֹλ��(���Ӵ��߶ε�Pos��Endֱ�Ӳ���)
	void SetEnd(const Vector3& vEnd){m_vEnd = vEnd;}
	const Vector3& GetEnd() const{return m_vEnd;}

    // ÿ�β���������ʼ�����С���루ȡֵ��Χ(0,�߶εĳ���]�������ӵ��������������߶εĳ��Ⱥ�����µ����ӵ��������ھ�Ϊ0��
	void SetMinIncrement(Real minIncrement){mMinIncrement = minIncrement;}
	Real GetMinIncrement() const{return mMinIncrement;}

    // ÿ�β���������ʼ��������루ȡֵ��Χ(0,�߶εĳ���]�������ӵ��������������߶εĳ��Ⱥ�����µ����ӵ��������ھ�Ϊ0��
	void SetMaxIncrement(Real maxIncrement){mMaxIncrement = maxIncrement;}
	Real GetMaxIncrement() const{return mMaxIncrement;}

    // �����߶ε����ƫ�ƴ�ֱ����
	void SetMaxDeviation(Real maxDeviation){mMaxDeviation = maxDeviation;}
	Real GetMaxDeviation() const{return mMaxDeviation;}
private:
	Vector3 m_vEnd;

	Real mMinIncrement;
	Real mMaxIncrement;
	Real mMaxDeviation;

	Vector3 mPerpendicular;
	Real mIncrement;
	Real mLength;
	bool mIncrementsLeft;
	bool mFirst;
};


// ---------------------------------------------------------------------
// Global Function
// ---------------------------------------------------------------------
 RefPtr<CParticleLineEmitter> CreateLineEmitter();

}