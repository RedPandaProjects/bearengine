#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearResource
	{
	BEAR_CLASS_NO_COPY(BearResource);
	public:
		BearResource():m_data(0){}
		inline ~BearResource() {  }

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
		void*m_data;
	};
}