#pragma once
#include "Particle.h"

namespace ma
{

//! Types of built in particle emitters
enum E_PARTICLE_EMITTER_TYPE
{
	EPET_POINT = 0,
	EPET_BOX,
	EPET_CYLINDER,
	EPET_MESH_VERTEX,
	EPET_RING,
	EPET_ELLIPSOID,
	EPET_HOLLOW_ELLIPSOID,
	EPET_LINE,
    EPET_MESH_SURFACE,
	EPET_COUNT
};

struct MESHEMITTER_VERTEX
{
    Vector3 pos;
    Vector3 normal;

    MESHEMITTER_VERTEX(){pos = Vector3::ZERO, normal = Vector3::UNIT_Z;}
    MESHEMITTER_VERTEX(const Vector3& _pos, const Vector3& _normal):pos(_pos),normal(_normal){}
};

//! A particle emitter for using with particle systems.
/** A Particle emitter emitts new particles into a particle system.
*/
class  CParticleEmitter : public Serializable
{

public:
	CParticleEmitter();
	virtual ~CParticleEmitter(void);

	void RegisterAttribute();

    virtual void Reset();

	//! Prepares an array with new particles to emitt into the system
	/** \param now Current time.
	\param timeSinceLastCall Time elapsed since last call, in milliseconds.
	\param outArray Pointer which will point to the array with the new
	particles to add into the system.
	\return Amount of new particles in the array. Can be 0. */
	virtual int Emitt(Real now, Real timeSinceLastCall, SParticle*& outArray, uint32 nFinalMaxParticles) = 0;

	//! Set the center of the emitter
    // ������λ��
	virtual void SetPos( const Vector3& pos ){mPos = pos;}
    virtual const Vector3& GetPos() const{return mPos;}

	//! Set direction the emitter emits particles
    // ��ʼ���䷽�򣨵�λ������
	virtual void SetDirection( const Vector3& newDirection ){mDirection = newDirection;mDirection.normalise();}
    virtual const Vector3& GetDirection() const{return mDirection;}

	/** Sets the emission rate for this emitter.
    @remarks
        This method tells the emitter how many particles per second should be emitted. The emitter
        subclass does not have to emit these in a continuous burst - this is a relative parameter
        and the emitter may choose to emit all of the second's worth of particles every half-second
        for example. This is controlled by the emitter's getEmissionCount method.
    @par
        Also, if the ParticleSystem's particle quota is exceeded, not all the particles requested
        may be actually emitted.
    @param
        particlesPerSecond The number of particles to be emitted every second.
    */
    // ����Ƶ�ʣ���ÿ�뷢�����ӵ�����
	virtual void SetEmissionRate(Real particlesPerSecond){mEmissionRate = particlesPerSecond;}
	/** Returns the emission rate set for this emitter. */
	virtual Real GetEmissionRate(void) const{return mEmissionRate;}

	//! Set minimum starting color for particles
    // ��ʼ��С��ɫ(��ɫ���MinStartColor��MaxStartColor��ȡ���ֵ)
	virtual void SetMinStartColor( const ColourValue& color ){mMinStartColor = color;}
    //! Get the minimum starting color for particles
    virtual const ColourValue& GetMinStartColor() const{return mMinStartColor;}

	//! Set maximum starting color for particles
    // ��ʼ�����ɫ(��ɫ���MinStartColor��MaxStartColor��ȡ���ֵ)
	virtual void SetMaxStartColor( const ColourValue& color ){mMaxStartColor = color;}
    //! Get the maximum starting color for particles
    virtual const ColourValue& GetMaxStartColor() const{return mMaxStartColor;}

	//! Set the maximum starting size for particles
    // ���ӳ�ʼ��С(min~max֮��ȡ���ֵ)
	virtual void SetMaxStartSize( const FloatSize& size ){mMaxStartSize = size;}
	//! Set the minimum starting size for particles
	virtual void SetMinStartSize( const FloatSize& size ){mMinStartSize = size;}
    //! Get the maximum starting size for particles
    virtual const FloatSize& GetMaxStartSize() const{return mMaxStartSize;}
    //! Get the minimum starting size for particles
    virtual const FloatSize& GetMinStartSize() const{return mMinStartSize;}

    // ���������Ƕ�(������䷽�����ʼ���䷽��Direction֮��ļн�
	virtual void SetMaxAngleDegrees(const Vec3i& nMaxAngleDegree){mMaxAngleDegrees = nMaxAngleDegree;}
    virtual const Vec3i& GetMaxAngleDegrees() const{return mMaxAngleDegrees;}

