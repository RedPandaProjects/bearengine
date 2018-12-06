#pragma once
namespace BearEngine
{
	class BearType
	{
	public:
		BearType() { m_type[0] = 0; m_type[8] = 0;}
		~BearType(){ }
		BearType(const bchar8*type)
		{
			m_type[8] = 0;
			BearCore::bear_copy(m_type, type, BearCore::bear_min(BearCore::BearString::GetSize(type),bsize(8))); 
		}
		uint64 to_uint64() const
		{ 
			return *reinterpret_cast<const uint64*>(m_type);
		}
		uint64 &to_uint64() 
		{
			return *reinterpret_cast<uint64*>(m_type);
		}
		inline bchar16* to_tchar()
		{
			for (bsize i = 0; i < 9; i++)
			{
				m_ttype[i] = static_cast<bchar16>(m_type[i]);
			}
			return m_ttype;
		}
		void set(const bchar8*type) 
		{
			BearCore::bear_copy(m_type, type, BearCore::bear_min(BearCore::BearString::GetSize(type), bsize(8)));
		}
		bool operator==(const BearType&type) const
		{
			return to_uint64() == type.to_uint64();
		}
		bool operator<(const BearType&type) const
		{
			return to_uint64() < type.to_uint64();
		}
		const bchar8* operator*() const
		{
			return m_type;
		}
		void copy(const BearType&right)
		{
			BearCore::bear_copy(m_type, right.m_type, 8);
		}
		void swap( BearType&right)
		{
			BearCore::bear_swap(m_type, right.m_type, 8);
		}
		BearType(BearType&&right)
		{
			m_type[0] = 0;
			swap(right);
		}
		BearType(const BearType&right)
		{
			m_type[0] = 0;
			copy(right);
		}
		BearType&operator=(const BearType&right)
		{
			copy(right);
			return *this;
		}
		BearType&operator=( BearType&&right)
		{
			swap(right);
			return *this;
		}
	private:
		bchar8 m_type[9];
		bchar16 m_ttype[9];
	};
}