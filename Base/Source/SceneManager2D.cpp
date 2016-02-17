#include "SceneManager2D.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "Strategy_Kill.h"

CSceneManager2D::CSceneManager2D()
	: PlaySelect(true)
	, HighscoreSelect(false)
	, OptionSelect(false)
	, ExitSelect(false)
{
}

CSceneManager2D::CSceneManager2D(const int m_window_width, const int m_window_height)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CSceneManager2D::~CSceneManager2D()
{
}

void CSceneManager2D::Init()
{
	// Blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Switch on culling
	glEnable(GL_CULL_FACE);
	
	// Render mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Activate blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate and bind vertex array
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	// Load the shaders
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Text.fragmentshader" );
	
	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	
	// Use our shader
	glUseProgram(m_programID);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	// Initialise the camera
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));

	// Create the meshes
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	// Load the ground mesh and texture
	meshList[GEO_BACKGROUND] = MeshBuilder::Generate2DMesh("GEO_BACKGROUND", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//sky_background.tga");
	
	meshList[GEO_MENU] = MeshBuilder::Generate2DMesh("GEO_MENU", Color(1, 1, 1), 0, 0, 800, 600);
	meshList[GEO_MENU]->textureID = LoadTGA("Image//MainMenu.tga");

	meshList[GEO_SELECT] = MeshBuilder::Generate2DMesh("GEO_SELECT", Color(1, 1, 1), 0, 0, 75, 55);
	meshList[GEO_SELECT]->textureID = LoadTGA("Image//Select.tga");

	// Do Options Here

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	rotateAngle = 0;
}

void CSceneManager2D::Update(double dt)
{
	if(Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	rotateAngle -= (float)Application::camera_yaw;// += (float)(10 * dt);

	camera.Update(dt);
	/*

	// Update the hero
	if(Application::IsKeyPressed('W'))
	this->theHero->MoveUpDown( true, 1.0f );
	if(Application::IsKeyPressed('S'))
	this->theHero->MoveUpDown( false, 1.0f );
	if(Application::IsKeyPressed('A'))
	this->theHero->MoveLeftRight( true, 1.0f );
	if(Application::IsKeyPressed('D'))
	this->theHero->MoveLeftRight( false, 1.0f );
	if(Application::IsKeyPressed(' '))
	this->theHero->SetToJumpUpwards(true);
	theHero->HeroUpdate(m_cMap);

	// ReCalculate the tile offsets
	tileOffset_x = (int) (theHero->GetMapOffset_x() / m_cMap->GetTileSize());
	if (tileOffset_x + m_cMap->GetNumOfTiles_Width() > m_cMap->getNumOfTiles_MapWidth())
	tileOffset_x = m_cMap->getNumOfTiles_MapWidth() - m_cMap->GetNumOfTiles_Width();

	// if the hero enters the kill zone, then enemy goes into kill strategy mode
	int checkPosition_X = (int) ((theHero->GetMapOffset_x() + theHero->GetPos_x()) / m_cMap->GetTileSize());
	int checkPosition_Y = m_cMap->GetNumOfTiles_Height() - (int) ( (theHero->GetPos_y() + m_cMap->GetTileSize()) / m_cMap->GetTileSize());
	if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 10)
	{
	theEnemy->ChangeStrategy( new CStrategy_Kill());
	}
	else if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 11)
	{
	theEnemy->ChangeStrategy(NULL);
	//		theEnemy->ChangeStrategy( new CStrategy_Kill());
	}
	else
	{
	//theEnemy->ChangeStrategy(NULL);
	}

	// Update the enemies
	theEnemy->SetDestination( theHero->GetPos_x(), theHero->GetPos_y() );
	theEnemy->Update( m_cMap );
	*/

	fps = (float)(1.f / dt);
}

/********************************************************************************
 Update Camera position
 ********************************************************************************/
void CSceneManager2D::UpdateCameraStatus(const unsigned char key, const bool status)
{
	//camera.UpdateStatus(key, status);

	// Update avatar position
}

/********************************************************************************
 Update Weapon status
 ********************************************************************************/
void CSceneManager2D::UpdateWeaponStatus(const unsigned char key)
{
	
}

/********************************************************************************
 Render text onto the screen
 ********************************************************************************/
void CSceneManager2D::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0)
		return;
	
	Mtx44 ortho;
	ortho.SetToOrtho(0, 800, 0, 600, -10, 10);
	projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
			viewStack.LoadIdentity();
			modelStack.PushMatrix();
				modelStack.LoadIdentity();
				modelStack.Translate(x, y, 0);
				modelStack.Scale(size, size, size);
				glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
				glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
				//	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
				glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, mesh->textureID);
				glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
				for(unsigned i = 0; i < text.length(); ++i)
				{
					Mtx44 characterSpacing;
					characterSpacing.SetToTranslation((i*0.5f) + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
					Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
					glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
					mesh->Render((unsigned)text[i] * 6, 6);
				}
				glBindTexture(GL_TEXTURE_2D, 0);
				glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
			modelStack.PopMatrix();
		viewStack.PopMatrix();
	projectionStack.PopMatrix();
}

