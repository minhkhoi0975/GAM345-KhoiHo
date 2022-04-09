#include <iostream>
#include <vector>
#include "SDL_gpu.h"
#include "NFont_gpu.h"
#include "Random.h"
#include "Vector2.h"
using namespace std;

Random rng;

class Ball
{
public:

	Vector2 position;
	Vector2 velocity;
	float radius;
	SDL_Color color;

	bool outline;

	Ball()
	{
		outline = true;

		position = Vector2(rng.Float(0, 800), rng.Float(0, 600));
		velocity = Vector2(rng.Float(-300, 300), rng.Float(-300, 300));

		radius = rng.Float(10, 30);

		color = GPU_MakeColor(rng.Integer(0, 256), rng.Integer(0, 256), rng.Integer(0, 256), 255);
	}

	Ball(float x, float y)
	{
		outline = true;

		position = Vector2(x, y);
		velocity = Vector2(rng.Float(-300, 300), rng.Float(-300, 300));

		radius = rng.Float(10, 30);

		color = GPU_MakeColor(rng.Integer(0, 256), rng.Integer(0, 256), rng.Integer(0, 256), 255);
	}

	void Tick(float dt)
	{
		position += velocity * dt;
	}

	void Draw(GPU_Target* target)
	{
		GPU_CircleFilled(target, position.x, position.y, radius, color);
		if (outline)
		{
			GPU_SetLineThickness(5);
			GPU_Circle(target, position.x, position.y, radius, GPU_MakeColor(0, 0, 0, 255));
			GPU_SetLineThickness(1);
		}
	}
};

