#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearViewport:public BearGraphics::BearViewport,public BearObject,public BearObjectResize
	{
		BEAR_OBJECT(BearViewport);
		BearViewport(const BearName&type);
		~BearViewport();
		friend class BearRender;
	public:
		bool IsFullScreen()const
		{
			return FullScreen;
		}
		virtual void Resize(bsize wigth, bsize height) override;
		virtual void SetFullScreen(bool fullscreen) override;
		inline BearCore::BearFVector2 GetSizeFloat()const
		{
			return BearCore::BearVector2<float>(static_cast<float>(Width), static_cast<float>(Height));
		}
		
		inline BearCore::BearVector2<bsize> GetSize()const
		{
			return BearCore::BearVector2<bsize>(Width, Height);
		}
		bool Update();
		virtual void Destroy() override;
		inline 
#ifdef WINDOWS
		HWND
#elif LINUX
		void*
#endif
		GetWindowHandle() const
		{
			return m_window;
		}
		const BearGraphics::BearShaderConstantsRef&GetOthroConstant()const
		{
			return m_sconst_othro;
		}
	private:
		virtual void Update(float time) override;
		virtual void Save(BearCore::BearOutputStream*stream) override;
		virtual void Load(const BearCore::BearInputStream*stream) override;
#ifdef WINDOWS
		HWND 
#elif LINUX
		void*
#endif
		m_window;
		bsize Width;
		bsize Height;
		bool FullScreen;
		BearGraphics::BearShaderConstantsRef m_sconst_othro;
		BearCore::BearMatrix m_othro;
	};

}