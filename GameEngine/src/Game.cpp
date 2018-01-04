// 3rd party/system headers
#include <sb7.h>
#include <assert.h>
#include <math.h>

// My libraries/Keenan's headers
#include "MathEngine.h"
#include "Framework.h"

// Game header
#include "Game.h"
// Input headers
#include "InputManager.h"
#include "Keyboard.h"
// Texture header
#include "TextureManager.h"
// Camera header
#include "CameraManager.h"
#include "CameraNode.h"
#include "Camera.h"
// Model headers
#include "CubeModel.h"
#include "PyramidModel.h"
#include "DiamondModel.h"
// Shader header
#include "Shader.h"
// GameObject headers
#include "GameObjectManager.h"
#include "GameObject.h"
// GraphicsObject headers
#include "GraphObj_SimpleColor.h"
#include "GraphObj_ColorByPosition.h"
#include "GraphObj_ColorLight.h"
#include "GraphObj_Wireframe.h"
#include "GraphObj_FlatTexture.h"
#include "GraphObj_TextureLight.h"


// TO DO: ----------------------------------

GameObject *pGameObject3 = 0;


//-----------------------------------------------------------------------------
//  Game::Game()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
Game::Game(const char* windowName, const int Width, const int Height)
	:Engine(windowName, Width, Height)
{
	assert(windowName);
}

Game::~Game()
{
}


//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{
	CameraManager::InitManager(this->info.windowWidth, this->info.windowHeight);
}


