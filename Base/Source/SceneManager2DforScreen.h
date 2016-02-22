#ifndef SCENE_MANAGER_2D_FS_H
#define SCENE_MANAGER_2D_FS_H

#include "GameStateManager.h"
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
#include "Player.h"
#include "Save.h"
#include "SpriteAnimation.h"
#include "SoundManager.h"

#include "Highscore.h"
#include "HighscoreData.h"
#include "Particle.h"
#include "LuaUsage.h"

// Goodies and Goodies Factory
#include "GoodiesFactory.h"
#include "Goodies.h"
#include "TreasureChest.h"

//grid system and grid class
#include "GridSystem.h"


class SceneManagerLevel2DforScreen : public Scene
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
		U_TEXT_ALPHA_ENABLED,
		U_TEXT_ALPHA,
		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_BACKGROUND,
		GEO_TILEGROUND,
		GEO_TILEHERO,
		GEO_TILETREE,
		GEO_TILESTRUCTURE,
		GEO_TILEHERO_FRAME0,
		GEO_TILEHERO_FRAME1,
		GEO_TILEHERO_FRAME2,
		GEO_TILEHERO_FRAME3,
		GEO_TILE_KILLZONE,
		GEO_TILE_SAFEZONE,
		GEO_TILEENEMY_FRAME0,
		GEO_TILE_TREASURECHEST,
		GEO_SPRITE_ANIMATION,
		GEO_OBJECT,

		GEO_MENU,
		GEO_SELECT,
		GEO_INSTRUCTION,
		GEO_HIGHSCORE,
		// TEMPO NAME
		GEO_VOL_MUTE,
		GEO_VOL,
		GEO_SOUND_MUTE,
		GEO_SOUND,

		GEO_TEXT,
		NUM_GEOMETRY,
	};
	enum PARTICLE_STYLE
	{
		DROPDOWN = 0,
		CONFETTI,
		NUM_PARTICLE_STYLE
	};
public:
	SceneManagerLevel2DforScreen();
	SceneManagerLevel2DforScreen(const int m_window_width, const int m_window_height, const int ScreenValue);
	~SceneManagerLevel2DforScreen();

	virtual void Init();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);
	// Update mouse status
	virtual void UpdateMouseStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y, bool enablealpha = false);
	void RenderBackground();
	void RenderMainMenu();
	void RenderHighscore();
	void RenderInstructions();
	void RenderOption();
	void Render2DMesh(Mesh *mesh, const bool enableLight, bool enablealpha = false, const int size = 1, const int x = 0, const int y = 0, const bool rotate = false, const bool flip = false);

	// Menu States
	bool PlaySelect;
	bool InstructionSelect;
	bool HighscoreSelect;
	bool OptionSelect;
	bool ExitSelect;

	// Option States
	bool SoundSelect;
	bool VolumeSelect;
	bool muted;

	void AddHighscore();
	HighscoreData theScore[5];
	CSoundManager Sound;

	float tempsound;

	enum WEAPON_ACTION
	{
		WA_NIL = 0,
		WA_LEFT_CLICKED,
		WA_FIRE,
		WA_RELOAD,
		WA_CHANGEWEAPON,
		WA_TOTAL,
	};

private:
	Player* m_player;
	Save* m_save;

	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float m_alpha;

	Camera3 camera;

	float rotateAngle;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	float fps;


	//window height and width
	short m_screenvalue;
	int m_windowHeight;
	int m_windowWidth;
	/*
	// Handle to the minimap
	CMinimap* m_cMinimap;

	// Handle to the tilemaps
	CMap* m_cMap;
	void RenderTileMap();
	// Hero's information
	CPlayerInfo* theHero;

	// Codes for Scrolling
	int tileOffset_x, tileOffset_y;

	// Codes for Parallax Scrolling
	CMap* m_cRearMap;
	void RenderRearTileMap();
	int rearWallOffset_x, rearWallOffset_y;
	int rearWallTileOffset_x, rearWallTileOffset_y;
	int rearWallFineOffset_x, rearWallFineOffset_y;

	// Enemies
	CEnemy* theEnemy;

	// Goodies and Goodies Factory
	CGoodiesFactory theGoodiesFactory;
	CGoodies** theArrayOfGoodies;
	void RenderGoodies(void);
	*/
};

#endif