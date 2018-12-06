#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearName
	{
	public:
		BearName() :m_id(0) {}
		inline ~BearName() {  }
		BearName(const BearName&right) :m_id(right.m_id) {}
		BearName(BearName&&right) :m_id(0) { swap(right); }

		BearName(const bchar*name) :m_id(0) { set(name); }
		inline const BearCore::BearString&to_string() const
		{
			return GetString(m_id);
		}
		inline void set(const bchar*name)
		{
			m_id = GetID(name);
		}

		inline void copy(const BearName&right)
		{
			m_id = right.m_id;
		}
		inline void swap( BearName&right)
		{
			BearCore::bear_swap(m_id, right.m_id);
		}
		inline BearName&operator=(const BearName&right)
		{
			copy(right);
			return*this;
		}
		inline BearName&operator=(BearName&&right)
		{
			swap(right);
			return*this;
		}
		bool operator<(const BearName&right)const
		{
			return m_id < right.m_id;
		}
		bool operator==(const BearName&right)const
		{
			return m_id == right.m_id;
		}
		bool operator!=(const BearName&right)const
		{
			return m_id != right.m_id;
		}
	private:
		static bsize GetID(const bchar*name);
		static const BearCore::BearString&GetString(bsize id);
		bsize m_id;
	};
#include "BearNames.h"
}