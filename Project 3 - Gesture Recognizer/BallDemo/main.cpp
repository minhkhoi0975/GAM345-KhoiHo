// $1 Single-Stroke Gesture Recognizer.
// Programmer: Khoi Ho
// Credits: The Cherno for the Save File dialog (https://www.youtube.com/watch?v=zn7N7zHgCcs&ab_channel=TheCherno)

#include <fstream>
#include <iostream>
#include <vector>
#include <windows.h>
#include "SDL_gpu.h"
#include "SDL_syswm.h"
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

// Open the save dialog. Return the file path.
string SaveDialog(SDL_Window* window, const char* filter)
{
	// Get the info of the native window.
	static SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window, &wmInfo);

	// Open the save file dialog.
	OPENFILENAMEA ofn;
	char szFile[260] = { 0 };
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = wmInfo.info.win.window;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
	if (GetSaveFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}
	return std::string();
}

// Open a template file.
vector<Vector2> OpenFile(const string& fileName)
{
	vector<Vector2> stroke;

	fstream inputFile(fileName);
	if (inputFile)
	{
		Vector2 position;

		while (inputFile >> position.x >> position.y)
		{
			stroke.push_back(position);
		}

		inputFile.close();
	}

	return stroke;
}

// Save the stroke to a template file. Return true if the file is successfully saved.
bool SaveFile(const string& fileName, const vector<Vector2>& stroke)
{
	fstream outputFile(fileName, ofstream::out | ofstream::trunc);

	if (outputFile)
	{
		for (int i = 0; i < stroke.size(); i++)
		{
			outputFile << stroke[i].x << "\t" << stroke[i].y << endl;
		}

		outputFile.close();

		return true;
	}

	return false;
}

// Find the total length of the lines between the points.
float PathLength(const vector<Vector2>& points)
{
	float length = 0;
	int pointCount = points.size();

	for (int i = 1; i < pointCount; ++i)
	{
		length += Vector2::Distance(points[i - 1], points[i]);
	}

	return length;
}

// Resample the points.
// n is the number of points after resample.
vector<Vector2> Resample(vector<Vector2> points, int n = 64)
{
	vector<Vector2> newPoints;
	newPoints.reserve(n);

	float I = PathLength(points) / (n - 1);
	float D = 0;

	newPoints.push_back(points[0]);
	for (int i = 1; i < points.size(); ++i)
	{
		float d = Vector2::Distance(points[i - 1], points[i]);

		if (D + d >= I)
		{
			Vector2 newPoint;
			newPoint.x = points[i - 1].x + ((I - D) / d) * (points[i].x - points[i - 1].x);
			newPoint.y = points[i - 1].y + ((I - D) / d) * (points[i].y - points[i - 1].y);

			newPoints.push_back(newPoint);

			points.insert(points.begin() + i, newPoint);

			D = 0;
		}
		else
		{
			D += d;
		}
	}

	return newPoints;
}

// Get the centroid of the points.
Vector2 Centroid(const vector<Vector2>& points)
{
	float sumX = 0;
	float sumY = 0;
	int pointCount = points.size();

	for (int i = 0; i < pointCount; ++i)
	{
		sumX += points[i].x;
		sumY += points[i].y;
	}

	return Vector2(sumX / pointCount, sumY / pointCount);
}

// Get the bounding box of the points.
void BoundingBox(const vector<Vector2>& points, Vector2& topLeftCorner, Vector2& bottomRightCorner)
{
	float minX = points[0].x;
	float minY = points[0].y;
	float maxX = points[0].x;
	float maxY = points[0].y;
	int pointCount = points.size();

	for (int i = 1; i < pointCount; ++i)
	{
		if (points[i].x < minX)
		{
			minX = points[i].x;
		}
		else if (points[i].x > maxX)
		{
			maxX = points[i].x;
		}

		if (points[i].y < minY)
		{
			minY = points[i].y;
		}
		else if (points[i].y > maxY)
		{
			maxY = points[i].y;
		}
	}

	topLeftCorner.x = minX;
	topLeftCorner.y = minY;

	bottomRightCorner.x = maxX;
	bottomRightCorner.y = maxY;
}

