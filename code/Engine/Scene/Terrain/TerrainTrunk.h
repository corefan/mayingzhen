#ifndef _TerrainTrunk_H_
#define _TerrainTrunk_H_


namespace ma
{
	class Terrain;
	class Camera;
	class TerrainRenderable;

	class TerrainTrunk : public RenderComponent
	{
	public:
		TerrainTrunk(Terrain* pTerrain);

		~TerrainTrunk();

		void Show(Camera* pCamera);

		bool Init(int i, int j);

		UINT GetLodIndex() const {return m_uLodIndex;}

		int GetIndexX() const{return m_nX;}
		
		int GetIndexY() const{return m_nY;}

		void SetLodParamDiv(float f);

		Terrain* GetTerrain() const {return m_pTerrain;}

		const AABB2D& GetUVAABB() const {return m_uvAABB;}

	private:
		void BuildLod();
		void BuildVertexBuffer();
		void BuildBody();
		void BuildBorder();
		void BuildSkirt();

		void BuildIndexBuffer();
		void BuildSkirtIndexBuffer();
		void BuildSkirtSideIB(RefPtr<IndexBuffer>& pSkirtIB,
			int nCellAmountSelf,int nCellAmountConnect,
			int nSelfStart,int nSelfStep);

		void UpdateRenderable();

		void AddToIBList( vector< vector<uint16> >& vecIBList, uint8 matID, uint16 triangle[3]);

		void ClearTempData();

	private:
		Terrain* m_pTerrain;

		int m_nX; 
		
		int m_nY;

		float m_fLodParam;

		UINT m_uLodIndex;

		typedef vector< RefPtr<TerrainRenderable> > VEC_RENDERABLE;

		struct SkitRenderable
		{
			RefPtr<TerrainRenderable> skirt[SideNum];
		};

		struct SkitIB
		{
			RefPtr<IndexBuffer> skirtIB[SideNum];
		};

		struct TERRAIN_LOD
		{
			VEC_RENDERABLE			m_vecBody; 
			VEC_RENDERABLE			m_vecBorder;

			vector<SkitRenderable>	m_vecSkirt;
			
		};
		vector<TERRAIN_LOD> m_vecLodRenderable;

		vector< set<uint8> > m_vecSetMatIDTemp;
		vector< vector<uint8> > m_vecTriangleMatID;

		vector< RefPtr<VertexBuffer> > m_vecVBTemp;
		vector< vector<TERRAIN_VERTEX> > m_vecVBDataTemp;

		vector< RefPtr<IndexBuffer> > m_vecIBTemp;
		vector< vector<uint16> > m_vecIBDataTemp;

		vector< vector<SkitIB> > m_vecSkirt;

		AABB2D m_uvAABB;

		friend class Terrain;
	};
}

#endif

