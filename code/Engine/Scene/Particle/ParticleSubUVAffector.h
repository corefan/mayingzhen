#pragma once
#include "ParticleAffector.h"

namespace ma
{

//! Particle Affector for UV particles about a point
class  CParticleSubUVAffector : public CParticleAffector
{
public:
	CParticleSubUVAffector();
	~CParticleSubUVAffector(void);

	// ---------------------------------------------------------------------
	// Inherite from CParticleAffector
	// ---------------------------------------------------------------------
public:
	virtual void Init(SParticle* particlearray, uint32 count);

	//! Affects a particle.
	virtual void Affect(Real now, Real timediff, LST_PARTICLE& lstParticles);

	//! Get emitter type
	virtual E_PARTICLE_AFFECTOR_TYPE GetType() const { return EPAT_SUB_UV; }

	// ---------------------------------------------------------------------
	// Self
	// ---------------------------------------------------------------------
	void SetTile(int nXTile,int nYTile);

    // ��ͼ��U����ĸ�������(>=1)
	void SetXTile(int nXTile) {SetTile(nXTile,m_nXTile);}
    int GetXTile() const {return m_nXTile;}

    // ��ͼ��V����ĸ�������(>=1)
	void SetYTile(int nYTile) {SetTile(m_nXTile,nYTile);}
	int GetYTile() const {return m_nYTile;}

    // �������������߸��ѭ������(>=1)
    void SetCycles(int nCycles) {m_nCycles = nCycles;}
    int GetCycles() const {return m_nCycles;}

    // �Ƿ�Ҫ�̶����ӣ�Ĭ��false����Ϊtrue����ʾ�����Ӳ�����ʱ�����ȡ���е�һ��
    void SetFixedTile(bool bEnabled){m_bFixedTile = bEnabled;}
    bool GetFixedTile() const{return m_bFixedTile;}

    // ���Ӳ�ֵ(��Ϊtrue�������particlecpu����Ҫ��TEXTURE_BLEND��������Ч��)
    void SetTileBlend(bool b){m_bTileBlend = b;}
    bool GetTileBlend() const {return m_bTileBlend;}

    // �߸��ٶ��Ƿ�������ӵ��������ڣ�Ĭ��true����Ϊfalse����ʾʹ��FrameRate���п����߸��ٶ�
    void SetUseEmitterTime(bool b){m_bUseEmitterTime = b;}
    bool GetUseEmitterTime() const{return m_bUseEmitterTime;}

    // Ĭ��ÿ֡���0.033��
    void SetFrameRate(float fRate){m_fRate = fRate;}
    float GetFrameRate() const{return m_fRate;}

    // �߸����ʼ������Ĭ��Ϊ0��ʾÿ�ζ��Ǵ�0��ʼ����>0��ʾ�������ʼ��������ȡһ��ֵ
    void SetStartIndex(int nStartIndex);
    int GetStartIndex() const{return m_nStartIndex;}

private:
    uint32 WeightToBlend(float fWeight0,float fWeight1,float fWeight2,float fWeight3);

private:
    bool m_bTileBlend;
	int m_nXTile;
	int	m_nYTile;
	int m_nCycles;
    int m_nStartIndex;
    bool m_bFixedTile;
    bool m_bUseEmitterTime;
    float m_fRate;

	typedef vector<Rectangle> VEC_UV;
	VEC_UV m_vecTileUV;
};

 RefPtr<CParticleSubUVAffector> CreateSubUVAffector();
}