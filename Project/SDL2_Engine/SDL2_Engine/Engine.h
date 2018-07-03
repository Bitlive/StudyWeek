#pragma once

#pragma region forward decleration
class SDL_Window;
class SDL_Surface;
class SDL_Renderer;
class CScene;
#pragma endregion

/// <summary>
/// core engine class
/// </summary>
class CEngine
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	CEngine();

	/// <summary>
	/// destructor
	/// </summary>
	~CEngine();
#pragma ednregion

#pragma region public function
	/// <summary>
	/// initialize engine
	/// </summary>
	/// <returns>if initialize successful</returns>
	bool Init();

	/// <summary>
	/// load images
	/// </summary>
	/// <returns>if images loaded successfully</returns>
	bool Load();

	/// <summary>
	/// running program
	/// </summary>
	void Run();

	/// <summary>
	/// clean up engine
	/// </summary>
	void Clean();

	/// <summary>
	/// change active scene
	/// </summary>
	/// <param name="_pScene">new scene</param>
	void ChangeScene(CScene* _pScene);

private:
#pragma region private primitive variable
	/// <summary>
	/// if engine is running
	/// </summary>
	bool m_isRunning;
#pragma endregion

#pragma region private variable
	/// <summary>
	/// window to render to
	/// </summary>
	SDL_Window* m_pWindow;

	/// <summary>
	///  surface from window
	/// </summary>
	SDL_Surface* m_pSurface;

	/// <summary>
	/// renderer to render images
	/// </summary>
	SDL_Renderer* m_pRenderer;

	/// <summary>
	/// active scene
	/// </summary>
	CScene* m_pScene;
#pragma enregion

#pragma region private function
	/// <summary>
	/// update every frame
	/// </summary>
	void Update();

	/// <summary>
	/// render every frame
	/// </summary>
	void Render();
#pragma endregion
};