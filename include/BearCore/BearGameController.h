#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearGameController :public BearObject
	{
		BEAR_OBJECT(BearGameController);
	protected:
		BearGameController(const BearName&type);
		~BearGameController();
	public:
		virtual void Destroy();
		virtual void Update(float time);
		virtual void Save(BearCore::BearOutputStream*stream) override;
		virtual void Load(const BearCore::BearInputStream*stream)override;

	};
	extern  BEARENGINE_API BearGameController *GGameController;
}