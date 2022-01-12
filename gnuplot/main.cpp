#include <iostream>
#include <cmath>
#include <fstream>

int main()
{
	std::fstream dataFile;

	dataFile.open("data.txt", std::ios::out | std::ios::trunc);

	if (dataFile)
	{
		// Print out the parameters.
		dataFile << "#x\tsin(x)\tcos(x)" << std::endl;

		// Print out the data.
		for (float t = 0; t <= 6.2f; t += 0.1f)
		{
			dataFile << t << '\t' << sin(t) << '\t' << cos(t) << std::endl;
		}

		// Close the data file.
		dataFile.close();

		// Run gnuplot.
		system("gnuplot.exe sample_plot.txt");
	}
	else
	{
		std::cout << "Cannot open data.txt" << std::endl;
	}
}