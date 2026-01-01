#include "func.h"
#include "client.h"
#define g 0.0098f

//enum
chess_stts cs;
chess_kind_piece cp;

//std
std::queue<SDL_MouseMotionEvent> mouseMotionQueue;

//SDL
SDL_Window* window;
SDL_Renderer* renderer;
SDL_GLContext glContext;

//mic
Mix_Music* BGM_title; // タイトル
Mix_Music* BGM_loading; // ロード
Mix_Music* BGM_park; // 広場
Mix_Music* BGM_chess; // チェス
Mix_Music* BGM_race_park; // レース広場用
Mix_Music* BGM_race_ingame; // レースゲーム用
Mix_Music* BGM_tank_park; // 戦車広場用
Mix_Music* BGM_tank_ingame; // 戦車ゲーム用
Mix_Music* BGM_shooting_park; // シューティング広場用
Mix_Music* BGM_shooting_ingame; // シューティングゲーム用

//bool
bool pressW = false;
bool pressS = false;
bool pressA = false;
bool pressD = false;
bool pressSPACE = false;
bool pressSHIFT_L = false;
bool pressCTRL_L = false;
bool flagShadow = false;
bool flagAnim = false;
bool chess_hukan = false;
bool shotCanon = false;
bool flyingCanon = false;
bool doorAIM = false;
bool doorANIM = false;
bool onFire = false;

//float
float radius_aincrad;
float height_aincrad;
float diffuseMat[] = { 1.0f,0.5f,0.4f,1.0f };
float specularMat[] = { 0.5f,0.3f,0.2f,1.0f };
float ambientMat[] = { 1.0f,1.0f,1.0f,1.0f };
float lightposMat[] = { 2300 , 0, 750, 0 };
float h1;
float angle = 0.0;
float piece_width = 0.2366;
float weapon_moving_anim = 0.0;
float weapon_aiming = 0.0;
float dt;
float parkOBJrotate = 0.0;
float movingStraight;
float movingRight;
float movingUp;
float myAngle;
float topHeight;
float curTime, lastTime, elapseTime;
float jumpSpeed;
float jumpingHeight;
float sita;
float alpha;
float sports_movingSpeed = 0.0;
float sports_wheelR = 0.0;
float sports_vec = 0.0;
float sports_body_vec = 0.0;
float main_rotate = 0.0;
float elapsedSeconds;


//int
int currentMeshNum = 0;
int currentAnimNum = 0;
int animFrame = 0;
int WINDOW_WIDTH;
int WINDOW_HEIGHT;
int num0 = 5;//�����ɕ��o�����(������)
int num1 = 7;//�����ɕ��o�����(������)
int fps = 0; //frames per sec
int currentFrame = 0;
int currentRadius = aincradRad;
int count = 0;
int jumpingTime;
int chess_index;
int chessMyColor;
int chess_having = 0;
int chess_get_point[2];
int mouseDisplayX = 0;
int mouseDisplayY = 0;
int cmap[8][8];
int canonCoolTime = 500;
int explosionTime = 0;
int doorANIMcount = 0;
extern int chessMap[8][8];
//W
//B : P = 1, R = 2, N = 3, B = 4, Q = 6, K = 5
//W : P = 7, R = 8, N = 9, B = 10, K = 11, Q = 12
int weapon_aiming_torigger = 0;
int onFire_frame_count = 0;
int torque = 0;
int gear = 1;
int mainloopcount = 0;

//struct
Position lookingPosition;
Position myPosition;
Position AIMPos;
Position canonPos;
explodePos explosionPos;
FireWorksPos fireCenterPos[20];

Scene scene;

vihicle tankPos;
vihicle sportsPos;

