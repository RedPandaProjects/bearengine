#pragma once
namespace BearEngine
{
	struct BearClassAllocator
	{
		BearClassAllocator() :OnlyOne(false) {}
		mutable bool OnlyOne;
		virtual BearObject*alloc(const BearName&type) const = 0;
	};
	template<class C>
	struct BearClassAllocatorPrivate :public BearClassAllocator
	{
		virtual BearObject*alloc(const BearName&type) const override
		{
			BEAR_FATALERROR(!OnlyOne, TEXT("Попытка создать одинарный класс"));
			auto item = BearCore::bear_alloc<C>(1);
			new(item)C(type);
//			item->m_created = false;
			OnlyOne = item->GetFlags().test(BO_OnlyOne);
			return item;
		}
	};
#define BEAR_CREATE_OBJECT(path) GObjectManager->Create<path>(BEAR_TO_STRING(path))
	class BEARENGINE_API BearObjectManager
	{
		
		friend class BearEngine;		
	private:
		BearObjectManager();
		~BearObjectManager();
	private:
	
		BearCore::BearMap<BearName, BearCore::BearMemoryRef<BearClassAllocator>> map_objects;
	public:
		template<class C>
		inline void Registor()
		{
#ifdef UNICODE
			BearCore::BearString type_text = *BearCore::BearEncoding::ToUTF16( typeid(C).name());
#else
			BearCore::BearString type_text = typeid(C).name();
#endif
			if (type_text.to_char(TEXT(' ')))
				type_text++;
			BearName type(*type_text);
			BEAR_FATALERROR(map_objects.find(type)== map_objects.end() , TEXT("такой класс[%s] существует"), *type.to_string());
			map_objects.insert(type, BearCore::bear_new<BearClassAllocatorPrivate<C>>());
		}

		template<class C>
		inline C*Create(BearName&&type)const
		{
			auto item = map_objects.find(type);
			BEAR_FATALERROR(item  != map_objects.end(), TEXT("такой класс[%s] не существует"), *type.to_string());
			auto result= dynamic_cast<C*>( item->second->alloc(type));
			BEAR_ASSERT(result);
			return result;
		}
		template<class C>
		inline C*Create(const BearName&type)const
		{
			auto item = map_objects.find(type);
			BEAR_FATALERROR(item != map_objects.end(), TEXT("такой класс[%s] не существует"), *type.to_string());
			auto result = dynamic_cast<C*>(item->second->alloc(type));
			BEAR_ASSERT(result);
			return result;
		}
	
	};

	extern BEARENGINE_API BearObjectManager* GObjectManager;
}