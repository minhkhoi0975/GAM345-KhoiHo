#include <iostream>
#include <fstream>
#include <chrono>
#include "Vector.h"
#include "LinkedList.h"
#include "Random.h"

// Generate a vector and a linked list whose elements are the same.
void GenerateVectorAndLinkedList(Vector<int>& vector, LinkedList<int>& linkedList, const int& n, Random& random)
{
	vector.Clear();
	linkedList.Clear();

	vector.Reserve(n);

	for (int i = 0; i < n; i++)
	{
		int value = random.Integer(0, n-1);
		vector.PushBack(value);
		linkedList.PushBack(value);
	}
}

void PrintVector(Vector<int>& vector)
{
	std::cout << "Vector's elements: ";
	if (vector.Size() == 0)
	{
		std::cout << "none";
	}
	else
	{
		for (int i = 0; i < vector.Size(); i++)
		{
			std::cout << vector[i] << ' ';
		}
	}
	std::cout << std::endl;
}

void PrintLinkedList(LinkedList<int>& linkedList)
{
	std::cout << "Linked list's elements: ";

	if (linkedList.Size() == 0)
	{
		std::cout << "none";
	}
	else
	{
		for (int i = 0; i < linkedList.Size(); i++)
		{
			std::cout << linkedList[i] << ' ';
		}
	}
	std::cout << std::endl;
}

void TestGeneratingVectorAndLinkedList(Vector<int>& vector, LinkedList<int>& linkedList, Random& random)
{
	// Test generating a vector and a linked list.
	GenerateVectorAndLinkedList(vector, linkedList, 10, random);
	PrintVector(vector);
	PrintLinkedList(linkedList);

	GenerateVectorAndLinkedList(vector, linkedList, 20, random);
	PrintVector(vector);
	PrintLinkedList(linkedList);

	GenerateVectorAndLinkedList(vector, linkedList, 30, random);
	PrintVector(vector);
	PrintLinkedList(linkedList);
}

// Generate the data file for the At() function.
bool GenerateDataAt(const std::string& dataFileName, const int& minN, const int& maxN, Random& random)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);

	if (!dataFile)
		return false;

	dataFile << "#n\tVector(ns)\tLinkedList(ns)" << std::endl;

	for (int n = minN; n <= maxN; n++)
	{
		// Generate a vector and a linked list of size n.
		Vector<int> vector;
		LinkedList<int> linkedList;
		GenerateVectorAndLinkedList(vector, linkedList, n, random);

		// Measure the average time of the same task in each data structure.
		long long vertexAverageTime = 0;
		long long linkedListAverageTime = 0;

		for (int i = 0; i < 100; i++)
		{
			int index = random.Integer(0, n - 1);

			auto vectorStartTime = std::chrono::high_resolution_clock::now();
			vector.At(index);
			auto vectorEndTime = std::chrono::high_resolution_clock::now();
			auto vertexTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(vectorEndTime - vectorStartTime).count();
			vertexAverageTime += vertexTimeInterval;

			auto linkedListStartTime = std::chrono::high_resolution_clock::now();
			linkedList.At(index);
			auto linkedListEndTime = std::chrono::high_resolution_clock::now();
			auto linkedListTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(linkedListEndTime - linkedListStartTime).count();
			linkedListAverageTime += linkedListTimeInterval;
		}

		vertexAverageTime /= 100;
		linkedListAverageTime /= 100;

		// Write the average times to the file.
		dataFile << n << '\t' << vertexAverageTime << '\t' << linkedListAverageTime << '\n';
	}

	dataFile.close();

	return true;
}

// Generate the script file for the At() function.
bool GenerateScriptAt(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileName)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return false;

	// Print out the parameters.
	scriptFile
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileName << "'" << std::endl
		<< std::endl
		<< "set title 'Average Completion Time of At() vs. Size of Data Set for Vector and LinkedList'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Vector' lw 1 with lines, \"" << dataFileName << "\" using 1:3 title 'Linked List' lw 1 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return true;
}

