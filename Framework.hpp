#ifndef FRAMEWORK_HPP
#define FRAMEWORK_HPP

#include <iostream>
#include "Singleton.hpp"
#include "Timer.hpp"

using namespace std;

#define g_pFramework CFramework::Get()

class CFramework : public TSingleton<CFramework>
{
	public:
		CFramework		();
		bool  Init		(int ScreenWidth, int ScreenHeight,
						 int ColorDepth, bool bFullscreen);
		void  Quit		();
		void  Update	();
		void  Clear		();
		void  Render	();
		bool  KeyDown	(int Key_ID);
		SDL_Renderer* GetRenderer() { return m_pRenderer; }
    
	private:		
		const Uint8		*m_pKeystate; // Array für aktuellen Tastaturstatus
		SDL_Window		*m_pWindow;	  // SDL-Windows	
		SDL_Renderer	*m_pRenderer; // SDL-Renderer

};

#endif
