#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearConsole :public BearObject
	{
		BEAR_OBJECT(BearConsole);
		BearConsole(const BearName&type);
		~BearConsole();
	
#ifdef BEAR_ENGINE_EXPORTS
	public:
#endif
		void CallStack();
		virtual void Save(BearCore::BearOutputStream*stream);
		virtual void Load(const BearCore::BearInputStream*stream);
		virtual void Destroy();
		virtual void Update(float time);
	public:
		bool Execute(const bchar*command);
		void PushCommand(BearConsoleCommand*);
	private:
		BearRenderText* m_text;
		BearRenderText* m_text_in;

		BearSprite*m_box;
		BearSprite*m_list_box;
		float m_timer_cursor;
		BearCore::BearVector<BearConsoleCommand*> m_commands;
	private:
		bool Show;
	private:
		bool ExecuteImpl(const bchar*command);
		BearCore::BearString m_command;
		BearCore::BearVector<BearCore::BearString> m_command_stack;
	};
	extern BearConsole * GConsole;
}