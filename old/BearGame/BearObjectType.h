#pragma once
namespace BearEngine
{
	class BearObjectType
	{
	public:
		BearObjectType() { m_type[0] = 0; }
		~BearObjectType(){ }
		BearObjectType(const bchar8*type)
		{
			BearCore::bear_copy(m_type, type, BearCore::bear_min(BearCore::BearString::GetSize(type),bsize(9))); 
		}
		uint64 to_uint64() const
		{ 
			return *reinterpret_cast<const uint64*>(m_type);
		}
		uint64 &to_uint64() 
		{
			return *reinterpret_cast<uint64*>(m_type);
		}
		void set(const bchar8*type) 
		{
			BearCore::bear_copy(m_type, type, BearCore::bear_min(BearCore::BearString::GetSize(type), bsize(9)));
		}
		bool operator==(const BearObjectType&type) const
		{
			return to_uint64() == type.to_uint64();
		}
		bool operator<(const BearObjectType&type) const
		{
			return to_uint64() < type.to_uint64();
		}
		void copy(const BearObjectType&right)
		{
			BearCore::bear_copy(m_type, right.m_type, 9);
		}
		void swap( BearObjectType&right)
		{
			BearCore::bear_swap(m_type, right.m_type, 9);
		}
		BearObjectType(BearObjectType&&right)
		{
			m_type[0] = 0;
			swap(right);
		}
		BearObjectType(const BearObjectType&right)
		{
			m_type[0] = 0;
			copy(right);
		}
		BearObjectType&operator=(const BearObjectType&right)
		{
			copy(right);
			return *this;
		}
		BearObjectType&operator=( BearObjectType&&right)
		{
			swap(right);
			return *this;
		}
	private:
		bchar8 m_type[9];
	};
}