#pragma once
namespace BearEngine
{
	template<class C>
	struct BearMultiResource
	{
	public:
		BearMultiResource():m_count(1){}
		inline ~BearMultiResource() { BEAR_ASSERT(*m_data&&m_count); m_data.clear(); }

		inline bool empty() const
		{
			return !*m_data;
		}
		inline P*&get()
		{
			return *m_data;
		}
		inline const P*get()const
		{
			return *m_data;
		}
		inline void operator++(int)
		{
			m_count++; 
		}
		inline void operator--(int)
		{
			m_count--;
			if(m_count==0)
			{
				m_data.clear();
			}
		}
	private:
		bsize m_count;
		BearCore::BearMemoryRef<C> m_data;
	};
}