/********************************************************************************
 Render 2D Mesh
 ********************************************************************************/
void CSceneManager2D::Render2DMesh(Mesh *mesh, bool enableLight, int size, int x, int y, bool rotate, bool flip)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 800, 0, 600, -10, 10);
	projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
			viewStack.LoadIdentity();
			modelStack.PushMatrix();
				modelStack.LoadIdentity();
				modelStack.Translate( (float)x, (float)y, 0);
				modelStack.Scale( (float)size, (float)size, (float)size);
				if (rotate)
					modelStack.Rotate(rotateAngle, 0, 0, 1);
       
				Mtx44 MVP, modelView, modelView_inverse_transpose;
	
				MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
				glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
				if(mesh->textureID > 0)
				{
					glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, mesh->textureID);
					glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
				}
				else
				{
					glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
				}
				mesh->Render();
				if(mesh->textureID > 0)
				{
					glBindTexture(GL_TEXTURE_2D, 0);
				}
       
			modelStack.PopMatrix();
		viewStack.PopMatrix();
	projectionStack.PopMatrix();
}

/********************************************************************************
 Render the background
 ********************************************************************************/
void CSceneManager2D::RenderBackground()
{
	// Render the crosshair
	Render2DMesh(meshList[GEO_BACKGROUND], false, 1);
}

/********************************************************************************
 Render this scene
 ********************************************************************************/
void CSceneManager2D::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
						camera.position.x, camera.position.y, camera.position.z,
						camera.target.x, camera.target.y, camera.target.z,
						camera.up.x, camera.up.y, camera.up.z
					);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	/*
	// Render the background image
	RenderBackground();
	// Render the rear tile map
	RenderRearTileMap();
	// Render the tile map
	RenderTileMap();
	// Render the goodies
	RenderGoodies();
	*/

	//On screen text
	/*
	std::ostringstream ss;
	ss.precision(5);
	ss << "theEnemy: " << theEnemy->GetPos_x() << ", " << theEnemy->GetPos_y();
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 30, 0, 6);
	std::ostringstream sss;
	sss.precision(5);
	sss << "mapOffset_x: "<<theHero->GetMapOffset_x();
	RenderTextOnScreen(meshList[GEO_TEXT], sss.str(), Color(0, 1, 0), 30, 0, 30);
	*/

	std::ostringstream ss;
	ss.precision(5);
	ss << "test text: " << " 9999999 ";
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 30, 0, 6);
}

void CSceneManager2D::RenderMainMenu()
{
	modelStack.PushMatrix();
	Render2DMesh(meshList[GEO_MENU], false);
	modelStack.PopMatrix();

	if (PlaySelect)
	{
		modelStack.PushMatrix();
		Render2DMesh(meshList[GEO_SELECT], false, 1.5, 250, 255);
		modelStack.PopMatrix();
	}
	else if (HighscoreSelect)
	{
		modelStack.PushMatrix();
		Render2DMesh(meshList[GEO_SELECT], false, 1.5, 170, 185);
		modelStack.PopMatrix();
	}
	else if (OptionSelect)
	{
		modelStack.PushMatrix();
		Render2DMesh(meshList[GEO_SELECT], false, 1.5, 210, 110);
		modelStack.PopMatrix();
	}
	else if (ExitSelect)
	{
		modelStack.PushMatrix();
		Render2DMesh(meshList[GEO_SELECT], false, 1.5, 260, 30);
		modelStack.PopMatrix();
	}
}

/********************************************************************************
 Exit this scene
 ********************************************************************************/
void CSceneManager2D::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}


