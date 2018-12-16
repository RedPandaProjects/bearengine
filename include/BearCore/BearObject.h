#pragma once
namespace BearEngine
{
	enum BearObjectFlags
	{
		BO_ForGame = 1 << 0,
		BO_OnlyOne = 1 << 1,
	};
#define BEAR_OBJECT_VALUE(value) Value(TEXT(BEAR_TO_STRING(value)),value,this)
#define BEAR_OBJECT_VALUE_FROM_USER(value) ValueFromUser(TEXT(BEAR_TO_STRING(value)),value,this)
#define BEAR_OBJECT_VALUE_TO_USER(value) ValueToUser(TEXT(BEAR_TO_STRING(value)),value,this)
#define BEAR_OBJECT_DESTROY(name) this->~name();BearCore::bear_free(this); 
#define BEAR_OBJECT(name)\
	BEAR_CLASS_NO_COPY(name)\
	friend  ::BearEngine::BearClassAllocatorPrivate<name>;
	class BEARENGINE_API BearObject
	{
	public:
		 
		virtual void Destroy() = 0;
		virtual void Update(float time) = 0;
		virtual void Save(BearCore::BearOutputStream*stream);
		virtual void Load(const BearCore::BearInputStream*stream);
		inline const BearCore::BearFlags<uint32>&GetFlags()const
		{
			return m_flags;
		}
		inline const BearName&GetType() const
		{
			return m_type;
		}
	protected:
		BearObject(const BearName&type, uint32 flags) :m_type(type), m_flags(flags) {}
		~BearObject() {}

		template<class C,class M>
		inline void Value(const bchar*name, C&c,M*m)
		{
			value(name, c);
		}
		template<class C, class M >
		inline void ValueToUser(const bchar*name, C&c, M*m)
		{
			valueToUser(name, c);
		}
		template<class C, class M>
		inline void ValueFromUser(const bchar*name, C&c, M*m)
		{
			valueFromUser(name, c);
		}
	private:
		void valueToUser( const bchar*key, uint8 data);
		void valueToUser( const bchar*key, uint16 data);
		void valueToUser( const bchar*key, uint32 data);
		void valueToUser( const bchar*key, uint64 data);
		void valueToUser( const bchar*key, int8 data);
		void valueToUser( const bchar*key, int16 data);
		void valueToUser( const bchar*key, int32 data);
		void valueToUser( const bchar*key, int64 data);
		void valueToUser( const bchar*key, bool data);
		void valueToUser( const bchar*key,const BearCore::BearString&data);
		void valueToUser( const bchar*key, const BearCore::BearVector<BearCore::BearString>&data);
	private:
		void valueFromUser( const bchar*key, uint8&data);
		void valueFromUser( const bchar*key, uint16&data);
		void valueFromUser( const bchar*key, uint32&data);
		void valueFromUser( const bchar*key, uint64&data);
		void valueFromUser( const bchar*key, int8&data);
		void valueFromUser( const bchar*key, int16&data);
		void valueFromUser( const bchar*key, int32&data);
		void valueFromUser( const bchar*key, int64&data);
		void valueFromUser( const bchar*key, bool& data);
		void valueFromUser( const bchar*key, BearCore::BearString&data);
		void valueFromUser( const bchar*key, BearCore::BearVector<BearCore::BearString>&data);
	private:
		void value( const bchar*key, float&data);
		void value( const bchar*key, uint8&data);
		void value( const bchar*key, uint16&data);
		void value( const bchar*key, uint32&data);
		void value( const bchar*key, uint64&data);
		void value( const bchar*key, int8&data);
		void value( const bchar*key, int16&data);
		void value( const bchar*key, int32&data);
		void value( const bchar*key, int64&data);
		void value( const bchar*key, bool& data);
		void value( const bchar*key, BearCore::BearString&data);
		void value( const bchar*key, BearCore::BearVector<BearCore::BearString>&data);
		BearObject*getValueClass(const bchar*key);
		template<class C>
		inline void value(const bchar*key, C*&c)
		{
			c = dynamic_cast<C*>(getValueClass(key));
			BEAR_ASSERT(c);
		}
	private:
		static const BearCore::BearString&GetType(const char*name);
	private:
		BearName m_type;
		BearCore::BearFlags<uint32> m_flags;
	};
	class BEARENGINE_API BearObjectResize
	{
	public:
		virtual void Resize(bsize widht, bsize height)=0;

	};
	class BEARENGINE_API BearObjectAppActive
	{
	public:
		virtual void AppActive()=0;

	};
	class BEARENGINE_API BearObjectAppDeactive
	{
	public:
		virtual void AppDeactive()=0;

	};
}