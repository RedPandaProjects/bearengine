#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearConsoleCommand
	{
	public: 
		BEAR_CLASS_NO_COPY(BearConsoleCommand);
		BearConsoleCommand(const BearCore::BearString&name, const BearCore::BearString&info,bool empty_args,bool call_only_at_begin=false) :m_name(name), m_info(info),b_empty_args(empty_args),b_call_only_at_begin(call_only_at_begin){}
		~BearConsoleCommand();
		virtual bool Execute(const bchar*command);
		virtual void Destroy();
		void Info();
		virtual void Status();
		inline  bool IsEmpyArgs()const
		{
			return b_empty_args;
		}
		inline  bool IsCallOnlyAtBegin()const
		{
			return b_call_only_at_begin;
		}
		inline const BearCore::BearString&GetName()const
		{
			return m_name;
		}
		inline bool operator==(const BearConsoleCommand&right)const
		{
			return m_name == right.m_name;
		}
		inline bool operator<(const BearConsoleCommand&right)const
		{
			return m_name < right.m_name;
		}
	private:
		bool b_empty_args;
		bool b_call_only_at_begin;
		BearCore::BearString m_name;
		BearCore::BearString m_info;
	};

	
}