// Generate the data file for the PushFront() function.
bool GenerateDataPushFront(const std::string& dataFileName, const int& minN, const int& maxN, Random& random)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);

	if (!dataFile)
		return false;

	dataFile << "#n\tVector(ns)\tLinkedList(ns)" << std::endl;

	for (int n = minN; n <= maxN; n++)
	{
		// Generate a vector and a linked list of size n.
		Vector<int> vector;
		LinkedList<int> linkedList;
		GenerateVectorAndLinkedList(vector, linkedList, n, random);

		// Measure the average time of the same task in each data structure.
		long long vertexAverageTime = 0;
		long long linkedListAverageTime = 0;

		for (int i = 0; i < 100; i++)
		{
			int value = random.Integer(0, n - 1);

			auto vectorStartTime = std::chrono::high_resolution_clock::now();
			vector.PushFront(value);
			auto vectorEndTime = std::chrono::high_resolution_clock::now();
			auto vertexTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(vectorEndTime - vectorStartTime).count();
			vertexAverageTime += vertexTimeInterval;

			auto linkedListStartTime = std::chrono::high_resolution_clock::now();
			linkedList.PushFront(value);
			auto linkedListEndTime = std::chrono::high_resolution_clock::now();
			auto linkedListTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(linkedListEndTime - linkedListStartTime).count();
			linkedListAverageTime += linkedListTimeInterval;
		}

		vertexAverageTime /= 100;
		linkedListAverageTime /= 100;

		// Write the average times to the file.
		dataFile << n << '\t' << vertexAverageTime << '\t' << linkedListAverageTime << '\n';
	}

	dataFile.close();

	return true;
}

// Generate the script file for the PushFront() function.
bool GenerateScriptPushFront(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileName)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return false;

	// Print out the parameters.
	scriptFile
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileName << "'" << std::endl
		<< std::endl
		<< "set title 'Average Completion Time of PushFront() vs. Size of Data Set for Vector and LinkedList'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Vector' lw 1 with lines, \"" << dataFileName << "\" using 1:3 title 'Linked List' lw 1 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return true;
}

// Generate the data file for the PushFront() function.
bool GenerateDataPushBack(const std::string& dataFileName, const int& minN, const int& maxN, Random& random)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);

	if (!dataFile)
		return false;

	dataFile << "#n\tVector(ns)\tLinkedList(ns)" << std::endl;

	for (int n = minN; n <= maxN; n++)
	{
		// Generate a vector and a linked list of size n.
		Vector<int> vector;
		LinkedList<int> linkedList;
		GenerateVectorAndLinkedList(vector, linkedList, n, random);

		// Measure the average time of the same task in each data structure.
		long long vertexAverageTime = 0;
		long long linkedListAverageTime = 0;

		for (int i = 0; i < 100; i++)
		{
			int value = random.Integer(0, n - 1);

			auto vectorStartTime = std::chrono::high_resolution_clock::now();
			vector.PushBack(value);
			auto vectorEndTime = std::chrono::high_resolution_clock::now();
			auto vertexTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(vectorEndTime - vectorStartTime).count();
			vertexAverageTime += vertexTimeInterval;

			auto linkedListStartTime = std::chrono::high_resolution_clock::now();
			linkedList.PushBack(value);
			auto linkedListEndTime = std::chrono::high_resolution_clock::now();
			auto linkedListTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(linkedListEndTime - linkedListStartTime).count();
			linkedListAverageTime += linkedListTimeInterval;
		}

		vertexAverageTime /= 100;
		linkedListAverageTime /= 100;

		// Write the average times to the file.
		dataFile << n << '\t' << vertexAverageTime << '\t' << linkedListAverageTime << '\n';
	}

	dataFile.close();

	return true;
}

// Generate the script file for the PushFront() function.
bool GenerateScriptPushBack(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileName)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return false;

	// Print out the parameters.
	scriptFile
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileName << "'" << std::endl
		<< std::endl
		<< "set title 'Average Completion Time of PushBack() vs. Size of Data Set for Vector and LinkedList'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Vector' lw 1 with lines, \"" << dataFileName << "\" using 1:3 title 'Linked List' lw 1 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return true;
}

// Generate the data file for the EraseAt() function.
bool GenerateDataEraseAt(const std::string& dataFileName, const int& minN, const int& maxN, Random& random)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);

	if (!dataFile)
		return false;

	dataFile << "#n\tVector(ns)\tLinkedList(ns)" << std::endl;

	for (int n = minN; n <= maxN; n++)
	{
		// Generate a vector and a linked list of size n.
		Vector<int> vector;
		LinkedList<int> linkedList;
		GenerateVectorAndLinkedList(vector, linkedList, n, random);

		// Measure the average time of the same task in each data structure.
		long long vertexAverageTime = 0;
		long long linkedListAverageTime = 0;

		for (int i = 0; i < 100; i++)
		{
			if (vector.Size() == 0)
				continue;

			int index = random.Integer(0, vector.Size()- 1);
			
			auto vectorStartTime = std::chrono::high_resolution_clock::now();
			vector.EraseAt(index);
			auto vectorEndTime = std::chrono::high_resolution_clock::now();
			auto vertexTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(vectorEndTime - vectorStartTime).count();
			vertexAverageTime += vertexTimeInterval;

			auto linkedListStartTime = std::chrono::high_resolution_clock::now();
			linkedList.EraseAt(index);
			auto linkedListEndTime = std::chrono::high_resolution_clock::now();
			auto linkedListTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(linkedListEndTime - linkedListStartTime).count();
			linkedListAverageTime += linkedListTimeInterval;
		}

		vertexAverageTime /= 100;
		linkedListAverageTime /= 100;

		// Write the average times to the file.
		dataFile << n << '\t' << vertexAverageTime << '\t' << linkedListAverageTime << '\n';
	}

	dataFile.close();

	return true;
}

