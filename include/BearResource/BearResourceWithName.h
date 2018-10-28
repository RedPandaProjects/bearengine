#pragma once
namespace BearEngine
{
	class BearResourceWithName
	{
		BEAR_CLASS_NO_COPY(BearResourceWithName);
	public:
		BearResourceWithName() : m_data(0) { m_name[0] = 0; }
		
		inline ~BearResourceWithName() {  }

		inline bchar*get_name()
		{
			return m_name;
		}
		
		inline const bchar*get_name() const
		{
			return m_name;
		}
		
		inline bool empty() const
		{
			return !m_data;
		}
		
		template<class P>
		inline P*&get()
		{
			return reinterpret_cast<P*&>(m_data);
		}
		
		template<class P>
		inline const P*get()const
		{
			return reinterpret_cast<const P*>(m_data);
		}
	private:
		mutable BearCore::BearString64 m_name;
		mutable void*m_data;
	};
}