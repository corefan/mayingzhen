#ifndef  _Component__H__
#define  _Component__H__

namespace ma
{
	class SceneNode;
	class Camera;

	class Component : public Object
	{
		
	public:
		Component();

		virtual ~Component();

		DECL_OBJECT(Component);
		
		virtual	void	Update() {}
		virtual void	ParallelUpdate() {}
		virtual void	EndParallelUpdate() {}

		virtual	void	OnAddToSceneNode(SceneNode* pGameObj);

		virtual	void	OnRemoveFromSceneNode(SceneNode* pGameObj);

		virtual void	MarkDirty() {}

		SceneNode*		GetSceneNode();

	protected:
		SceneNode*		m_pSceneNode;
	};

}



#endif // _Component__H__