    // ��������ʱ��
	virtual void SetMinLifeTime(Real time){mMinLifeTime = time;}
	virtual void SetMaxLifeTime(Real time){mMaxLifeTime = time;}
    virtual Real GetMinLifeTime() const{return mMinLifeTime;}
    virtual Real GetMaxLifeTime() const{return mMaxLifeTime;}

    // ��ʼ�����ٶȣ�min~max֮��ȡ���ֵ��
    virtual void SetMinVelocity(Real f){mMinVelocity = f;}
    virtual void SetMaxVelocity(Real f){mMaxVelocity = f;}
	virtual Real GetMinVelocity() const{return mMinVelocity;}
	virtual Real GetMaxVelocity() const{return mMaxVelocity;}

    // ��ʼ�����ʱ���(��)
	//! Sets the 'start time' of this emitter.
    virtual void SetStartTime(Real startTime);

    /** Gets the start time of the emitter. */
	// Ĭ��Ϊ0
	virtual Real GetStartTime(void) const{return mStartTime;}

    // �������ʱ��(��)��Ĭ��Ϊ0����ʾ����ʱ�����޳�
	/** Sets the duration of the emitter.*/
    virtual void SetDuration(Real duration);

    /** Gets the duration of the emitter from when it is created or re-enabled. */
	virtual Real GetDuration(void) const{return mDuration;}

	/** Sets the time between repeats of the emitter.*/
	// ����ѭ��֮����ӳ�ʱ��(��)��Ĭ��0��ʾ��ѭ��
    virtual void SetRepeatDelay(Real duration);

    /** Gets the duration of the emitter from when it is created or re-enabled. */
	virtual Real GetRepeatDelay(void) const{return mRepeatDelay;}

	struct BURST : public Referenced
	{
		Real fTime;//duration�ڵ�time������fTime��Χ[0~duration]
		bool bToEmit;//�ڲ�ʹ��
		uint32 nNumParticles;//ÿ���������������

		CParticleEmitter* pEmitter;
		BURST():fTime(0),bToEmit(true),nNumParticles(0),pEmitter(NULL){}
	};

    // time�����ʱ��㣨duration�ڵ�ʱ��㣬����Time��Χ[0~duration]��
    // nNumParticles���ʱ���һ���������������������
	virtual BURST* AddBurst(Real time, uint32 nNumParticles);
	virtual uint32 GetNumBursts() const;
	virtual void ClearBursts();
	virtual void RemoveBurstByIndex(uint32 nIndex);
	virtual BURST* GetBurstByIndex(uint32 nIndex);
	virtual void RemoveBurst(BURST* pBurst);

	//! Get emitter type
	virtual E_PARTICLE_EMITTER_TYPE GetType() const = 0;

    virtual bool GetEmitting(float fNow) const;

    virtual void SetEnabled(bool enabled) { m_bEnabled = enabled; }
    virtual bool GetEnabled() const { return m_bEnabled; }

    void _SetLodEnabled(bool b){m_bLodEnabled = b;}
protected:
	void GenEmissionVelocity(IN OUT SParticle& p);
	void GenEmission(IN OUT SParticle& p);
	uint32 GenConstantEmissionCount(Real now, Real timeElapsed, uint32 nFinalMaxParticles);
	
	void SetInternalEnable(bool bEnable);

	/** Internal method for initialising the duration & repeat of an emitter. */
	void InitDurationRepeat(void);
protected:
    bool m_bEnabled;
    bool m_bLodEnabled;
	Vector3 mPos;
	Vector3 mDirection;
	FloatSize mMaxStartSize, mMinStartSize;
	
	/// Rate in particles per second at which this emitter wishes to emit particles
	Real mEmissionRate;

	ColourValue mMinStartColor, mMaxStartColor;
	Real mMinLifeTime, mMaxLifeTime;

	Real mMinVelocity, mMaxVelocity;

	Vec3i mMaxAngleDegrees;

	/// Start time (in seconds from start of first call to ParticleSystem to update)
	Real mStartTime, mStartTimeRemain;
	
	/// Maximum length of time the emitter will run for (0 = forever)
	Real mDuration;

	/// Current duration remainder
	Real mDurationRemain;

	/// Time between each repeat(0 = nerver)
	Real mRepeatDelay;

	/// Repeat delay left
	Real mRepeatDelayRemain;

	/// Whether this emitter is currently enabled (defaults to true)
	bool mInternalEnabled;

	// Fractions of particles wanted to be emitted last time
	Real mRemainder;

	typedef vector<SParticle> VEC_PARTICLE;
	VEC_PARTICLE mParticles;

	typedef deque<RefPtr<BURST> > DEQ_BURST;
	DEQ_BURST mBursts;


};

}