// Generate the script file for the EraseAt() function.
bool GenerateScriptEraseAt(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileName)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return false;

	// Print out the parameters.
	scriptFile
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileName << "'" << std::endl
		<< std::endl
		<< "set title 'Average Completion Time of EraseAt() vs. Size of Data Set for Vector and LinkedList'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Vector' lw 1 with lines, \"" << dataFileName << "\" using 1:3 title 'Linked List' lw 1 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return true;
}

// Generate the data file for the Find() function.
bool GenerateDataFind(const std::string& dataFileName, const int& minN, const int& maxN, Random& random)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);

	if (!dataFile)
		return false;

	dataFile << "#n\tVector(ns)\tLinkedList(ns)" << std::endl;

	for (int n = minN; n <= maxN; n++)
	{
		// Generate a vector and a linked list of size n.
		Vector<int> vector;
		LinkedList<int> linkedList;
		GenerateVectorAndLinkedList(vector, linkedList, n, random);

		// Measure the average time of the same task in each data structure.
		long long vertexAverageTime = 0;
		long long linkedListAverageTime = 0;

		for (int i = 0; i < 100; i++)
		{
			int value = random.Integer(0, n - 1);

			auto vectorStartTime = std::chrono::high_resolution_clock::now();
			vector.Find(value);
			auto vectorEndTime = std::chrono::high_resolution_clock::now();
			auto vertexTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(vectorEndTime - vectorStartTime).count();
			vertexAverageTime += vertexTimeInterval;

			auto linkedListStartTime = std::chrono::high_resolution_clock::now();
			linkedList.Find(value);
			auto linkedListEndTime = std::chrono::high_resolution_clock::now();
			auto linkedListTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(linkedListEndTime - linkedListStartTime).count();
			linkedListAverageTime += linkedListTimeInterval;
		}

		vertexAverageTime /= 100;
		linkedListAverageTime /= 100;

		// Write the average times to the file.
		dataFile << n << '\t' << vertexAverageTime << '\t' << linkedListAverageTime << '\n';
	}

	dataFile.close();

	return true;
}

// Generate the script file for the Find() function.
bool GenerateScriptFind(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileName)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return false;

	// Print out the parameters.
	scriptFile
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileName << "'" << std::endl
		<< std::endl
		<< "set title 'Average Completion Time of Find() vs. Size of Data Set for Vector and LinkedList'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Vector' lw 1 with lines, \"" << dataFileName << "\" using 1:3 title 'Linked List' lw 1 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return true;
}

// Generate the data file for the Contains() function.
bool GenerateDataContains(const std::string& dataFileName, const int& minN, const int& maxN, Random& random)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);

	if (!dataFile)
		return false;

	dataFile << "#n\tVector(ns)\tLinkedList(ns)" << std::endl;

	for (int n = minN; n <= maxN; n++)
	{
		// Generate a vector and a linked list of size n.
		Vector<int> vector;
		LinkedList<int> linkedList;
		GenerateVectorAndLinkedList(vector, linkedList, n, random);

		// Measure the average time of the same task in each data structure.
		long long vertexAverageTime = 0;
		long long linkedListAverageTime = 0;

		for (int i = 0; i < 100; i++)
		{
			int value = random.Integer(0, n - 1);

			auto vectorStartTime = std::chrono::high_resolution_clock::now();
			vector.Contains(value);
			auto vectorEndTime = std::chrono::high_resolution_clock::now();
			auto vertexTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(vectorEndTime - vectorStartTime).count();
			vertexAverageTime += vertexTimeInterval;

			auto linkedListStartTime = std::chrono::high_resolution_clock::now();
			linkedList.Contains(value);
			auto linkedListEndTime = std::chrono::high_resolution_clock::now();
			auto linkedListTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(linkedListEndTime - linkedListStartTime).count();
			linkedListAverageTime += linkedListTimeInterval;
		}

		vertexAverageTime /= 100;
		linkedListAverageTime /= 100;

		// Write the average times to the file.
		dataFile << n << '\t' << vertexAverageTime << '\t' << linkedListAverageTime << '\n';
	}

	dataFile.close();

	return true;
}

