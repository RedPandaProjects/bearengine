#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearConsole :public BearObject,public BearObjectResize
	{
		BEAR_OBJECT(BearConsole);
		BearConsole(const BearName&type);
		~BearConsole();
	
#ifdef BEAR_ENGINE_EXPORTS
	public:
#endif
		void CallStack();
		virtual void Resize(bsize width, bsize height);
		virtual void Save(BearCore::BearOutputStream*stream);
		virtual void Load(const BearCore::BearInputStream*stream);
		virtual void Destroy();
		virtual void Update(float time);
	public:
		bool Execute(const bchar*command);
		void PushCommand(BearConsoleCommand*);
	private:

		BearRenderText* m_render_log;
		BearRenderText* m_render_command;
		BearRenderText* m_render_finder;

		BearSprite*m_plane_log;
		BearSprite*m_plane_finder;
		BearSprite*m_plane_item;

		float m_timer_cursor;

		bsize m_count_line;

		bsize m_shift_item;
		bint m_id_item;

		BearCore::BearVector<BearConsoleCommand*> m_command_list;
	private:
		bool Show;
	private:
		BearCore::BearVector<const bchar*> m_finder_command_data;
	private:
		bool ExecuteImpl(const bchar*command);
		BearCore::BearString m_command;
		BearCore::BearString m_command_last;
		BearCore::BearVector<BearCore::BearString> m_command_stack;
	};
	extern BearConsole * GConsole;
}