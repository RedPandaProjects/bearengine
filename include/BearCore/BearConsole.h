#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearConsole :public BearObject
	{
		BEAR_OBJECT(BearConsole);
		BearConsole(const BearName&type);
		~BearConsole();
	public:
		virtual void Save(BearCore::BearOutputStream*stream);
		virtual void Load(const BearCore::BearInputStream*stream);
		virtual void Destroy();
		virtual void Update(float time);
	private:
		BearRenderText* m_text;
		BearSprite*m_box;
		BearSprite*m_list_box;
	private:
		bool Show;
	};
	extern BearConsole * GConsole;
}