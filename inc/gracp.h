#include <fstream>
#include <string>

#ifndef _GRACP_H
#define _GRACP_H

#define _GRACP_AUTH "Rafael de Bie"
#define _GRACP_COPY "(c) Rafael de Bie 2023"
#define _GRACP_VERS "0.2"
#define _GRACP_BUFFSIZE(_c) "16"


class gracp
{
	public:
		std::ifstream input;
		std::ofstream output;
		std::ofstream head;

		gracp(std::string, std::string);
		~gracp();
	private:
		void setInput(std::string);
		void setOutput(std::string);

		void readFile();

		void registerClass(const char *_class);
		void emitFunction(const char *_ret, const char *_class, const char *_name, bool);
		void emitFunction(const char *_ret, const char *_class, const char *_name, const char *_args, bool);

		std::string pp[256];
		int ppc;
};




#endif
