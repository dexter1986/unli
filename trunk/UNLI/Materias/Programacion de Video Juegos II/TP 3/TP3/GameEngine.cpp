#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stdio.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <climits>
#include "GameEngine.h"


GameEngine::GameEngine(int ancho,int alto,std::string titulo,int fps)
{	
	m_currentScene = NULL;
	m_sceneToDelete = NULL;
	exitEngine = false;
	isPause = false;
	fpsScale = 1.0f;
	j.up=j.down=j.left=j.right=j.a=j.b=0;

	srand(time(NULL));
	
	wnd = new RenderWindow(VideoMode(ancho,alto),titulo);	
	wnd->SetFramerateLimit(fps);

	//App.SetView(App.GetDefaultView());

	wnd->Show(true);		
}

void GameEngine::Init()
{
}

GameEngine::~GameEngine(void)
{
}

void GameEngine::PushScene(SceneBase *scene)
{
	m_sceneQueue.push_back(scene);
}

void GameEngine::Loop()
{	
	float dt = 0.0f;
	
	while(wnd->IsOpened() && !exitEngine)
	{
		if (m_currentScene == NULL)
		{
			if(m_sceneQueue.size() > 0)
			{
				m_currentScene = m_sceneQueue.front();
				m_currentScene->Init();
			}
			else
			{
				m_currentScene = NULL;	
				exitEngine = true;
			}
		}
		else if(m_currentScene->IsFinished())
		{
			m_currentScene->Cleanup();
			m_sceneQueue.pop_front();
			delete m_currentScene;
			m_currentScene = NULL;
		}
		else if(m_currentScene->IsExit())
		{
			if(m_currentScene)
			{
				m_currentScene->Cleanup();
				m_sceneQueue.pop_front();
				delete m_currentScene;
				m_currentScene = NULL;
			}

			while(m_sceneQueue.size() > 0)
			{
				m_currentScene = m_sceneQueue.front();
				m_sceneQueue.pop_front();
				delete m_currentScene;
				m_currentScene = NULL;
			}
		}
		else
		{
			dt = clk.GetElapsedTime() * fpsScale;
			clk.Reset();
			if(!isPause)
			{	
				DoEvents();
				UpdateEvents(dt);
			}
			
			DrawGame();
		}	
	}
	wnd->Close();
}

void GameEngine::DoEvents(){
	Event evt;
	while(wnd->GetEvent(evt)){	
		if(evt.Type == evt.Closed)
		{				
			exitEngine = true;
		}
		else
		{
			JoystickUpdate(evt);
			UpdatePoolEvents(evt);
		}		
	}
	
}

void GameEngine::DrawGame()
{
	wnd->Clear();
	m_currentScene->Render(*wnd);
	wnd->Display();
}

void GameEngine::UpdatePoolEvents(const Event &evt)
{
	m_currentScene->ProcessEvent(evt);
}

void GameEngine::UpdateEvents(const float &dt)
{
	m_currentScene->Update(dt);
}

void GameEngine::JoystickUpdate(const Event &evt)
{
	if (evt.Type == sf::Event::KeyPressed){
		switch(evt.Key.Code){
			case sf::Key::Up:		j.up=true; break; 
			case sf::Key::Down: 	j.down=true; break; 
			case sf::Key::Left: 	j.left=true; break; 
			case sf::Key::Right: 	j.right=true; break; 
			case sf::Key::A: 		j.a=true; break; 
			case sf::Key::S: 		j.b=true; break;
			/*case sf::Key::P:		
				if(!isContinue)
				{
					isPause = !isPause; 					
					//cronometro->Reset();
				}
				break;			
			case sf::Key::Return:	
				if(isPause)
				{
					toReload = true;
				}
				break; 
			case sf::Key::Escape: 
				isGameFinish = true; 
				isExit = true; 
				break;
			case sf::Key::Q:    						
				isSlowTime = !isSlowTime;						
				if(isSlowTime)
				{
					fpsScale = 0.5f;							
					slowTimeCount = 0;
				}
				else
				{
					fpsScale = 1.0f;
				}
				break;*/
		}
	}
			
	if (evt.Type == sf::Event::KeyReleased){
		switch(evt.Key.Code){
			case sf::Key::Up:		j.up=false; break; 
			case sf::Key::Down: 	j.down=false; break; 
			case sf::Key::Left: 	j.left=false; break; 
			case sf::Key::Right: 	j.right=false; break; 
			case sf::Key::A: 		j.a=false; break; 
			case sf::Key::S: 		j.b=false; break;
		}
	}	
}