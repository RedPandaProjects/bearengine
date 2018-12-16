#pragma once
namespace BearEngine
{
	class BEARENGINE_API BearInput :public BearObject
	{

		BEAR_OBJECT(BearInput);
		BearInput(const BearName&type);
		~BearInput();
	public:
		bool IsKeyPress(const BearName&Key);
		bool IsKeyDown(const BearName&Key);
		bool IsKeyUp(const BearName&Key);
		inline float GetMouseScroll()
		{
			return m_mouse_scroll;
		}
		BearCore::BearFVector2 GetMousePosition();
		void SetMousePosition(const BearCore::BearFVector2&position);
		inline void SetMousePosition(float x,float y)
		{
			SetMousePosition(BearCore::BearFVector2(x,y));
		}
		virtual void Destroy();
		inline const BearCore::BearString&GetInputString()
		{
			return m_input_string;
		}
	private:

		virtual void Update(float time) override;
		virtual void Save(BearCore::BearOutputStream*stream) override;
		virtual void Load(const BearCore::BearInputStream*stream) override;
#ifdef BEAR_ENGINE_EXPORTS
	public:
#endif
		BearCore::BearString m_input_string;
		friend BearViewport;
		enum KeyStats
		{
			KS_None,
			KS_Down,
			KS_Press,
			KS_Up,
		};
		float m_mouse_scroll;
		BearCore::BearMap<BearName, KeyStats> m_keys;
#ifdef WINDOWS
		BearCore::BearMap<DWORD, BearName> m_keys_windows;
#endif
	};
	BEARENGINE_API extern BearInput*GInput;
#include "BearInputNames.h"
}