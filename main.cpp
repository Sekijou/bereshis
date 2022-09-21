//dingdongpingpong dude!!

#include "raylib.h"

struct Ball {
	float x, y;
	float speedX, speedY;
	float radius;

	void Draw() {
		DrawCircle((int) x, (int) y, radius, RED);

	}

};



int main() {
	InitWindow(800, 600, "Ding dong ping pong");
	SetWindowState(FLAG_VSYNC_HINT);

	Ball ball;
	ball.x = GetScreenWidth()/2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 100;
	ball.speedY = 300;


	while (!WindowShouldClose()) {
		ball.Draw();
		ball.x += ball.speedX * GetFrameTime();
		ball.y += ball.speedY * GetFrameTime();

		if (ball.y < 0) {
			ball.y = 0;
			ball.speedY *= -1;

		};

		if (ball.y > GetScreenHeight()) {
			ball.y = GetScreenHeight();
			ball.speedY *= -1;
		};


		BeginDrawing();
		
			ClearBackground(BLACK);
			DrawFPS(10,10);

			
			DrawRectangle(50, GetScreenHeight() / 2 - 50, 10, 100, GREEN );
			DrawRectangle(GetScreenWidth() - 50 - 10, GetScreenHeight()/2 - 50, 10, 100, GREEN);
	
			
		EndDrawing();
	}
	CloseWindow();
	return 0;
}