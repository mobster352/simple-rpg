#include "raylib.h"
#include "raymath.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "player.h"
#include "sprite.h"
#include "constants.h"

void* concatVector2ToString(const char *string, Vector2 value){
	char buffer[32];
	// Format the vector as (x, y)
    snprintf(buffer, sizeof(buffer), "(%d, %d)", (int)value.x, (int)value.y);
    // Calculate required size for new string
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

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_UNDECORATED);
	// Create the window and OpenGL context
	InitWindow(1280, 768, "A Simple RPG");
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	Texture background = LoadTexture("Water_Background_color.png");
	Texture map = LoadTexture("map.png");
	Texture playerIdleTexture = LoadTexture("Warrior_Idle.png");
	Texture playerRunTexture = LoadTexture("Warrior_Run.png");
	Texture playerAttack1Texture = LoadTexture("Warrior_Attack1.png");

	Animation playerIdleAnimation = createAnimation(IDLE_ANIMATION, playerIdleTexture, 8, 192, 1.2f, true);
	Animation playerRunAnimation = createAnimation(RUN_ANIMATION, playerRunTexture, 6, 192, 1.2f, true);
	Animation playerAttack1Animation = createAnimation(ATTACK1_ANIMATION, playerAttack1Texture, 4, 192, 1.2f, false);

	Animation playerAnimations[5] = {
		playerIdleAnimation,
		playerRunAnimation,
		playerAttack1Animation
	};

	SetTargetFPS(60);
	
	Player player = createPlayer(100,100,192,192);
	Sprite playerSprite = createSprite(
		playerIdleAnimation,
		(Rectangle){0,0,192,192},
		(Rectangle){
			player.transform2D.position.x, 
			player.transform2D.position.y, 
			playerIdleAnimation.size/playerIdleAnimation.divisor, 
			playerIdleAnimation.size/playerIdleAnimation.divisor, 
		},
		Vector2Zero(),
		0.0f,
		WHITE
	);
	changeSprite(&player, playerSprite);
	// changeAnimation(&player, playerRunAnimation);

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

		updatePlayer(&player, playerAnimations, &index);
		
		// drawing
		BeginDrawing();
		BeginMode2D(playerCamera);
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);
		DrawTexturePro(background,(Rectangle){0,0, GetScreenWidth(), GetScreenHeight()},(Rectangle){0,0, GetScreenWidth(), GetScreenHeight()},Vector2Zero(),0.0f,WHITE);
		DrawTexture(map,0,0,WHITE);
		drawTextWithVector2("Pos: ", GetMousePosition(), playerCamera.target.x + GetScreenWidth() - 170, playerCamera.target.y + GetScreenHeight() - 20, 20, WHITE);
		
		PlayAnimation(&player.sprite, playerAnimations, &index, &animationTimer);
		drawPlayerHitbox(player, &debug);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndMode2D();
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(background);
	UnloadTexture(map);
	UnloadTexture(playerIdleTexture);
	UnloadTexture(playerRunTexture);
	UnloadTexture(playerAttack1Texture);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
