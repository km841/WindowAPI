#include "Common.h"
#include "yaComponent.h"

namespace ya
{
	class Animator
		: public Component
	{
	public:
		Animator();
		virtual ~Animator();

	private:
		virtual void Tick();
		virtual void Render(HDC hdc);
	};


}