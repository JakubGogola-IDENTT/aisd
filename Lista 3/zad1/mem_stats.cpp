#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <sys/sysinfo.h>
#include <unistd.h>

unsigned long mem_stats (unsigned long *diff) {

	struct sysinfo *info = new struct sysinfo;
	sysinfo (info);

	/*system ("date");
	std::cout << "uptime: " << info->uptime << std::endl;
	std::cout << "loads (1 min): " << info->loads[0] << std::endl;
	std::cout << "loads (5 min): " << info->loads[1] << std::endl;
	std::cout << "loads (15 min): " << info->loads[2] << std::endl;
	std::cout << "totalram: " << info->totalram << std::endl;
	std::cout << "freeram: " << info->freeram << std::endl;
	std::cout << "sharedram: " << info->sharedram << std::endl;
	std::cout << "bufferram: " << info->bufferram << std::endl;
	std::cout << "totalswap: " << info->totalswap << std::endl;
	std::cout << "freeswap: " << info->freeswap << std::endl;*/

	*diff = info->totalram - info->freeram;
	delete info;
}

void statistics (int repeats) {
	std::ofstream fout;
	unsigned long diff;

	fout.open("mem_stats.csv");	
	fout << "n;Used_memory;\n";

	for (int i = 0; i < repeats; i++) {
		mem_stats(&diff);
		fout << i << ";" << diff << ";\n";
		system ("sleep 1");
	}
	fout.close();
}

int main (int argc, char** argv) {

	if (argc != 2) {
		std::cerr << "Invalid number of arguments!" << std::endl;
		return 0;
	}

	int repeats;
	std::istringstream ss ((std::string) argv[1]);

	ss >> repeats;

	statistics(repeats);

	return 0;
}