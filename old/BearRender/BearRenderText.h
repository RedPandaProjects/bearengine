#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearRenderText
	{
		BEAR_CLASS_NO_COPY(BearRenderText);
	public:
		BearCore::BearString text;
		BearCore::BearFVector2 position;
		static BearRenderText*Create(const bchar*font);
		void destroy();
		void draw();
	private:
		BearRenderText(const bchar*font);
		~BearRenderText();
		BearFont*m_font;
		BearMaterialInstance*m_material_font;
	};
}