void SceneController()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
	glMatrixMode(GL_MODELVIEW);
	float diffuse[] = { 1,1,1 };
	float specular[] = { 1.0,   1.0, 1.0 };
	float ambient[] = { 1.0,1.0,1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, lightposMat); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	if (mainloopcount == 0)//load Animation
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glPushMatrix();

		readAnim(currentMeshNum);

		glPopMatrix();
		glDisable(GL_NORMALIZE);
		glDisable(GL_DEPTH_TEST);
	}
	else if (mainloopcount == 1)//load init meshes
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glPushMatrix();

		loadInitMesh(currentMeshNum);

		glPopMatrix();
		glDisable(GL_NORMALIZE);
		glDisable(GL_DEPTH_TEST);
	}
	else if (mainloopcount == 2)//load inside park
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glPushMatrix();

		loadReturnfromGame(currentMeshNum);

		glPopMatrix();
		glDisable(GL_NORMALIZE);
		glDisable(GL_DEPTH_TEST);
	}
	else if (mainloopcount == 3)//load race
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glPushMatrix();

		loadRaceGameMesh(currentMeshNum);

		glPopMatrix();
		glDisable(GL_NORMALIZE);
		glDisable(GL_DEPTH_TEST);
	}
	else if (mainloopcount == 4)//load chess
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glPushMatrix();

		loadChessGameMesh(currentMeshNum);

		glPopMatrix();
		glDisable(GL_NORMALIZE);
		glDisable(GL_DEPTH_TEST);
	}
	else if (mainloopcount == 5)//load shooting
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glPushMatrix();

		loadShootingGameMesh(currentMeshNum);

		glPopMatrix();
		glDisable(GL_NORMALIZE);
		glDisable(GL_DEPTH_TEST);
	}
	else if (mainloopcount == 6)//load tank
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_NORMALIZE);
		glPushMatrix();

		loadTankGameMesh(currentMeshNum);

		glPopMatrix();
		glDisable(GL_NORMALIZE);
		glDisable(GL_DEPTH_TEST);
	}
	else
	{
		switch (scene)
		{
		case scene_1:
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_NORMALIZE);
			glPushMatrix();
			scene1(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			glPopMatrix();
			glDisable(GL_NORMALIZE);
			glDisable(GL_DEPTH_TEST);
			break;
		case scene_2:
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_NORMALIZE);
			glPushMatrix();
			scene2(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			glPopMatrix();
			glDisable(GL_NORMALIZE);
			glDisable(GL_DEPTH_TEST);
			break;
		case scene_3:
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_NORMALIZE);
			glPushMatrix();
			scene3(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			glPopMatrix();
			glDisable(GL_NORMALIZE);
			glDisable(GL_DEPTH_TEST);
			break;
		case scene_4:
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_NORMALIZE);
			glPushMatrix();
			scene4(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			glPopMatrix();
			glDisable(GL_NORMALIZE);
			glDisable(GL_DEPTH_TEST);
			break;
		case scene_5:
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_NORMALIZE);
			glPushMatrix();
			scene5(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			glPopMatrix();
			glDisable(GL_NORMALIZE);
			glDisable(GL_DEPTH_TEST);
			break;
		case scene_6:
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_NORMALIZE);
			glPushMatrix();
			scene6(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			glPopMatrix();
			glDisable(GL_NORMALIZE);
			glDisable(GL_DEPTH_TEST);
			break;
		case scene_7:
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_NORMALIZE);
			glPushMatrix();
			scene7(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			glPopMatrix();
			glDisable(GL_NORMALIZE);
			glDisable(GL_DEPTH_TEST);
			break;
		case scene_8:
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_NORMALIZE);
			glPushMatrix();
			scene8(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
			glPopMatrix();
			glDisable(GL_NORMALIZE);
			glDisable(GL_DEPTH_TEST);
			break;
		default:
			break;
		}

	}
}


