#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearObject
	{
	public:
		virtual BearObject*Create(const BearName&name, const BearCore::BearVector2<float> & position)=0;
		virtual void update(float time)=0;
		virtual void destroy() = 0;
		inline BearCore::BearVector2<float>  getPosition()const
		{
			return position;
		}
		inline bool isStatic()const
		{
			return bStatic;
		}
		inline const BearName&getName() const
		{
			return name;
		}
	protected:
		BearObject(const BearName&name,const BearCore::BearVector2<float> & position, bool bStatic) :position(position),name(name), bStatic(bStatic) {}
		BearObject(): bStatic(true){};
		~BearObject() {}
		BearCore::BearVector2<float> position;

	private:
		BearName name;
		bool bStatic;
	};
}