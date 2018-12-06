#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearSampler
	{
		friend class BearRender;
	public:
		BearSampler();
		BearSampler(const BearName&texture);
		~BearSampler();

		void swap(BearSampler&right);
		BearSampler(BearSampler&right);
		BearSampler&operator=(BearSampler&right);

		enum SamplerMode
		{
			SM_WRAP = 0,
			SM_MIRROR,
			SM_CLAMP,
			SM_BORDER,
		};
		enum SamplerFilter
		{
			SF_MAG_MIP_POINT = 0,
			SF_MAG_LINEAR_MIP_POINT,
			SF_MAG_MIP_LINEAR,
			SF_ANISOTROPIC,
			SF_COMPARISON_MAG_MIP_POINT,
			SF_COMPARISON_MAG_LINEAR_MIP_POINT,
			SF_COMPARISON_MAG_MIP_LINEAR,
			SF_COMPARISON_ANISOTROPIC,
		};

		void SetTexture(const BearName&texture);
		inline void SetMode(SamplerMode mode) { m_mode = mode; }
		inline void SetFilter(SamplerFilter filter) { m_filter = filter;}
		inline const BearTexture2DRef&GetTexture()const
		{
			return *m_texture;
		}
	private:
		BearTexture2DRef*m_texture;
		SamplerFilter m_filter;
		SamplerMode  m_mode;
	};
};