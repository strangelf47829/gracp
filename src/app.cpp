#include "gracp.h"
#include <stdio.h>
#include <string>
#include <fstream>

int disp(bool isH)
{



	printf("gracp - wrap c++ classes in c-callable functions.\n\n\n");

	if(!isH)
	{
		printf("version %s. (%s)\n",_GRACP_VERS,_GRACP_COPY);
		printf("author: %s\n",_GRACP_AUTH);
		return 0;
	}

	printf("usage: gracp [-c | -r | -h | -v] input [output]\n\tInput file **must** end with .cpp\n\n\n");
	printf("Options:\n\t-c: copy over contents from input file to output file, then append C-functions.\n\t-r: replace input file with output file. input file is backed up as [input].old\n");
	printf("\t-h: print this page\n\t-v: print version info\n\n\toutput: the name of the output file. defaults to \"input_c.cpp\"\n");
	return 0;
}

//gracp test.cpp -> write to test_c.cpp, do not copy
//gracp -r test.cpp -> replace test.cpp, create test.cpp.old, copy
//gracp test.cpp new.cpp -> write to new.cpp, do not copy
//gracp -c test.cpp new.cpp -> write to new.cpp, copy

int main(int argc, const char **argv)
{
	std::string inp;
	std::string out;
	bool copy = false;

	if(argc == 1) // No argument
	{
		//printf("No Arguments specified... Printing Help page\n");
		return disp(true);
	}
	if(argc == 2)
	{
		std::string arg1(argv[1]);
		if(!arg1.compare("-h"))
			return disp(true);
		if(!arg1.compare("-v"))
			return disp(false);
		inp = arg1;
		out = inp.substr(0,inp.find(".cpp")).append("_c.cpp");
	}
	else if(argc == 3)
	{
		std::string first(argv[1]);
		std::string secon(argv[2]);
		if(!first.compare("-c"))
		{
			copy = true;
			inp = secon;
			out = inp.substr(0,inp.find(".cpp")).append("_c.cpp");
		} else if(!first.compare("-r"))
		{
			//printf("not implemented yet.. Sorry!\n");
			return -2;
		}
		else
		{
		inp = first;
		out = secon;
		}
	}
	else if(argc == 4)
	{
		std::string f(argv[1]);
		std::string s(argv[2]);
		std::string t(argv[3]);
		if(f.compare("-c"))
			return -3;
		inp = s;
		out = t;
		copy = true;
	}
	else
	{
		printf("Too many arguments!\n");
		return disp(true) - 1;
	}

	//printf("starting gracp...\n\tInput: %s\n\tOutput: %s\n\tCopy? %s\n\t",inp.data(),out.data(),copy?"yes":"no"); 
	gracp *g = new gracp(inp,out);
	delete(g);
	if(copy)
	{
		std::ofstream tmp;
		std::ifstream swp;
		tmp.open(out.append(".tmp").data());
		swp.open(inp.data());
		////printf("%s -> %s\n",inp.data(),out.data());
		char buf[1024];
		do //Copy over original file
		{
			swp.read(buf,1024);
			tmp.write(buf, swp.gcount());
		} while (swp.gcount() > 0);
		swp.close();
		out = out.substr(0,out.find(".tmp"));
		out = out.substr(0,out.find(".tmp"));
		swp.open(out.substr(0,out.find(".tmp")).data());
		////printf("\t%s -> %s\n",out.data(),out.append(".tmp").data());
		do //Copy over emitted file
		{
			swp.read(buf,1024);
			tmp.write(buf, swp.gcount());
		} while(swp.gcount() > 0);
		tmp.close();
		swp.close();
		std::string cl_tgt(out.data());
		std::string cl_tmp(out.append(".tmp").data());
		//printf("\nCleaning up...\n restoring %s as %s\n",cl_tmp.data(),cl_tgt.data());
		int _cp = system(std::string("cp ").append(cl_tmp).append(" ").append(cl_tgt).data());
		if(_cp)
			printf("ERR: gracp does not support your shell. \"cp\" exited with code %d\n",_cp);
		int _rm = system(std::string("rm ").append(cl_tmp).data());
		if(_rm)
			printf("ERR: gracp does not support your shell. \"rm\" exited with code %d\n",_rm);
		return _cp + _rm;
	}


}




