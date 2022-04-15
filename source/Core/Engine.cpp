#include "Engine.h"
#include "Texture.h"
#include <iostream>
#include <SDL.h>
#include "Vector2D.h"
#include "Transform.h"
#include "Doctor.h"
#include "Obs.h"
#include "Collision.h"
using namespace std;
Engine* Engine::s_Instance = nullptr;

Doctor* player = nullptr;

Obs* obstacles = nullptr;

Obs* obstacles2 = nullptr;

bool Engine::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0&& IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) !=0){
        SDL_Log("Failed to intialize SDL: %s", SDL_GetError());
        return false;
    } // Kiểm tra khởi tạo video và hình ảnh đúng định dạng

    m_Window = SDL_CreateWindow("Dinosaur", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    if(m_Window == nullptr){
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    m_Renderer = SDL_CreateRenderer(m_Window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(m_Renderer == nullptr){
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    Texture::GetInstance()->Load("background", "img/background.jpg"); // Tải texture

    Texture::GetInstance()->Load("character", "img/characterrun.png"); // Tải texture

    Texture::GetInstance()->Load("Obstacles", "img/obstacles.png"); // Tải texture

    Texture::GetInstance()->Load("Obstacles2", "img/covid.png"); // Tải texture

    player = new Doctor(new Properties("character", 100, 450, 120, 122));

    obstacles = new Obs(new Properties("Obstacles", 1000, 475, 74, 85));

    obstacles2 = new Obs(new Properties("Obstacles2", 1300, 470, 48, 51));

    return m_IsRunning = true;
}

bool Engine::Clean()
{
    Texture::GetInstance()->Clean();
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    IMG_Quit();
    SDL_Quit();

}

void Engine::Quit()
{
    m_IsRunning = false;
}

void Engine::Update()
{
    player->Update(0);

    Rect_id["character"].w-=55;
    Rect_id["character"].h-=40;

    Rect_id["Obstacles"].w-=15;
    //Rect_id["Obstacles"].h-=15;

    bool check_collision = Collision::GetCollision()->check_Collision(Rect_id["character"], Rect_id["Obstacles"]);
    if(check_collision == 1) m_IsRunning=0;

    bool check_collision_2 = Collision::GetCollision()->check_Collision(Rect_id["character"], Rect_id["Obstacles2"]);
    if(check_collision_2 == 1) m_IsRunning=0;

    //cout<<Rect_id["character"].x<<' '<<Rect_id["character"].y<<' '<<Rect_id["character"].h<<' '<<Rect_id["character"].w<<'\n';
    //cout<<Rect_id["Obstacles2"].x<<' '<<Rect_id["Obstacles2"].y<<' '<<Rect_id["Obstacles2"].h<<' '<<Rect_id["Obstacles2"].w<<'\n';

}

void Engine::Render()
{
    //SDL_SetRenderDrawColor(m_Renderer,96,241,110, 105); //set màu cho thao tác trên m_Renderer
    SDL_RenderClear(m_Renderer);

    Texture::GetInstance()->Draw("background", 0, 0, 1000 , 658); //In ra texture
    player->Draw();

    obstacles->Draw();

    obstacles2->Draw();

    SDL_RenderPresent(m_Renderer); //In ra m_Renderer bản final
}

void Engine::Envents()
{
    SDL_Event event;
    SDL_PollEvent(&event); //Check hàng đợi sự kiện
    if(event.type == SDL_QUIT){
            Quit();
    }
    if(event.type == SDL_KEYDOWN && player->stt == 0 && event.key.keysym.sym == SDLK_SPACE){
        //cout<<1<<'\n';
        player->Jump();
    }
}
int Engine::timeperframe(){
    return 1000/fps;
}
