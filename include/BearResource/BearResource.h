#pragma once
namespace BearEngine
{
	template<class C>
	class BearResource
	{
		friend class BearResourceManager;
		BearResource(const BearName&name,const C&c):m_resource(c),m_name(name){}
		inline ~BearResource() { /*m_resource.Clear();*/ }
		BearName m_name;
		C m_resource;
	public:
		inline const C&get()const
		{
			return m_resource;
		}
		inline const C*operator->()const
		{
			return &m_resource;
		}
		inline const BearName&get_name()const
		{
			return m_name;
		}
	};
}