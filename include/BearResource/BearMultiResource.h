#pragma once
namespace BearEngine
{
	template<class C>
	struct BearMultiResource
	{
	public:
		BearMultiResource():m_count(1),m_data(0){}
		inline ~BearMultiResource() {}

		inline bool empty() const
		{
			return !m_count;
		}
		inline C*get()
		{
			return m_data;
		}
		inline void set(C* data)
		{
			m_data = data;
		}
		inline const C*get()const
		{
			return m_data;
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
				m_data = 0;
			}
		}
	private:
		bsize m_count;
		C * m_data;
	};
}