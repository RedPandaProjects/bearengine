#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearViewport:public BearGraphics::BearViewport,public BearObject
	{
		BEAR_OBJECT(BearViewport);
		BearViewport(const BearName&type);
		~BearViewport();
		friend class BearRender;
	public:
		virtual void Resize(bsize wigth, bsize height) override;
		virtual void SetFullScreen(bool fullscreen) override;
		BearCore::BearFVector2 GetSizeFloat()const;
		BearCore::BearVector2<bsize> GetSize()const;
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
	BEARENGINE_API extern BearViewport*GGeneralViewport;
}