/*

void CSceneManager2D::RenderTileMap()
{
	int m = 0;
	for (int i = 0; i < m_cMap->GetNumOfTiles_Height(); i++)
	{
		for (int k = 0; k < m_cMap->GetNumOfTiles_Width() + 1; k++)
		{
			m = tileOffset_x + k;
			// If we have reached the right side of the Map, then do not display the extra column of tiles.
			if ((tileOffset_x + k) >= m_cMap->getNumOfTiles_MapWidth())
				break;
			if (m_cMap->theScreenMap[i][m] == 1)
			{
				Render2DMesh(meshList[GEO_TILEGROUND], false, 1, k*m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 575 - i*m_cMap->GetTileSize());
			}
			else if (m_cMap->theScreenMap[i][m] == 2)
			{
				Render2DMesh(meshList[GEO_TILETREE], false, 1, k*m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 575 - i*m_cMap->GetTileSize());
			}
			else if (m_cMap->theScreenMap[i][m] == 10)
			{
				Render2DMesh(meshList[GEO_TILE_KILLZONE], false, 1, k*m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 575 - i*m_cMap->GetTileSize());
			}
			else if (m_cMap->theScreenMap[i][m] == 11)
			{
				Render2DMesh(meshList[GEO_TILE_SAFEZONE], false, 1, k*m_cMap->GetTileSize() - theHero->GetMapFineOffset_x(), 575 - i*m_cMap->GetTileSize());
			}
		}
	}

	if (theHero->GetAnimationInvert() == false)
	{
		if (theHero->GetAnimationCounter() == 0)
			Render2DMesh(meshList[GEO_TILEHERO_FRAME0], false, 1, theHero->GetPos_x(), theHero->GetPos_y());
		else if (theHero->GetAnimationCounter() == 1)
			Render2DMesh(meshList[GEO_TILEHERO_FRAME1], false, 1, theHero->GetPos_x(), theHero->GetPos_y());
		else if (theHero->GetAnimationCounter() == 2)
			Render2DMesh(meshList[GEO_TILEHERO_FRAME2], false, 1, theHero->GetPos_x(), theHero->GetPos_y());
		else if (theHero->GetAnimationCounter() == 3)
			Render2DMesh(meshList[GEO_TILEHERO_FRAME3], false, 1, theHero->GetPos_x(), theHero->GetPos_y());
		else
			Render2DMesh(meshList[GEO_TILEHERO_FRAME0], false, 1, theHero->GetPos_x(), theHero->GetPos_y());
	}
	else
	{
		if (theHero->GetAnimationCounter() == 0)
			Render2DMesh(meshList[GEO_TILEHERO_FRAME0], false, 1, theHero->GetPos_x(), theHero->GetPos_y(), false, true);
		else if (theHero->GetAnimationCounter() == 1)
			Render2DMesh(meshList[GEO_TILEHERO_FRAME1], false, 1, theHero->GetPos_x(), theHero->GetPos_y(), false, true);
		else if (theHero->GetAnimationCounter() == 2)
			Render2DMesh(meshList[GEO_TILEHERO_FRAME2], false, 1, theHero->GetPos_x(), theHero->GetPos_y(), false, true);
		else if (theHero->GetAnimationCounter() == 3)
			Render2DMesh(meshList[GEO_TILEHERO_FRAME3], false, 1, theHero->GetPos_x(), theHero->GetPos_y(), false, true);
		else
			Render2DMesh(meshList[GEO_TILEHERO_FRAME0], false, 1, theHero->GetPos_x(), theHero->GetPos_y(), false, true);
	}

	// Render the enemy
	int theEnemy_x = theEnemy->GetPos_x() - theHero->GetMapFineOffset_x();
	int theEnemy_y = theEnemy->GetPos_y();
	if (((theEnemy_x >= 0) && (theEnemy_x<800)) &&
		((theEnemy_y >= 0) && (theEnemy_y<600)))
	{
		Render2DMesh(meshList[GEO_TILEENEMY_FRAME0], false, 1, theEnemy_x, theEnemy_y);
	}
}


void CSceneManager2D::RenderRearTileMap()
{
	rearWallOffset_x = (int)(theHero->GetMapOffset_x() / 2);
	rearWallOffset_y = 0;
	rearWallTileOffset_y = 0;
	rearWallTileOffset_x = (int)(rearWallOffset_x / m_cRearMap->GetTileSize());
	if (rearWallTileOffset_x + m_cRearMap->GetNumOfTiles_Width() > m_cRearMap->getNumOfTiles_MapWidth())
		rearWallTileOffset_x = m_cRearMap->getNumOfTiles_MapWidth() - m_cRearMap->GetNumOfTiles_Width();
	rearWallFineOffset_x = rearWallOffset_x % m_cRearMap->GetTileSize();

	int m = 0;
	for (int i = 0; i < m_cRearMap->GetNumOfTiles_Height(); i++)
	{
		for (int k = 0; k < m_cRearMap->GetNumOfTiles_Width() + 1; k++)
		{
			m = rearWallTileOffset_x + k;
			// If we have reached the right side of the Map, then do not display the extra column of tiles.
			if ((rearWallTileOffset_x + k) >= m_cRearMap->getNumOfTiles_MapWidth())
				break;
			if (m_cRearMap->theScreenMap[i][m] == 3)
			{
				Render2DMesh(meshList[GEO_TILESTRUCTURE], false, 1, k*m_cRearMap->GetTileSize() - rearWallFineOffset_x, 575 - i*m_cRearMap->GetTileSize());
			}
		}
	}
}


void CSceneManager2D::RenderGoodies()
{
	// Render the goodies
	for (int i = 0; i<10; i++)
	{
		Render2DMesh(theArrayOfGoodies[i]->GetMesh(), false, 1, theArrayOfGoodies[i]->GetPos_x(), theArrayOfGoodies[i]->GetPos_y());
	}
}
*/