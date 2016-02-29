#pragma once
#include "ParticleAffector.h"

namespace ma
{

class CParticleAlignAffector : public CParticleAffector
{
public:
	CParticleAlignAffector(void);
	~CParticleAlignAffector(void);

	// ---------------------------------------------------------------------
	// Inherite from CParticleAffector
	// ---------------------------------------------------------------------
public:
	//! Affects a particle.
	virtual void Affect(Real now, Real timediff, LST_PARTICLE& lstParticles);

	//! Get emitter type
	virtual E_PARTICLE_AFFECTOR_TYPE GetType() const { return EPAT_ALIGN; }

	// ---------------------------------------------------------------------
	// Self
	// ---------------------------------------------------------------------
public:
	/** Set resize. This attribute determines whether the size of the particle must be changed
		according to its alignment with the previous particle.
	*/
    // ���ӵĸ߶��Ƿ�Ҫ�������Ӿ�����е���ֵΪ\"������һ�����ӵĳ���\"+\"���ӳ���\"��
	void SetResize(bool bResize){mResize = bResize;}
	bool GetResize() const{return mResize;}

    // ���ӵ���С���ȣ�����ResizeΪtrueʱ��Ч��
	void SetMinAddLength(Real minAddLength){mMinAddLength = minAddLength;}
	Real GetMinAddLength() const{return mMinAddLength;}

    // ���ӵ���󳤶ȣ�����ResizeΪtrueʱ��Ч��
	void SetMaxAddLength(Real maxAddLength){mMaxAddLength = maxAddLength;}
	Real GetMaxAddLength() const{return mMaxAddLength;}

private:
	bool mResize;
	Real mMinAddLength;
	Real mMaxAddLength;
};

RefPtr<CParticleAlignAffector> CreateAlignAffector();
}