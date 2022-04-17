// $1 Single-Stroke Gesture Recognizer.
// Programmer: Khoi Ho
// Credits: The Cherno for the Save File dialog (https://www.youtube.com/watch?v=zn7N7zHgCcs&ab_channel=TheCherno)

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <filesystem>
#include <sstream>
#include <windows.h>
#include "SDL_gpu.h"
#include "SDL_syswm.h"
#include "NFont_gpu.h"
#include "Random.h"
#include "Vector2.h"
using namespace std;

const float PI = 2.0f * acosf(0.0f);

// ---------------------
// File system utils
// ---------------------

// Open the save dialog. Return the file path.
string SaveFileDialog(SDL_Window* window, const char* filter)
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
	return string();
}

// Open the open file dialog. Return the file path.
string OpenFileDialog(SDL_Window* window, const char* filter)
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
	if (GetOpenFileNameA(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}
	return string();
}

// Open a template file.
vector<Vector2> OpenTemplateFile(const string& fileName)
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
	else
	{
		cerr << "Cannot open the template file!" << endl;
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

// ---------------------------------------------------------------------
// Get all files in a folder.
// ---------------------------------------------------------------------

vector<string> GetAllFileNames(const string& templateFolderPath, const string& filter = "*.*")
{
	vector<string> names;

	/*
	for (const auto& entry : std::filesystem::directory_iterator(templateFolderPath))
	{
		std::cout << entry.path() << std::endl;
	}
	*/

	string searchPath = templateFolderPath + "/" + filter;

	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(searchPath.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

// -------------------------------------------
// Utils
// -------------------------------------------

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

// -------------------------------------------
// Step 1
// -------------------------------------------

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

	// Fix the bug in which the size of newPoints does not match n.
	if (newPoints.size() < n)
	{
		newPoints.push_back(points[points.size() - 1]);
	}

	return newPoints;
}

// -------------------------------------------
// Step 2
// -------------------------------------------

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

// -------------------------------------------
// Step 3
// -------------------------------------------

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

// -------------------------------------------
// Step 4
// -------------------------------------------

// Find the average distance between 2 repsective points of two strokes.
float PathDistance(const vector<Vector2>& points1, const vector<Vector2>& points2)
{
	if (points1.size() != points2.size())
	{
		throw exception("Error: Two strokes have different sizes. Make sure to resample them before finding the path distance.");
	}

	float distance = 0;

	for (int i = 0; i < points1.size(); ++i)
	{
		distance += Vector2::Distance(points1[i], points2[i]);
	}

	return distance / points1.size();
}

float DistanceAtAngle(const vector<Vector2>& points1, const vector<Vector2>& points2, const float& angle)
{
	vector<Vector2> newPoints = RotateBy(points1, angle);

	float distance = PathDistance(newPoints, points2);

	return distance;
}

float DistanceAtBestAngle(const vector<Vector2>& points1, const vector<Vector2>& points2, float angleAlpha, float angleBeta, const float& angleDelta)
{
	static const float phi = 0.5 * (-1 + sqrt(5));

	float x1 = phi * angleAlpha + (1 - phi) * angleBeta;
	float f1 = DistanceAtAngle(points1, points2, x1);

	float x2 = (1 - phi) * angleAlpha + phi * angleBeta;
	float f2 = DistanceAtAngle(points1, points2, x2);

	while (abs(angleAlpha - angleBeta) > angleDelta)
	{
		if (f1 < f2)
		{
			angleBeta = x2;
			x2 = x1;
			f2 = f1;
			x1 = phi * angleAlpha + (1 - phi) * angleBeta;
			f1 = DistanceAtAngle(points1, points2, x1);
		}
		else
		{
			angleAlpha = x1;
			x1 = x2;
			f1 = f2;
			x2 = (1 - phi) * angleAlpha + phi * angleBeta;
			f2 = DistanceAtAngle(points1, points2, x2);
		}
	}

	return f1 < f2 ? f1 : f2;
}

pair<string, float> Recognize(const vector<Vector2>& points, const map<string, vector<Vector2>>& strokeTemplates, const float& size = 250)
{
	pair<string, float> matchingStroke;

	float b = numeric_limits<float>::infinity();

	for (const pair<string, vector<Vector2>>& strokeTemplate : strokeTemplates)
	{
		float distance = DistanceAtBestAngle(points, strokeTemplate.second, -0.25f * PI, 0.25f * PI, PI / 90.0f);
		
		if (distance < b)
		{
			b = distance;
			matchingStroke.first = strokeTemplate.first;
		}

		float score = 1 - b / 0.5f * sqrt(size * size + size * size);
		matchingStroke.second = score;
	}

	return matchingStroke;
}

int main(int argc, char* argv[])
{
	// Initialize SDL_GPU.
	GPU_Target* screen = GPU_Init(800, 600, GPU_DEFAULT_INIT_FLAGS);
	if (screen == nullptr)
		return 1;

	// Create a window.
	SDL_SetWindowTitle(SDL_GetWindowFromID(screen->context->windowID), "$1 Single-Stroke Gesture Recognizer");
	
	// Load a font to display text on screen.
	NFont font;
	font.load("FreeSans.ttf", 14);

	const Uint8* keystates = SDL_GetKeyboardState(nullptr);

	// Coordinates of the mouse.
	int mouseX = 0, mouseY = 0;

	bool drawing = false;
	vector<Vector2> drawingPoints;

	// The stroke that matches the drawn stroke.
	// + The first value is the file name of the matching stroke.
	// + The second value is the score.
	pair<string, float> matchingStroke;

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
				// Press ESC to exit the program.
				if (event.key.keysym.sym == SDLK_ESCAPE)
					done = true;

				// Press S to save the template to a file.
				if (event.key.keysym.sym == SDLK_s)
				{
					// Cannot save the drawn stroke if it is too short.
					if (drawingPoints.size() < 10)
					{
						cout << "Cannot save the stroke: The stroke is too short." << endl;
					}
					else
					{
						string fileName = SaveFileDialog(SDL_GetWindowFromID(screen->context->windowID), "Stroke Template (*.stroke)\0*.stroke\0");



						SaveFile(fileName, drawingPoints);

						/*
						// Test reading template.
						cout << fileName << endl;

						vector<Vector2> stroke(OpenTemplateFile(fileName));
						for (int i = 0; i < stroke.size(); ++i)
						{
							cout << stroke[i].x << " " << stroke[i].y << endl;
						}
						*/
					}
				}

				// Press O to open an existing template.
				if (event.key.keysym.sym == SDLK_o)
				{
					string fileName = OpenFileDialog(SDL_GetWindowFromID(screen->context->windowID), "Stroke Template (*.stroke)\0*.stroke\0");
					cout << fileName << endl;

					drawingPoints.clear();
					drawingPoints = OpenTemplateFile(fileName);
				}

				// Press T to resample the drawn stroke.
				if (event.key.keysym.sym == SDLK_t)
				{
					drawingPoints = Resample(drawingPoints);
					drawingPoints = RotateBy(drawingPoints, -IndicativeAngle(drawingPoints));
					drawingPoints = ScaleTo(drawingPoints);
					drawingPoints = TranslateTo(drawingPoints, Vector2(400, 300));
				}
			}

			// Hold left mouse to draw.
			if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					drawing = true;
					drawingPoints.clear();
				}
			}

			// Release left mouse to stop drawing.
			if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					drawing = false;

					// Cannot recognize the drawn stroke if it is too short.
					if (drawingPoints.size() < 10)
					{
						cout << "The stroke is too short." << endl;
					}
					else
					{
						// Read the stroke templates.
						map<string, vector<Vector2>> strokes;

						for (const string& fileName : GetAllFileNames("Stroke Templates", "*.stroke"))
						{
							strokes[fileName] = OpenTemplateFile("Stroke Templates/" + fileName);
						}

						if (strokes.size() > 0)
						{

							// Process the drawn stroke.
							vector<Vector2> drawingPointsCopy = drawingPoints;
							drawingPointsCopy = Resample(drawingPointsCopy);
							drawingPointsCopy = RotateBy(drawingPointsCopy, -IndicativeAngle(drawingPointsCopy));
							drawingPointsCopy = ScaleTo(drawingPointsCopy);
							drawingPointsCopy = TranslateTo(drawingPointsCopy);

							// cout << "Drawing stroke size: " << drawingPointsCopy.size() << endl;

							// Process the strokes from the template files.
							map<string, vector<Vector2>>::iterator it = strokes.begin();
							while (it != strokes.end())
							{
								it->second = Resample(it->second);
								it->second = RotateBy(it->second, -IndicativeAngle(it->second));
								it->second = ScaleTo(it->second);
								it->second = TranslateTo(it->second);

								// cout << it->first << " size: " << it->second.size() << endl;

								++it;
							}

							// Recognize the pattern.
							matchingStroke = Recognize(drawingPointsCopy, strokes);
							cout << "Matching stroke: " << matchingStroke.first << "\t" << "Score: " << matchingStroke.second << endl;
						}
					}
				}
			}
		}

		SDL_GetMouseState(&mouseX, &mouseY);

		// Holding mouse button
		if(drawing)
		{
			Vector2 mousePosition(mouseX, mouseY);

			// Don't at the latest cursor position to the array if it is not moving.
			if (drawingPoints.size() == 0 || mousePosition != drawingPoints[drawingPoints.size() - 1])
			{
				drawingPoints.push_back(mousePosition);
				//cout << mousePosition.x << " " << mousePosition.y << endl;
			}
		}

		GPU_ClearRGB(screen, 255, 255, 255);

		// Draw the starting point.
		if (drawingPoints.size() > 0)
		{
			GPU_Circle(screen, drawingPoints[0].x, drawingPoints[0].y, 5.0f, GPU_MakeColor(0, 0, 255, 255));
		}

		// Draw lines
		GPU_SetLineThickness(5.0f);
		for (int i = 1; i < drawingPoints.size(); ++i)
		{
			Vector2 p1 = drawingPoints[i-1];
			Vector2 p2 = drawingPoints[i];
			GPU_Line(screen, p1.x, p1.y, p2.x, p2.y, GPU_MakeColor(255, 0, 0, 255));
		}
		GPU_SetLineThickness(1.0f);

		// Draw the ending point.
		if (drawingPoints.size() > 0)
		{
			const int lastPoint = drawingPoints.size() - 1;
			GPU_Circle(screen, drawingPoints[lastPoint].x, drawingPoints[lastPoint].y, 5.0f, GPU_MakeColor(0, 122, 0, 255));
		}

		font.draw(screen, screen->w - 50.0f, 10.0f, NFont::AlignEnum::RIGHT, 
			"Left click: Draw gesture\n"
			"S: Save template\n"
			"O: View an existing template\n"
		    "T: Resample the stroke");

		
		if (!matchingStroke.first.empty())
		{
			stringstream matchingStrokeSS;
			matchingStrokeSS << "Matching stroke: " << matchingStroke.first;
			font.draw(screen, 10.0f, screen->h - 20, NFont::AlignEnum::LEFT, matchingStrokeSS.str().c_str());
		}

		GPU_Flip(screen);

		SDL_Delay(1);
	}

	font.free();

	GPU_Quit();

	return 0;
}