int main(int argc, char* argv[])
{
	GPU_Target* screen = GPU_Init(800, 600, GPU_DEFAULT_INIT_FLAGS);
	if (screen == nullptr)
		return 1;

	SDL_SetWindowTitle(SDL_GetWindowFromID(screen->context->windowID), "Ball Demo");
	
	NFont font;
	font.load("FreeSans.ttf", 14);

	const Uint8* keystates = SDL_GetKeyboardState(nullptr);

	int mx = 0, my = 0;

	float dt = 0.0f;
	Uint32 startTime = SDL_GetTicks();
	Uint32 endTime = 0;

	bool drawing = false;
	vector<Vector2> drawingPoints;

	vector<Ball> balls;
	bool useOutlines = true;
	bool useCollisions = false;
	bool useGravity = false;

	/*for (int i = 0; i < 3000; ++i)
	{
		balls.emplace_back();
	}*/

	SDL_Event event;
	bool done = false;
	while (!done)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				done = true;
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE)
					done = true;
				if (event.key.keysym.sym == SDLK_SPACE)
				{
					useOutlines = !useOutlines;
					for (auto& b : balls)
						b.outline = useOutlines;
				}
				if (event.key.keysym.sym == SDLK_EQUALS)
				{
					for (auto& b : balls)
						b.radius *= 1.3f;
				}
				if (event.key.keysym.sym == SDLK_MINUS)
				{
					for (auto& b : balls)
						b.radius /= 1.3f;
				}
				if (event.key.keysym.sym == SDLK_c)
				{
					useCollisions = !useCollisions;
				}
				if (event.key.keysym.sym == SDLK_g)
				{
					useGravity = !useGravity;
				}
				if (event.key.keysym.sym == SDLK_r)
				{
					balls.clear();
				}
			}
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					drawing = true;
					drawingPoints.clear();
				}
				if (event.button.button == SDL_BUTTON_RIGHT)
				{
					balls.emplace_back(event.button.x, event.button.y);
				}
			}
			if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					// TODO: Gesture recognition
					drawing = false;
				}
			}
		}

		SDL_GetMouseState(&mx, &my);

		// Holding mouse button
		if(drawing)
		{
			/*
			Vector2 mousePosition(mx, my);

			if (drawingPoints.size() == 0 || mousePosition != drawingPoints[drawingPoints.size() - 1])
			{
				drawingPoints.push_back(mousePosition);
				cout << "(" << mousePosition.x << "\t,\t" << mousePosition.y << ")" << endl;
			}
			*/

			// Holding mouse button
			drawingPoints.push_back(Vector2(mx, my));
		}

		if (useGravity)
		{
			for (auto& b : balls)
				b.velocity.y += 1000.0f*dt;
		}

		for (auto& b : balls)
			b.Tick(dt);

		if (useCollisions)
		{
			for (size_t i = 0; i < balls.size() - 1; ++i)
			{
				for (size_t j = i + 1; j < balls.size(); ++j)
				{
					float dx = balls[j].position.x - balls[i].position.x;
					float dy = balls[j].position.y - balls[i].position.y;
					float r = balls[i].radius + balls[j].radius;
					if (fabsf(r) > 0.01f && dx * dx + dy * dy < r * r)
					{
						Vector2 normal(dx, dy);
						normal.Normalize();

						Vector2 tangent(-normal.y, normal.x);
						float dist = sqrtf(dx * dx + dy * dy) - r;
						balls[i].position += normal * dist/2;
						balls[j].position -= normal * dist/2;

						Vector2 biVel(balls[i].velocity.Dot(normal), balls[i].velocity.Dot(tangent));
						Vector2 bjVel(balls[j].velocity.Dot(normal), balls[j].velocity.Dot(tangent));
						
						float m1 = balls[i].radius;
						float m2 = balls[j].radius;
						float biFinalVel = (m1 - m2)/(m1 + m2) * biVel.x + 2*m2/(m1 + m2) * bjVel.x;
						float bjFinalVel = (m2 - m1)/(m1 + m2) * bjVel.x + 2*m1/(m1 + m2) * biVel.x;
						biVel.x = biFinalVel;
						bjVel.x = bjFinalVel;
						balls[i].velocity = biVel.x * normal + biVel.y * tangent;
						balls[j].velocity = bjVel.x * normal + bjVel.y * tangent;
					}
				}
			}
		}

		for (auto& b : balls)
		{
			if (b.position.x < b.radius)
			{
				b.position.x = b.radius;
				b.velocity.x = -b.velocity.x;
			}
			if (b.position.y < b.radius)
			{
				b.position.y = b.radius;
				b.velocity.y = -b.velocity.y;
			}
			if (b.position.x > screen->w - b.radius)
			{
				b.position.x = screen->w - b.radius;
				b.velocity.x = -b.velocity.x;
			}
			if (b.position.y > screen->h - b.radius)
			{
				b.position.y = screen->h - b.radius;
				b.velocity.y = -b.velocity.y;
			}
		}



		GPU_ClearRGB(screen, 255, 255, 255);

		for (auto& b : balls)
			b.Draw(screen);

		// Draw lines
		GPU_SetLineThickness(5.0f);
		for (int i = 1; i < drawingPoints.size(); ++i)
		{
			Vector2 p1 = drawingPoints[i-1];
			Vector2 p2 = drawingPoints[i];
			GPU_Line(screen, p1.x, p1.y, p2.x, p2.y, GPU_MakeColor(255, 0, 0, 255));
		}
		GPU_SetLineThickness(1.0f);

		font.draw(screen, screen->w - 50.0f, 10.0f, NFont::AlignEnum::RIGHT, 
			"Left click: Draw gesture\n"
			"Right click: Create ball\n"
			"Space: Toggle outline\n"
			"+: Size up\n"
			"-: Size down\n"
			"C: Toggle collisions\n"
			"G: Toggle gravity\n"
			"R: Reset");

		GPU_Flip(screen);

		SDL_Delay(1);

		endTime = SDL_GetTicks();
		dt = (endTime - startTime) / 1000.0f;
		startTime = endTime;
	}

	font.free();

	GPU_Quit();

	return 0;
}