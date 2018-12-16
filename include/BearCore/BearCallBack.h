#pragma once
namespace BearEngine
{
	class BearCallBack;
#define RegisterCallBack(name,typeobj,function,arg_in,arg_out)\
	struct BearCallBack##name\
	{\
friend BearCallBack;\
	inline void add(typeobj*cl,int32 id) \
	{\
		BearCallBackObject<typeobj> item;\
		item.c = cl; item.id = id;\
		auto object=BearCore::bear_lower_bound(m_list.begin(),m_list.end(),item);\
		m_list.insert(object,item);\
	}\
	inline void remove(typeobj*cl) \
	{\
		auto begin =m_list.begin();\
		auto end = m_list.end();\
		while (begin != end)\
		{\
			begin->c = cl;\
			begin++;\
		}\
	}\
private:\
	inline void call_back(arg_in) \
	{\
		auto begin =m_list.begin();\
		auto end = m_list.end();\
		while (begin != end)\
		{\
			begin->c->function(arg_out);\
			begin++;\
		}\
	}\
		BearCore::BearVector< BearCallBackObject<typeobj>> m_list;\
	};



	namespace Impl
	{
		template<class C>
		struct BearCallBackObject
		{
			int32 id;
			C*c;;
			bool operator<(const BearCallBackObject&obj) const { return id < obj.id; }
			bool operator==(C*obj)const { return cl == obj; }

		};
#include "BearCallBacks.h"
	};

#undef RegisterCallBack

#define RegisterCallBack(name,typeobj,function,arg_in,arg_out)\
private:\
	Impl::BearCallBack##name m_##name;\
public:\
	inline 	Impl::BearCallBack##name&Get##name()\
	{\
	return m_##name; \
	}\
private:\
	inline 	void CallBack##name(arg_in)\
	{\
	 m_##name.call_back(arg_out);\
	}\

#define BEAR_CALLBACK_START -200
#define BEAR_CALLBACK_END 200
	

	class BEARENGINE_API BearCallBack :public BearObject
	{
		friend class BearEngine;
		friend class BearRender;
		friend class BearViewport;
		BEAR_OBJECT(BearCallBack);
		BearCallBack(const BearName&name);
		~BearCallBack();
		virtual void Destroy();
	private:
		void ObjectsDestroy();
		virtual void Update(float time) override;
		virtual void Save(BearCore::BearOutputStream*stream) override;
		virtual void Load(const BearCore::BearInputStream*stream)override;
#include "BearCallBacks.h"
	};
#undef RegisterCallBack
	BEARENGINE_API extern BearCallBack*GCallBack;
}
