#include "main.h"
#include "map.h"
#include "player.h"
#include "cursor.h"
#include "renderer.h"

char msg[ERRBUFSIZE];

const int MainApp::mapSize = 16;

MainApp mainApp;

MainApp::MainApp(){
    state = S_STOP;

    dt = 18/1000.0;
    g = 1.0;

    mapname = "assets/test.map";

    map = new Map(mapSize);
    player = new Player();
    cursor = new Cursor();

    cursor->active1 = cursor->active2 = 0;
    cursor->focus = C_None;
}

MainApp::~MainApp(){
    delete map;
    delete player;
    delete cursor;
}

int MainApp::OnExecute() {
    try{
        if (OnInit() == false){
            return -1;
        }

        SDL_Event event;
        while (state != S_STOP){
            while (SDL_PollEvent(&event)){
                OnEvent(&event);
            }
            OnLoop();
            OnRender();
            OnDelay();
        }
        map->save(mapname);
    }
    catch (SDL_Exception & e){
        printf("%s", e.what());
    }
    catch (std::exception & e){
        printf("%s", e.what());
    }

    OnCleanup();

    return 0;
}


int main(int argc, char* argv[]) {
    if (argc >= 2){
        mainApp.mapname = std::string("assets/test") + argv[1] + ".map";
    }
    return mainApp.OnExecute();
}

bool MainApp::OnInit(){
    //initializing window and render environment
    renderer = new Renderer(mapSize);

    //loading map
    try{
        map->load(mapname);
        player->init(map);
    }
    catch (std::exception & e){
        SDL_Log(e.what());
        errno = 0;
        SDL_Log("Starting with empty map");
        map->clear();
    }
    
    //done initilizing
    state = S_RUNNING;

    return true;
}

void MainApp::OnRender(){
    renderer->clear();

    renderer->tex["background"]->draw(NULL);
    renderer->tex["field"]->draw(&renderer->lfieldrect);
    renderer->tex["field"]->draw(&renderer->rfieldrect);

    map->render(player, renderer);
    player->render(renderer);
    cursor->render(renderer);

    renderer->present();
}

void MainApp::OnLoop(){
    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    player->react(keystate, dt);
    player->move(map, dt);
}

void MainApp::OnDelay(){
    //SDL_Delay(18);
}

void MainApp::OnCleanup(){
    if (renderer) delete renderer;
}

