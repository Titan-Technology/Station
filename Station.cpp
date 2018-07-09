#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	string fil;
	int pos = 0;
	string options[];
	string opt;
	bool CFLAGS = false;
	if(string(argv[1]) == "clean")
		{
			system("rm -r build/");
			return 0;
		}
	else
	{
		ifstream in("FallPath");
		if(!in)
			{
			  cout << "Cannot Calculate FallPath(No Fallpath file found).\n";
			  return 0;
			}
		string str;
		while (getline(in, str))
			{
				if(string(argv[1]) == "build")
				{
					string infile = str;
					int TempNumOne = infile.size();
					char Filename[1000];
					for (int a = 0;a<=TempNumOne;a++)
						{
							Filename[a] = infile[a];
							cout << infile[a] << endl;
							fil += Filename[a];
							if(fil == "CFLAGS=\"")
								{
									fil = " ";
									CFLAGS = true; 
								}
							if(CFLAGS == true && Filename[a] != "\"")
								{
									opt += fil;
								}
							if(Filename[a] == "\"" && CFLAGS == true)
								{
									CFLAGS = false;
								}
						  }
				}
			}
	}
}