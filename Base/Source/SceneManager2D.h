#ifndef SCENE_MANAGER_2D_H
#define SCENE_MANAGER_2D_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Minimap.h"
#include "Map.h"
#include "Vector2.h"
#include "PlayerInfo.h"
#include "Enemy.h"

// Goodies and Goodies Factory
#include "GoodiesFactory.h"
#include "Goodies.h"
#include "TreasureChest.h"

class CSceneManager2D : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_LIGHTENABLED,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_BACKGROUND,
		GEO_MENU,
		GEO_SELECT,
		GEO_HIGHSCORE,
		// TEMPO NAME
		GEO_OPTION1,
		GEO_OPTION2,
		GEO_OPTION3,
		GEO_OPTION4,
		GEO_TEXT,
		NUM_GEOMETRY,
	};

public:
	CSceneManager2D();
	CSceneManager2D(const int m_window_width, const int m_window_height);
	~CSceneManager2D();

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update Weapon status
	virtual void UpdateWeaponStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderBackground();
	void RenderMainMenu();
	void RenderHighscore();
	void RenderOption();
	void Render2DMesh(Mesh *mesh, const bool enableLight, const int size=1, const int x=0, const int y=0, const bool rotate=false, const bool flip=false);

	// Menu States
	bool PlaySelect;
	bool HighscoreSelect;
	bool OptionSelect;
	bool ExitSelect;

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera3 camera;

	float rotateAngle;

	MS modelStack;
	MS viewStack;
	MS projectionStack;


	float fps;

	// Window size
	int m_window_width;
	int m_window_height;

};

#endif