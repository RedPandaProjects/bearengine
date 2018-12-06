#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearEngine:public BearObject
	{
		BEAR_OBJECT(BearEngine);
	protected:
		BearEngine(const BearName&type);
		~BearEngine();
	public:
		virtual void Loop();
		static void Create(const bchar*game);
		static void Close();
		virtual void Initialize(bchar**V,int32 C);
		virtual void Destroy();
	private:
		virtual void Update(float time) override;
		virtual void Save(BearCore::BearOutputStream*stream) override;
		virtual void Load(const BearCore::BearInputStream*stream) override;
	};
	BEARENGINE_API extern BearEngine*GEngine;
}