#ifndef __CharaControlComponent_H__
#define __CharaControlComponent_H__

#include "Component.h"

namespace ma
{

	class FRAMWORK_API CharaControlComponent : public Component
	{
		DECL_OBJECT(CharaControlComponent)

	public:
		CharaControlComponent(GameObject* pGameObj);

		ICharaControll*		GetCharaControll() {return m_pCharaControll;}

		virtual void		Serialize(Serializer& sl, const char* pszLable = "CharaControlComponent");

		virtual	void		Render();

	private:
		ICharaControll*		m_pCharaControll;
	};

}

#endif