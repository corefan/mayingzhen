#ifndef  _AnimationDevice__H__
#define  _AnimationDevice__H__

namespace ma
{
	class ISkeleton;
	class IAnimationPlay;
	class IAnimationSet;

	class ANIMATION_API AnimationDevice : public IAnimationDevice
	{
	public:

		virtual ISkeleton*		CreateSkeleton();

		virtual IAnimationPlay*	CreateAnimationPlay();

		virtual	IAnimationSet*	CreateAnimationSet();
	};
}

#endif