// Generate the script file for the Contains() function.
bool GenerateScriptContains(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileName)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return false;

	// Print out the parameters.
	scriptFile
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileName << "'" << std::endl
		<< std::endl
		<< "set title 'Average Completion Time of Contains() vs. Size of Data Set for Vector and LinkedList'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Vector' lw 1 with lines, \"" << dataFileName << "\" using 1:3 title 'Linked List' lw 1 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return true;
}

// Generate the data file for the Insert() function.
bool GenerateDataInsert(const std::string& dataFileName, const int& minN, const int& maxN, Random& random)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);

	if (!dataFile)
		return false;

	dataFile << "#n\tVector(ns)\tLinkedList(ns)" << std::endl;

	for (int n = minN; n <= maxN; n++)
	{
		// Generate a vector and a linked list of size n.
		Vector<int> vector;
		LinkedList<int> linkedList;
		GenerateVectorAndLinkedList(vector, linkedList, n, random);

		// Measure the average time of the same task in each data structure.
		long long vertexAverageTime = 0;
		long long linkedListAverageTime = 0;

		for (int i = 0; i < 100; i++)
		{
			int value = random.Integer(0, n - 1);
			int index = random.Integer(0, n - 1);

			auto vectorStartTime = std::chrono::high_resolution_clock::now();
			vector.Insert(value, index);
			auto vectorEndTime = std::chrono::high_resolution_clock::now();
			auto vertexTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(vectorEndTime - vectorStartTime).count();
			vertexAverageTime += vertexTimeInterval;

			auto linkedListStartTime = std::chrono::high_resolution_clock::now();
			linkedList.Insert(value, index);
			auto linkedListEndTime = std::chrono::high_resolution_clock::now();
			auto linkedListTimeInterval = std::chrono::duration_cast<std::chrono::nanoseconds>(linkedListEndTime - linkedListStartTime).count();
			linkedListAverageTime += linkedListTimeInterval;
		}

		vertexAverageTime /= 100;
		linkedListAverageTime /= 100;

		// Write the average times to the file.
		dataFile << n << '\t' << vertexAverageTime << '\t' << linkedListAverageTime << '\n';
	}

	dataFile.close();

	return true;
}

// Generate the script file for the Insert() function.
bool GenerateScriptInsert(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileName)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return false;

	// Print out the parameters.
	scriptFile
		<< "set terminal png size 1920,1080" << std::endl
		<< "set output '" << outputFileName << "'" << std::endl
		<< std::endl
		<< "set title 'Average Completion Time of Insert() vs. Size of Data Set for Vector and LinkedList'" << std::endl
		<< "set xlabel 'Size (N)'" << std::endl
		<< "set ylabel 'Average time (ns)'" << std::endl
		<< "set xzeroaxis" << std::endl
		<< "set key inside top left" << std::endl
		<< std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Vector' lw 1 with lines, \"" << dataFileName << "\" using 1:3 title 'Linked List' lw 1 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return true;
}

int main()
{	
	Random random;

	GenerateDataAt("data_at.txt", 50, 1000, random);	
	GenerateScriptAt("script_at.txt", "data_at.txt", "image_at.png");
	system("gnuplot.exe script_at.txt");
	
	GenerateDataPushFront("data_push_front.txt", 50, 1000, random);
	GenerateScriptPushFront("script_push_front.txt", "data_push_front.txt", "image_push_front.png");
	system("gnuplot.exe script_push_front.txt");
		
	GenerateDataPushBack("data_push_back.txt", 50, 1000, random);
	GenerateScriptPushBack("script_push_back.txt", "data_push_back.txt", "image_push_back.png");
	system("gnuplot.exe script_push_back.txt");

	GenerateDataEraseAt("data_erase_at.txt", 50, 1000, random);
	GenerateScriptEraseAt("script_erase_at.txt", "data_erase_at.txt", "image_erase_at.png");
	system("gnuplot.exe script_erase_at.txt");
	
	GenerateDataFind("data_find.txt", 50, 1000, random);
	GenerateScriptFind("script_find.txt", "data_find.txt", "image_find.png");
	system("gnuplot.exe script_find.txt");

	GenerateDataContains("data_contains.txt", 50, 1000, random);
	GenerateScriptContains("script_contains.txt", "data_contains.txt", "image_contains.png");
	system("gnuplot.exe script_contains.txt");

	GenerateDataInsert("data_insert.txt", 50, 1000, random);
	GenerateScriptInsert("script_insert.txt", "data_insert.txt", "image_insert.png");
	system("gnuplot.exe script_insert.txt");
}