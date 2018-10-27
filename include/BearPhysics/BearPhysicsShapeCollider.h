#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearPhysicsBody
	{
	public:
		BEAR_CLASS_NO_COPY(BearPhysicsBody);
		BearPhysicsBody();
		void create(BearPhysicsShape&shape,float x,float y,bool dynamic);
		BearCore::BearVector2<float> getPosition()const;
		void clear();
		~BearPhysicsBody();
		template<class C>
		inline C*&getRef()
		{
			return reinterpret_cast<C*&>(m_ref);
		}
		template<class C>
		inline const C* getRef() const
		{
			return reinterpret_cast<const C*>(m_ref);
		}
	private:
		void*m_ref;
	};
}