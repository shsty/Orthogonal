#include "main.h"

char msg[ERRBUFSIZE];

const char * MainApp::WINDOW_NAME = "SDL2";
const std::string MainApp::respath  = "sketch/";

MainApp mainApp;

MainApp::MainApp():map(16){
    state = S_STOP;
    screen_width = 1096;
    screen_height = 560;
    fieldscale = 32;

    window = nullptr;
    ren = nullptr;
    
    bgtex = nullptr;
    fieldtex = nullptr;
    playertex = nullptr;
    blocktex = nullptr;
    cursortex = nullptr;

    dt = 18/1000.0;
    g = 1.0;

    mapname = "assets/test.map";

    cursor.active1 = cursor.active2 = 0;
    cursor.focus = Cursor::C_None;
}

MainApp::~MainApp(){
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
    return mainApp.OnExecute();
}

bool MainApp::OnInit(){
    //SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) throw SDL_Exception();

    int imgflags = IMG_INIT_PNG;
    if (IMG_Init(imgflags) & imgflags != imgflags) throw IMG_Exception();

    SDL_version sdlversion;
    SDL_GetVersion(&sdlversion);

    SDL_Log("SDL Version %d.%d.%d", sdlversion.major, sdlversion.minor, sdlversion.patch);

    const SDL_version * img_version = IMG_Linked_Version();

    SDL_Log("SDL_Image Version %d.%d.%d", img_version->major, img_version->minor, img_version->patch);

    //Creating window
    window = SDL_CreateWindow(
            WINDOW_NAME,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            screen_width,
            screen_height,
            SDL_WINDOW_SHOWN
    );
    if (window == nullptr) throw SDL_Exception();

    //Creating renderer
    ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) throw SDL_Exception();

    //loading images
    bgtex = LoadTexture("background2.png");
    fieldtex = LoadTexture("field2.png");
    playertex = LoadTexture("player.png");
    blocktex = LoadTexture("blocks.png");
    cursortex = LoadTexture("cursor.png");
    
    //setting up fields
    int fw = fieldscale * map.size;
    int fh = fieldscale * map.size;
    lfieldrect.w = rfieldrect.w = fw;
    lfieldrect.h = rfieldrect.h = fh;
    lfieldrect.x = (screen_width - 2*fw)/3;
    lfieldrect.y = (screen_height - fh)/2;
    rfieldrect.x = lfieldrect.x*2 + fw;
    rfieldrect.y = lfieldrect.y;

    //loading map
    try{
        map.load(mapname);
    }
    catch (std::exception & e){
        SDL_Log(e.what());
        errno = 0;
        SDL_Log("Starting with empty map");
        map.clear();
    }
    
    //done initilizing
    state = S_RUNNING;

    return true;
}

SDL_Texture * MainApp::LoadTexture(const std::string & imgname){
    //Loading resources
    std::string imgpath = respath + imgname;
    SDL_Surface *img = IMG_Load(imgpath.c_str());
    if (img == nullptr) throw IMG_Exception();

    //convert surface to texture
    SDL_Texture * tex = SDL_CreateTextureFromSurface(ren, img);
    SDL_FreeSurface(img);
    if (tex == nullptr) throw SDL_Exception();
    
    return tex;
}

void MainApp::OnDelay(){
    //SDL_Delay(18);
}

void MainApp::OnCleanup(){
    if (bgtex) SDL_DestroyTexture(bgtex);
    if (fieldtex) SDL_DestroyTexture(fieldtex);
    if (playertex) SDL_DestroyTexture(playertex);
    if (blocktex) SDL_DestroyTexture(blocktex);
    if (cursortex) SDL_DestroyTexture(cursortex);
    if (ren) SDL_DestroyRenderer(ren);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