//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{
	/** Camera Setup **/
	//CameraNode *pCamNode;

	//// Medium shot, straight-on
	//pCamNode = new CameraNode(this->info.windowWidth, this->info.windowHeight);
	//assert(pCamNode != 0);
	//pCamNode->SetupCamera(50.0f, Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 0.0f, 6.0f));
	//pCamNode->UpdateCamera();
	//CameraManager::Add(pCamNode);

	//// Set active camera
	//CameraManager::SetActiveCamera(pCamNode);

	//// Wide shot, right side
	//pCamNode = new CameraNode(this->info.windowWidth, this->info.windowHeight);
	//assert(pCamNode != 0);
	//pCamNode->SetupCamera(50.0f, Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(5.5f, 0.0f, 3.0f));
	//pCamNode->UpdateCamera();
	//CameraManager::Add(pCamNode);

	//// Wide shot, left side
	//pCamNode = new CameraNode(this->info.windowWidth, this->info.windowHeight);
	//assert(pCamNode != 0);
	//pCamNode->SetupCamera(50.0f, Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(-5.5f, 0.0f, 3.0f));
	//pCamNode->UpdateCamera();
	//CameraManager::Add(pCamNode);

	// Medium shot, straight-on
	CameraManager::Add(50.0f, Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 0.0f, 6.0f));
	// Wide shot, right side
	CameraManager::Add(50.0f, Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(5.5f, 0.0f, 3.0f));
	// Wide shot, left side
	CameraManager::Add(50.0f, Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(-5.5f, 0.0f, 3.0f));


	/** Create models **/
	CubeModel *pCubeModel = new CubeModel("CubeModel.azul");
	assert(pCubeModel != 0);
	PyramidModel *pPyramidModel = new PyramidModel("PyramidModel.azul");
	assert(pPyramidModel != 0);
	DiamondModel *pDiamondModel = new DiamondModel("DiamondModel.azul");
	assert(pDiamondModel != 0);


	/** Create Shader object **/
	Shader *pShader_ColorSimple = new Shader("SimpleColorShader", Shader::Name::COLOR_SIMPLE);
	assert(pShader_ColorSimple != 0);
	Shader *pShader_ColorPos = new Shader("ColorShader", Shader::Name::COLOR_POSITION);
	assert(pShader_ColorPos != 0);
	Shader *pShader_ColorLight = new Shader("ColorPointLightDiff", Shader::Name::COLOR_LIGHT);
	assert(pShader_ColorLight != 0);
	Shader *pShader_Texture = new Shader("TextureShader", Shader::Name::TEXTURE_FLAT);
	assert(pShader_Texture != 0);
	Shader *pShader_TexLight = new Shader("TexturePointLightDiff", Shader::Name::TEXTURE_LIGHT);
	assert(pShader_TexLight != 0);

	/** Add textures to TextureManager **/
	TextureManager::AddTexture("Duckweed.tga", TextureManager::Name::DUCKWEED);
	TextureManager::AddTexture("RedBrick.tga", TextureManager::Name::RED_BRICK);
	TextureManager::AddTexture("Rocks.tga", TextureManager::Name::ROCKS);
	TextureManager::AddTexture("Stone.tga", TextureManager::Name::STONES);

	/** Create GameObject Instances **/
	GraphObj_SimpleColor	 *pGraphic_ColorSimple;
	GraphObj_ColorByPosition *pGraphic_ColorPos;
	GraphObj_ColorLight		 *pGraphic_ColorLight;
	GraphObj_Wireframe		 *pGraphic_Wireframe;
	GraphObj_FlatTexture	 *pGraphic_Texture;
	GraphObj_TextureLight	 *pGraphic_TexLight;

	GameObject *pGameObject;

	Vect whiteLight(1.0f, 1.0f, 1.0f);
	Vect lightPos(1.0f, 0.5f, 1.0f);

	// Top Row
	pGraphic_ColorSimple = new GraphObj_SimpleColor(pCubeModel, pShader_ColorSimple, Vect(0.35f, 0.7f, 0.35f, 0.0f));
	pGameObject = new GameObject(pGraphic_ColorSimple);
	pGameObject->SetTranslation(Vect(-3.0f, 1.0f, 0.0f));
	pGameObject->SetRotX(55.0f);
	pGameObject->SetScale(Vect(0.5f, 0.5f, 0.5f));
	GameObjectManager::Add(pGameObject);

	pGraphic_ColorPos = new GraphObj_ColorByPosition(pCubeModel, pShader_ColorPos);
	pGameObject = new GameObject(pGraphic_ColorPos);
	pGameObject->SetTranslation(Vect(-2.0f, 1.0f, 0.0f));
	GameObjectManager::Add(pGameObject);

	pGraphic_ColorLight = new GraphObj_ColorLight(pCubeModel, pShader_ColorLight, Vect(1.0f, 0.5f, 1.0f), Vect(0.5f, 0.7f, 0.4f));
	pGameObject = new GameObject(pGraphic_ColorLight);
	pGameObject->SetTranslation(Vect(-0.5f, 1.0f, 0.0f));
	pGameObject->SetRotZ(20.0f);
	GameObjectManager::Add(pGameObject);

	pGraphic_Wireframe = new GraphObj_Wireframe(pCubeModel, pShader_ColorPos);
	pGameObject = new GameObject(pGraphic_Wireframe);
	pGameObject->SetTranslation(Vect(0.5f, 1.0f, 0.0f));
	pGameObject->SetRotY(20.0f);
	pGameObject->SetScale(Vect(0.75f, 0.75f, 0.75f));
	GameObjectManager::Add(pGameObject);

	pGraphic_Texture = new GraphObj_FlatTexture(pCubeModel, pShader_Texture, TextureManager::Name::STONES);
	pGameObject = new GameObject(pGraphic_Texture);
	pGameObject->SetTranslation(Vect(2.0f, 1.0f, 0.0f));
	pGameObject->SetRotY(20.0f);
	pGameObject->SetRotZ(20.0f);
	pGameObject->SetScale(Vect(0.75f, 0.75f, 0.75f));
	GameObjectManager::Add(pGameObject);

	pGraphic_TexLight = new GraphObj_TextureLight(pCubeModel, pShader_TexLight, TextureManager::Name::ROCKS, whiteLight, lightPos);
	pGameObject = new GameObject(pGraphic_TexLight);
	pGameObject->SetTranslation(Vect(3.0f, 1.0f, 0.0f));
	pGameObject->SetRotX(55.0f);
	GameObjectManager::Add(pGameObject);

	// Middle Row
	pGraphic_ColorSimple = new GraphObj_SimpleColor(pPyramidModel, pShader_ColorSimple, Vect(0.35f, 0.7f, 0.35f, 0.0f));
	pGameObject = new GameObject(pGraphic_ColorSimple);
	pGameObject->SetTranslation(Vect(-3.0f, 0.0f, 0.0f));
	pGameObject->SetRotX(55.0f);
	pGameObject->SetScale(Vect(0.5f, 0.5f, 0.5f));
	GameObjectManager::Add(pGameObject);

	pGraphic_ColorPos = new GraphObj_ColorByPosition(pPyramidModel, pShader_ColorPos);
	pGameObject = new GameObject(pGraphic_ColorPos);
	pGameObject->SetTranslation(Vect(-2.0f, 0.0f, 0.0f));
	GameObjectManager::Add(pGameObject);

	pGraphic_ColorLight = new GraphObj_ColorLight(pPyramidModel, pShader_ColorLight, Vect(1.0f, 0.5f, 1.0f), Vect(0.5f, 0.7f, 0.4f));
	pGameObject = new GameObject(pGraphic_ColorLight);
	pGameObject->SetTranslation(Vect(-0.5f, 0.0f, 0.0f));
	pGameObject->SetRotZ(20.0f);
	GameObjectManager::Add(pGameObject);

	pGraphic_Wireframe = new GraphObj_Wireframe(pPyramidModel, pShader_ColorPos);
	pGameObject = new GameObject(pGraphic_Wireframe);
	pGameObject->SetTranslation(Vect(0.5f, 0.0f, 0.0f));
	pGameObject->SetRotY(20.0f);
	pGameObject->SetScale(Vect(0.75f, 0.75f, 0.75f));
	GameObjectManager::Add(pGameObject);

	pGraphic_Texture = new GraphObj_FlatTexture(pPyramidModel, pShader_Texture, TextureManager::Name::STONES);
	pGameObject = new GameObject(pGraphic_Texture);
	pGameObject->SetTranslation(Vect(2.0f, 0.0f, 0.0f));
	pGameObject->SetRotY(20.0f);
	pGameObject->SetRotZ(20.0f);
	pGameObject->SetScale(Vect(0.75f, 0.75f, 0.75f));
	GameObjectManager::Add(pGameObject);

	pGraphic_TexLight = new GraphObj_TextureLight(pPyramidModel, pShader_TexLight, TextureManager::Name::ROCKS, whiteLight, lightPos);
	pGameObject = new GameObject(pGraphic_TexLight);
	pGameObject->SetTranslation(Vect(3.0f, 0.0f, 0.0f));
	pGameObject->SetRotX(55.0f);
	pGameObject3 = pGameObject;
	GameObjectManager::Add(pGameObject);

	// Bottom Row
	pGraphic_ColorSimple = new GraphObj_SimpleColor(pDiamondModel, pShader_ColorSimple, Vect(0.35f, 0.7f, 0.35f, 0.0f));
	pGameObject = new GameObject(pGraphic_ColorSimple);
	pGameObject->SetTranslation(Vect(-3.0f, -1.0f, 0.0f));
	pGameObject->SetRotX(55.0f);
	pGameObject->SetScale(Vect(0.5f, 0.5f, 0.5f));
	GameObjectManager::Add(pGameObject);

	pGraphic_ColorPos = new GraphObj_ColorByPosition(pDiamondModel, pShader_ColorPos);
	pGameObject = new GameObject(pGraphic_ColorPos);
	pGameObject->SetTranslation(Vect(-2.0f, -1.0f, 0.0f));
	GameObjectManager::Add(pGameObject);

	pGraphic_ColorLight = new GraphObj_ColorLight(pDiamondModel, pShader_ColorLight, Vect(1.0f, 0.5f, 1.0f), Vect(0.5f, 0.7f, 0.4f));
	pGameObject = new GameObject(pGraphic_ColorLight);
	pGameObject->SetTranslation(Vect(-0.5f, -1.0f, 0.0f));
	pGameObject->SetRotZ(20.0f);
	GameObjectManager::Add(pGameObject);

	pGraphic_Wireframe = new GraphObj_Wireframe(pDiamondModel, pShader_ColorPos);
	pGameObject = new GameObject(pGraphic_Wireframe);
	pGameObject->SetTranslation(Vect(0.5f, -1.0f, 0.0f));
	pGameObject->SetRotY(20.0f);
	pGameObject->SetScale(Vect(0.75f, 0.75f, 0.75f));
	GameObjectManager::Add(pGameObject);

	pGraphic_Texture = new GraphObj_FlatTexture(pDiamondModel, pShader_Texture, TextureManager::Name::STONES);
	pGameObject = new GameObject(pGraphic_Texture);
	pGameObject->SetTranslation(Vect(2.0f, -1.0f, 0.0f));
	pGameObject->SetRotY(20.0f);
	pGameObject->SetRotZ(20.0f);
	pGameObject->SetScale(Vect(0.75f, 0.75f, 0.75f));
	GameObjectManager::Add(pGameObject);

	pGraphic_TexLight = new GraphObj_TextureLight(pDiamondModel, pShader_TexLight, TextureManager::Name::ROCKS, whiteLight, lightPos);
	pGameObject = new GameObject(pGraphic_TexLight);
	pGameObject->SetTranslation(Vect(3.0f, -1.0f, 0.0f));
	pGameObject->SetRotX(55.0f);
	GameObjectManager::Add(pGameObject);
}


