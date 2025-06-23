#include "raylib.h"
#include "raymath.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "player.h"
#include "sprite.h"

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

	Texture playerIdleTexture = LoadTexture("Warrior_Idle.png");

	SetTargetFPS(60);
	
	Player player = createPlayer(100,100);
	Sprite playerSprite = createSprite(
		createAnimation(0, playerIdleTexture, 8, 192),
		(Rectangle){0,0,192,192},
		(Rectangle){player.transform2D.position.x, player.transform2D.position.y, 192,192},
		Vector2Zero(),
		0.0f,
		WHITE
	);
	changeSprite(&player, playerSprite);

	Camera2D playerCamera;
	playerCamera.target = player.transform2D.position;
	playerCamera.zoom = 1.0f;
	playerCamera.rotation = 0.0f;
	playerCamera.offset = Vector2Zero();

	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		float cameraX = (player.sprite.dest.x-GetScreenWidth()/2) + player.sprite.dest.width/2;
		float cameraY = (player.sprite.dest.y-GetScreenHeight()/2) + player.sprite.dest.height/2;
		playerCamera.target = (Vector2){cameraX, cameraY};  
		
		// drawing
		BeginDrawing();
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);
		drawTextWithVector2("Pos: ", GetMousePosition(), GetScreenWidth()-170, GetScreenHeight()-20, 20, WHITE);
		
		BeginMode2D(playerCamera);

		drawPlayerHitbox(player);

		int animation = 0;
		int index = 0;
		bool isOnceAnimationPlaying = false;
		float animationTimer = 0;
		float animationSpeed = 100;
		bool loop = false;
		PlayAnimation(player.sprite, &animation, &index, &isOnceAnimationPlaying, &animationTimer, animationSpeed, loop);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndMode2D();
		
		EndDrawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(playerIdleTexture);

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