// Find the indicative angle from the centroid to the first point.
float IndicativeAngle(const vector<Vector2>& points)
{
	Vector2 centroid = Centroid(points);
	return atan2(centroid.y - points[0].y, centroid.x - points[0].x);
}

// Rotate all the points around their centroid by an angle.
vector<Vector2> RotateBy(const vector<Vector2>& points, const float& angle)
{
	vector<Vector2> newPoints;

	Vector2 centroid = Centroid(points);

	for (const Vector2& point : points)
	{
		Vector2 newPoint;
		newPoint.x = (point.x - centroid.x) * cos(angle) - (point.y - centroid.y) * sin(angle) + centroid.x;
		newPoint.y = (point.x - centroid.x) * sin(angle) + (point.y - centroid.y) * cos(angle) + centroid.y;

		newPoints.push_back(newPoint);
	}

	return newPoints;
}

vector<Vector2> ScaleTo(const vector<Vector2>& points, const int& size = 250)
{
	vector<Vector2> newPoints;

	// Get the bounding box of the points.
	Vector2 topLeftCorner;
	Vector2 bottomRightCorner;
	BoundingBox(points, topLeftCorner, bottomRightCorner);

	// Get the size of the bounding box.
	float width = bottomRightCorner.x - topLeftCorner.x;
	float height = bottomRightCorner.y - topLeftCorner.y;

	for (const Vector2& point : points)
	{
		Vector2 newPoint;
		newPoint.x = point.x * size / width;
		newPoint.y = point.y * size / height;

		newPoints.push_back(newPoint);
	}

	return newPoints;
}

vector<Vector2> TranslateTo(const vector<Vector2>& points, const Vector2& origin = Vector2())
{
	vector<Vector2> newPoints;
	newPoints.reserve(points.size());

	Vector2 centroid = Centroid(points);

	for (const Vector2& point : points)
	{
		Vector2 newPoint;
		newPoint.x = point.x + origin.x - centroid.x;
		newPoint.y = point.y + origin.y - centroid.y;

		newPoints.push_back(newPoint);
	}

	return newPoints;
}

int main(int argc, char* argv[])
{
	GPU_Target* screen = GPU_Init(800, 600, GPU_DEFAULT_INIT_FLAGS);
	if (screen == nullptr)
		return 1;

	SDL_SetWindowTitle(SDL_GetWindowFromID(screen->context->windowID), "$1 Single-Stroke Gesture Recognizer");
	
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

				// Save the template to a file.
				if (event.key.keysym.sym == SDLK_s)
				{
					string fileName = SaveDialog(SDL_GetWindowFromID(screen->context->windowID), "Stroke Template (*.stroke)\0*.stroke\0");

					SaveFile(fileName, drawingPoints);

					cout << fileName << endl;

					// Test reading template.
					vector<Vector2> stroke(OpenFile(fileName));
					for (int i = 0; i < stroke.size(); ++i)
					{
						cout << stroke[i].x << " " << stroke[i].y << endl;
					}
				}

				// Resample the stroke.
				if (event.key.keysym.sym == SDLK_t)
				{
					drawingPoints = Resample(drawingPoints);

					/*
					float indicativeAngle = IndicativeAngle(drawingPoints);
					drawingPoints = RotateBy(drawingPoints, indicativeAngle);

					drawingPoints = ScaleTo(drawingPoints);
					drawingPoints = TranslateTo(drawingPoints);
					*/
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
			Vector2 mousePosition(mx, my);

			if (drawingPoints.size() == 0 || mousePosition != drawingPoints[drawingPoints.size() - 1])
			{
				drawingPoints.push_back(mousePosition);
				cout << mousePosition.x << " " << mousePosition.y << endl;
			}
			
			// Holding mouse button
			//drawingPoints.push_back(Vector2(mx, my));
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
			"R: Reset\n"
			"S: Save template\n"
		    "T: Resample the stroke");

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