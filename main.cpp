//dingdongpingpong dude!!

#include "raylib.h"

struct Paddle {
	float x, y;
	float speedY;
	float width, height;

	Rectangle GetRect() {
		return Rectangle {x - width / 2, y - height /2, 10, 100,};
	};


	void Draw() {
		DrawRectangleRec(GetRect(), GREEN);
	}
};


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

	Paddle leftPaddle;
	leftPaddle.x = 50;
	leftPaddle.y = GetScreenHeight() / 2 - 50;
	leftPaddle.width = 10;
	leftPaddle.height = 100;
	leftPaddle.speedY = 600;

	Paddle rightPaddle;
	rightPaddle.x = GetScreenWidth() - 50 - 10;
	rightPaddle.y = GetScreenHeight() / 2 - 50;
	rightPaddle.width = 10;
	rightPaddle.height = 100;
	rightPaddle.speedY = 600;


	Ball ball;
	ball.x = GetScreenWidth()/2.0f;
	ball.y = GetScreenHeight() / 2.0f;
	ball.radius = 5;
	ball.speedX = 300;
	ball.speedY = 300;


	const char* winnerText = nullptr;


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

		if (IsKeyDown(KEY_W)) {
			leftPaddle.y -= leftPaddle.speedY * GetFrameTime();
		}

		if (IsKeyDown(KEY_S)) {
			leftPaddle.y += leftPaddle.speedY * GetFrameTime();
		}

		if (IsKeyDown(KEY_UP)) {
			rightPaddle.y -= rightPaddle.speedY * GetFrameTime();
		}

		if (IsKeyDown(KEY_DOWN)) {
			rightPaddle.y += rightPaddle.speedY * GetFrameTime();
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius,
			leftPaddle.GetRect())) {

			if (ball.speedX < 0) {
				ball.speedX *= -1.1;
				ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2) * ball.speedX;
			}
		}

		if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius,
			rightPaddle.GetRect())) {
			if (ball.speedX > 0) {
			ball.speedX *= -1.1;
			ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
		}
	}

		if (ball.x < 0) {
			leftPaddle.y = 300;
			rightPaddle.y = 300;
			winnerText = "Player 2 wins!!";
		}
		if (ball.x > GetScreenWidth()) {
			 leftPaddle.y = 300;
			 rightPaddle.y = 300;
			winnerText = "Player 1 wins!!";
		};

		if (winnerText) {
			int textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
		}

		if (winnerText && IsKeyPressed(KEY_SPACE)) {
			ball.x = GetScreenWidth() / 2;
			ball.y = GetScreenHeight() / 2;
			ball.speedX = 300;
			ball.speedY = 300;
			winnerText = nullptr;
		}

		BeginDrawing();
		
			ClearBackground(BLACK);
			DrawFPS(10,10);

			
			leftPaddle.Draw();
			rightPaddle.Draw();
			
		

			

		EndDrawing();
	}
	CloseWindow();
	return 0;
}