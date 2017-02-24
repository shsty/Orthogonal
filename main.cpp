#include "main.h"
#include "map.h"
#include "player.h"
#include "cursor.h"
#include "renderer.h"

char msg[ERRBUFSIZE];

MainApp mainApp;

MainApp::MainApp(){
    state = S_STOP;

    mapname = "assets/test.map";

    map = new Map();
    player = new Player(map);
    cursor = new Cursor();

    cursor->active1 = cursor->active2 = 0;
    cursor->focus = C_None;
}

MainApp::~MainApp(){
    delete player;
    delete map;
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
    //loading map
    try{
        map->load(mapname);
    }
    catch (std::exception & e){
        SDL_Log(e.what());
        errno = 0;
        SDL_Log("Starting with empty map");
        map->clear();
    }

    //initializing player position
    player->init(map);

    //initializing window and render environment
    renderer = new Renderer(map->size);
    
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
    player->update();
}

void MainApp::OnDelay(){
    //SDL_Delay(18);
}

void MainApp::OnCleanup(){
    if (renderer) delete renderer;
}