//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Game::Update(float currentTime)
{
	// Needs to be updated once a frame
	CameraManager::UpdateActiveCam();

	InputManager::Update();

	Keyboard *pKeyboard = InputManager::GetKeyboard();

	/******************** Swap Textures *********************/
	if (pKeyboard->GetKeyState(Keyboard::KEYS::KEY_1) == true)
	{
		// Get graphics object and cast to GraphObj_FlatTexture
		GraphObj_FlatTexture *pGraphObj = (GraphObj_FlatTexture *)pGameObject3->GetGraphicsObject();
		// Set new texture
		pGraphObj->textureName = TextureManager::Name::DUCKWEED;
	}
	if (pKeyboard->GetKeyState(Keyboard::KEYS::KEY_2) == true)
	{
		// Get graphics object and cast to GraphObj_FlatTexture
		GraphObj_FlatTexture *pGraphObj = (GraphObj_FlatTexture *)pGameObject3->GetGraphicsObject();
		// Set new texture
		pGraphObj->textureName = TextureManager::Name::RED_BRICK;
	}
	if (pKeyboard->GetKeyState(Keyboard::KEYS::KEY_3) == true)
	{
		// Get graphics object and cast to GraphObj_FlatTexture
		GraphObj_FlatTexture *pGraphObj = (GraphObj_FlatTexture *)pGameObject3->GetGraphicsObject();
		// Set new texture
		pGraphObj->textureName = TextureManager::Name::ROCKS;
	}
	if (pKeyboard->GetKeyState(Keyboard::KEYS::KEY_4) == true)
	{
		// Get graphics object and cast to GraphObj_FlatTexture
		GraphObj_FlatTexture *pGraphObj = (GraphObj_FlatTexture *)pGameObject3->GetGraphicsObject();
		// Set new texture
		pGraphObj->textureName = TextureManager::Name::STONES;
	}

	// Update game object
	GameObjectManager::Update(currentTime);
}


//-----------------------------------------------------------------------------
// Game::Render()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Render()
{
	GameObjectManager::Render();
}


//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{
	GameObjectManager::UnloadContent();
	TextureManager::DeleteTextures();
	CameraManager::Destroy();
}


//-----------------------------------------------------------------------------
// Game::ScreenResize()
//-----------------------------------------------------------------------------
void Game::OnResize(int w, int h)
{
    Engine::OnResize(w, h);
}


//------------------------------------------------------------------
// Game::ClearBuffer()
// Allows user to change the way the clear buffer function works
//------------------------------------------------------------------
void Game::ClearBuffer()
{
	const GLfloat grey[] = { 0.7f, 0.7f, 0.8f, 1.0f };
	const GLfloat one = 1.0f;

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glClearBufferfv(GL_COLOR, 0, grey);
	glClearBufferfv(GL_DEPTH, 0, &one);
}
