#include "Animation/NodeLink.h"

namespace ma
{
	void NodeLink::Build(Skeleton* pSkeleton,Animation* pAnimation)
	{
		if (pSkeleton == NULL || pAnimation == NULL)
			return;

		UINT uBoneNumber = pSkeleton->GetBoneNumer();
		m_arrMapBoneInd.resize(uBoneNumber,InvalidID<BoneIndex>());
		for (UINT i = 0; i < uBoneNumber; ++i)
		{
			const char* pszBoneName = pSkeleton->GetBoneNameByIndex(i); 
			UINT uTransfTrackIndex = pAnimation->GetTransfTrackIndexByName(pszBoneName);
			m_arrMapBoneInd[i] = uTransfTrackIndex;
		}
	}

	BoneIndex NodeLink::MapNode(BoneIndex uBoneInd)
	{
		if (uBoneInd >= m_arrMapBoneInd.size() || uBoneInd < 0)
			return InvalidID<BoneIndex>();

		return m_arrMapBoneInd[uBoneInd];
	}
}