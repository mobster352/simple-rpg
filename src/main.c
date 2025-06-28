#include "raylib.h"
#include "raymath.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "player.h"
#include "enemy.h"
#include "sprite.h"
#include "constants.h"
#include "dynamic_array.h"
#include "map.h"

void* concatVector2ToString(const char *string, Vector2 value){
	char buffer[32];
	// Format the vector as (x, y)
    snprintf(buffer, sizeof(buffer), "(%d, %d)", (int)value.x, (int)value.y);
	//Calculate required size for new string
	size_t new_string_len = strlen(string) + strlen(buffer) + 1; //+1 for null terminator
	//Allocate memory for new string
	char *result = (char *)malloc(new_string_len);
	if(result == NULL){
			perror("Failed to allocate memory");
			return NULL;
	}
	//Copy the first string
	strcpy(result, string);
	strcat(result, buffer);
	return result;
}

void drawTextWithVector2(char *text, Vector2 value, int posX, int posY, int fontSize, Color color){
	void *newText = concatVector2ToString(text, value);
	DrawText(newText,posX,posY,fontSize,color);
	free(newText);
}

void updateEnemies(DynamicArray* enemies){
	for(int i=0; i<enemies->size; i++){
		Enemy* e = (Enemy*) da_get(enemies, i);
        updateEnemy(e);
    }
}

void drawEnemies(DynamicArray* enemies, bool debug){
	for(int i=0; i<enemies->size; i++){
		Enemy* e = (Enemy*) da_get(enemies, i);
        drawEnemy(*e, debug);
    }
}

void cleanupEnemies(DynamicArray* enemies){
	for(int i=0; i<enemies->size; i++){
		Enemy* e = (Enemy*) da_get(enemies, i);
        if(e->hp <= 0){
			da_remove(enemies, i);
        }
    }
}

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_UNDECORATED);
	// Create the window and OpenGL context
	InitWindow(1280, 768, "A Simple RPG");
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	Texture background = LoadTexture("Water_Background_color.png");

	Texture playerIdleTexture = LoadTexture("units/blue/warrior/Warrior_Idle.png");
	Texture playerRunTexture = LoadTexture("units/blue/warrior/Warrior_Run.png");
	Texture playerAttack1Texture = LoadTexture("units/blue/warrior/Warrior_Attack1.png");

	Texture enemyIdleTexture = LoadTexture("units/red/warrior/Warrior_Idle.png");

	Animation playerIdleAnimation = createAnimation(IDLE_ANIMATION, playerIdleTexture, 8, 192, 1.2f, true);
	Animation playerRunAnimation = createAnimation(RUN_ANIMATION, playerRunTexture, 6, 192, 1.2f, true);
	Animation playerAttack1Animation = createAnimation(ATTACK1_ANIMATION, playerAttack1Texture, 4, 192, 1.2f, false);

	Animation enemyIdleAnimation = createAnimation(IDLE_ANIMATION, enemyIdleTexture, 8, 192, 1.2f, true);

	Animation playerAnimations[5] = {
		playerIdleAnimation,
		playerRunAnimation,
		playerAttack1Animation
	};

	SetTargetFPS(60);

	Map* maps = initMaps();
	int currentMap = START_MAP;
	
	Player player = createPlayer(100, 100, 192, 192, playerIdleAnimation);
	
	Enemy e = createEnemy(400, 400, 192, 192, enemyIdleAnimation);

	DynamicArray* enemies = da_create(sizeof(Enemy), 1);
	da_push(enemies, &e);

	Camera2D playerCamera;
	playerCamera.target = player.transform2D.position;
	playerCamera.zoom = 1.0f;
	playerCamera.rotation = 0.0f;
	playerCamera.offset = Vector2Zero();

	int index = 0;
	float animationTimer = 0.0f;
	float animationSpeed = 0.1f;

	bool debug = false;

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		float cameraX = (player.transform2D.position.x-GetScreenWidth()/2) + player.transform2D.width/2;
		float cameraY = (player.transform2D.position.y-GetScreenHeight()/2) + player.transform2D.height/2;
		playerCamera.target = (Vector2){cameraX, cameraY};  

		if(IsKeyPressed(KEY_F2)){
			e.transform2D.position = GetMousePosition();
			da_push(enemies, &e);
		}

		cleanupEnemies(enemies);
		updateEnemies(enemies);
		updatePlayer(&player, playerAnimations, &index, enemies);
		
		// drawing
		BeginDrawing();
		// BeginMode2D(playerCamera);
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);
		DrawTexturePro(background,(Rectangle){0,0, GetScreenWidth(), GetScreenHeight()},(Rectangle){0,0, GetScreenWidth(), GetScreenHeight()},Vector2Zero(),0.0f,WHITE);
		
		DrawMap(maps, currentMap, debug);
		
		// drawTextWithVector2("Pos: ", GetMousePosition(), playerCamera.target.x + GetScreenWidth() - 170, playerCamera.target.y + GetScreenHeight() - 20, 20, WHITE); //this is for follow camera logic
		drawTextWithVector2("Pos: ", GetMousePosition(), GetScreenWidth() - 170, GetScreenHeight() - 20, 20, WHITE);
		
		drawEnemies(enemies, debug);

		PlayAnimation(&player.sprite, playerAnimations, &index, &animationTimer);
		drawPlayerHitbox(player, &debug);
		
		DrawFPS(GetScreenWidth()-40, 20);
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		// EndMode2D();
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(background);
	UnloadTexture(playerIdleTexture);
	UnloadTexture(playerRunTexture);
	UnloadTexture(playerAttack1Texture);
	UnloadTexture(enemyIdleTexture);

	unloadMaps(maps);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
