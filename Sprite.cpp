#include "Sprite.hpp"

// Konstruktor
//
// Aufgabe: Zeiger auf Renderer holen
//
CSprite::CSprite()
{
	// Zeiger auf Renderer holen
	m_pRenderer = g_pFramework->GetRenderer();

} // Konstruktor


// Destruktor
//
// Aufgabe: Textur des Sprites freigeben
//
CSprite::~CSprite ()
{
	// Textur freigeben
	SDL_DestroyTexture(m_pImage);

} // Destruktor


// Load
//
// Aufgabe: Einfaches, nicht animiertes Sprite laden
//
void CSprite::Load (const string sFilename)
{
	// Bitmap temporär in eine Surface laden
	SDL_Surface *pTemp = SDL_LoadBMP (sFilename.c_str () );

    // Prüfen ob alles glatt ging
	if (pTemp == NULL)
	{
		cout << "Fehler beim Laden von: " << sFilename.c_str ();
		cout << endl;
		cout << "Fehlermeldung: " << SDL_GetError () << endl;

		// Framework herunterfahren
		g_pFramework->Quit ();

		// Gesamtes Spiel beenden
		exit (1);
	}

	// Transparente Farbe festlegen
	SDL_SetColorKey(pTemp, SDL_TRUE, SDL_MapRGB(pTemp->format, 255, 0, 255));
    
	// Die eigentliche Textur erzeugen
    m_pImage = SDL_CreateTextureFromSurface(m_pRenderer, pTemp);

    // Rect initialisieren
    m_Rect.x = 0;
    m_Rect.y = 0;
    m_Rect.w = pTemp->w;
    m_Rect.h = pTemp->h;
    
	// Temporäre Surface freigeben
    SDL_FreeSurface(pTemp);

} // Load


// Load
//
// Aufgabe: Animiertes Sprite laden
//
void CSprite::Load (const string sFilename, int NumFrames,
					int FrameWidth, int FrameHeight)
{
	// Bitmap laden
	Load (sFilename);

	// Rect für Animationsphase initialisieren
	m_NumFrames   = NumFrames;
	m_FrameWidth  = FrameWidth;
	m_FrameHeight = FrameHeight;
	m_FrameRect.w = FrameWidth;
	m_FrameRect.h = FrameHeight;
	m_NumFramesX  = m_Rect.w / m_FrameWidth;

	// Ziel-Rect korrigieren
	m_Rect.w = FrameWidth;
	m_Rect.h = FrameHeight;

} // Load


// SetPos
//
// Aufgabe: Position des Sprites festlegen
//
void CSprite::SetPos (float fXPos, float fYPos)
{
	// Rect updaten
	m_Rect.x = static_cast<int>(fXPos);
	m_Rect.y = static_cast<int>(fYPos);

} // SetPos


// Render
//
// Aufgabe: Sprite rendern (ohne Animation)
//
void CSprite::Render ()
{
	// Sprite rendern
    SDL_RenderCopy(m_pRenderer, m_pImage, NULL, &m_Rect);
	
} // Render


// Render
//
// Aufgabe: Ausschnitt des Sprites rendern (Animationsphase)
//
void CSprite::Render (float fFrameNumber)
{
	// Ausschnitt der aktuellen Animationsphase berechnen
	//

	// Spalte berechnen
	int Column = static_cast<int>(fFrameNumber)%m_NumFramesX;

	// Zeile berechnen
	int Row = static_cast<int>(fFrameNumber)/m_NumFramesX;

	// Rect berechnen
	m_FrameRect.x = Column * m_FrameWidth;
	m_FrameRect.y = Row * m_FrameHeight;

	// Ausschnitt rendern
    SDL_RenderCopy(m_pRenderer, m_pImage, &m_FrameRect, &m_Rect);

} // Render