int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	u_short port = DEF_PORT;
	char server_name[MAX_LEN_NAMES];
	sprintf(server_name, "localhost");

	switch (argc) {
	case 1:
		break;
	case 2:
		// 引数が２個のときサーバ名を読み取る
		sprintf(server_name, "%s", argv[1]);
		break;
	case 3:
		// 引数が３個のときサーバ名とポート番号を読み取る
		sprintf(server_name, "%s", argv[1]);
		port = (u_short)atoi(argv[2]);
		break;
	default:
		// 引数が0もしくは4個以上なら注意書きを表示する
		fprintf(stderr, "Usage: %s [server name] [port number]\n", argv[0]);
		return 1;
	}

	setup_client(server_name, port);
	std::cout << "setuped" << std::endl;

	// Set Current Directory to executable path to ensure assets are found
	char *base_path = SDL_GetBasePath();
	if (base_path) {
#ifdef _WIN32
		SetCurrentDirectoryA(base_path);
#else
		chdir(base_path);
#endif
		SDL_free(base_path);
	}

	// Create SDL window with OpenGL context
	SDL_DisplayMode displayMode;
	if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
		printf("Could not get display mode! SDL_Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	WINDOW_WIDTH = displayMode.w ;
	WINDOW_HEIGHT = displayMode.h ;

	SDL_Window* window = SDL_CreateWindow("OpenGL",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		SDL_WINDOW_OPENGL);

	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

	SDL_Color textColor = { 0, 0, 0, 255 }; // ���F

	glContext = SDL_GL_CreateContext(window);
	if (glContext == nullptr) {
		std::cerr << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// VSync を有効化してCPU使用率を削減
	SDL_GL_SetSwapInterval(1); // 1 = VSync有効, 0 = VSync無効

	renderer = SDL_CreateRenderer(window, -1, 0);
	bool running = true;

	Uint32 startTime = SDL_GetTicks();
	Uint32 remainST = SDL_GetTicks();
	int frameCount = 0;
	float fps = 0.0f;

	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "GLEW initialization failed: " << glewGetErrorString(err) << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!glGenBuffers) {
		std::cerr << "glGenBuffers is not loaded properly!" << std::endl;
		exit(EXIT_FAILURE);
	}

    // 再生する音声形式を指定して初期化
    int flags = MIX_INIT_MP3;
    if ((Mix_Init(flags) & flags) != flags) {
        printf("Mix_Init failed: %s\n", Mix_GetError());
        // Don't exit here, attempt to proceed (maybe other formats work or it's a minor issue), 
        // but likely Mix_LoadMUS will fail later if this failed.
    }

    // オーディオデバイスの初期化
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        printf("failed to initialize SDL_mixer.\n");
        SDL_Quit();
        exit(-1);
    }

    // BGMロード
    if ((BGM_title = Mix_LoadMUS("config/music/BGM_title.mp3")) == NULL) {
        printf("failed to load music (BGM_title): %s\n", Mix_GetError());
        Mix_CloseAudio(); // オーディオデバイスの終了
        SDL_Quit();
        exit(-1);
    }

    if ((BGM_loading = Mix_LoadMUS("config/music/BGM_loading.mp3")) == NULL) {
        printf("failed to load music and chunk.\n");
        Mix_CloseAudio(); // オーディオデバイスの終了
        SDL_Quit();
        exit(-1);
    }

    if ((BGM_park = Mix_LoadMUS("config/music/BGM_park.mp3")) == NULL) {
        printf("failed to load music and chunk.\n");
        Mix_CloseAudio(); // オーディオデバイスの終了
        SDL_Quit();
        exit(-1);
    }

    if ((BGM_chess = Mix_LoadMUS("config/music/BGM_chess.mp3")) == NULL) {
        printf("failed to load music and chunk.\n");
        Mix_CloseAudio(); // オーディオデバイスの終了
        SDL_Quit();
        exit(-1);
    }

    if ((BGM_race_park = Mix_LoadMUS("config/music/BGM_race_park.mp3")) == NULL) {
        printf("failed to load music and chunk.\n");
        Mix_CloseAudio(); // オーディオデバイスの終了
        SDL_Quit();
        exit(-1);
    }	

    if ((BGM_race_ingame = Mix_LoadMUS("config/music/BGM_race_ingame.mp3")) == NULL) {
        printf("failed to load music and chunk.\n");
        Mix_CloseAudio(); // オーディオデバイスの終了
        SDL_Quit();
        exit(-1);
    }	

    if ((BGM_tank_park = Mix_LoadMUS("config/music/BGM_tank_park.mp3")) == NULL) {
        printf("failed to load music and chunk.\n");
        Mix_CloseAudio(); // オーディオデバイスの終了
        SDL_Quit();
        exit(-1);
    }	

    if ((BGM_tank_ingame = Mix_LoadMUS("config/music/BGM_tank_ingame.mp3")) == NULL) {
        printf("failed to load music and chunk.\n");
        Mix_CloseAudio(); // オーディオデバイスの終了
        SDL_Quit();
        exit(-1);
    }	

    if ((BGM_shooting_park = Mix_LoadMUS("config/music/BGM_shooting_park.mp3")) == NULL) {
        printf("failed to load music and chunk.\n");
        Mix_CloseAudio(); // オーディオデバイスの終了
        SDL_Quit();
        exit(-1);
    }	

    if ((BGM_shooting_ingame = Mix_LoadMUS("config/music/BGM_shooting_ingame.mp3")) == NULL) {
        printf("failed to load music and chunk.\n");
        Mix_CloseAudio(); // オーディオデバイスの終了
        SDL_Quit();
        exit(-1);
    }

    Mix_PlayMusic(BGM_loading, -1);


	InitialProc();
	preReadPoints();

	while (running) {
		Uint32 frameStart = SDL_GetTicks();
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				keyDown(event.key.keysym.sym, 0, 0);
				break;
			case SDL_KEYUP:
				keyUp(event.key.keysym.sym, 0, 0);
				break;
			case SDL_MOUSEMOTION:
				passiveMotion(event.motion.x, event.motion.y);
				break;
			case SDL_MOUSEBUTTONDOWN:
				clicked_down(event.motion.x, event.motion.y, event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				clicked_up(event.motion.x, event.motion.y, event.button.button);
				break;
			}
		}
		frameCount++;
		Uint32 currentTime = SDL_GetTicks();
		elapsedSeconds = (currentTime - remainST) / 1000.0f;
		if (currentTime - startTime >= 1000) {
			fps = frameCount / ((currentTime - startTime) / 1000.0f);
			std::cout << "FPS: " << fps << std::endl;
			frameCount = 0;
			startTime = currentTime;
		}
		control_requests();
		SceneController();
		SDL_GL_SwapWindow(window);
		Uint32 frameTime = SDL_GetTicks() - frameStart;
		const int TARGET_FPS = 60; // FireWork最適化により60 FPSに戻す
		if (frameTime < 1000 / TARGET_FPS) {
			SDL_Delay(1000 / TARGET_FPS - frameTime);
		}
	}

	SDL_GL_DeleteContext(glContext);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glDisable(GL_COLOR_MATERIAL_FACE);
	glDisable(GL_COLOR_MATERIAL);

	return 0;
}
