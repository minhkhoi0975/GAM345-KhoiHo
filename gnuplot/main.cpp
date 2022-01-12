#include <iostream>
#include <cmath>
#include <fstream>

// Generate a data file. Return true if the file is successfully generated.
bool GenerateDataFile(const std::string& dataFileName);

// Generate a script file. Return true if the file is successfully generated.
bool GenerateScriptFile(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileName);

int main()
{
	// Ask the user to enter the file names.
	std::cout << "Enter the data file name: ";
	std::string dataFileName;
	std::cin >> dataFileName;

	std::cout << "Enter the script file name: ";
	std::string scriptFileName;
	std::cin >> scriptFileName;

	std::cout << "Enter the output file name: ";
	std::string outputFileName;
	std::cin >> outputFileName;

	// Generate the data file.
	if (!GenerateDataFile(dataFileName))
	{
		std::cout << "Cannot generate the data file " << dataFileName << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Generate the script file.
	if (!GenerateScriptFile(scriptFileName, dataFileName, outputFileName))
	{
		std::cout << "Cannot generate the script file " << scriptFileName << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Run gnuplot.
	std::string command("gnuplot.exe ");
	command.append(scriptFileName);
	system(command.c_str());
}

bool GenerateDataFile(const std::string& dataFileName)
{
	std::fstream dataFile(dataFileName, std::ios::out | std::ios::trunc);
	
	if (!dataFile)
		return false;

	// Print out the parameters.
	dataFile << "#t\tsin(t)\tcos(t)" << std::endl;

	// Print out the data.
	for (float t = 0; t <= 6.2f; t += 0.1f)
	{
		dataFile << t << '\t' << sin(t) << '\t' << cos(t) << std::endl;
	}

	// Close the file.
	dataFile.close();

	return true;
}

bool GenerateScriptFile(const std::string& scriptFileName, const std::string& dataFileName, const std::string& outputFileName)
{
	std::fstream scriptFile(scriptFileName, std::ios::out | std::ios::trunc);

	if (!scriptFile)
		return false;

	// Print out the parameters.
	scriptFile
		<< "set terminal png size 1000,800"				<< std::endl
		<< "set output '" << outputFileName << "'"		<< std::endl
														<< std::endl
		<< "set title 'Sine and Cosine'"				<< std::endl
		<< "set xlabel 't'"								<< std::endl
		<< "set ylabel 'f(t)'"							<< std::endl
		<< "set xzeroaxis"								<< std::endl
		<< "set key inside bottom left"					<< std::endl
														<< std::endl
		<< "plot \"" << dataFileName << "\" using 1:2 title 'Sine' lw 5 with lines, \"" << dataFileName << "\" using 1:3 title 'Cosine' lw 5 with lines" << std::endl;

	// Close the file.
	scriptFile.close();

	return true;
}