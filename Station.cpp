#include<iostream>
#include<fstream>
#include<string>
#include<bits/stdc++.h>
#include<algorithm>
#include<array>
#include<unistd.h>
#include<stdio.h>

using namespace std;

void searchFile(); 
void build_func();
void get_info();
void gen();


string GetStdoutFromCommand(string cmd)
{
	string data;
	FILE * stream;
	const int max_buffer = 256;
	char buffer[max_buffer];
	cmd.append(" 2>&1");
	stream = popen(cmd.c_str(), "r");
	if(stream)
		{
			while (!feof(stream))
				if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
					pclose(stream);
		}
	return data;
}
int pos3=0;
int pos4d = 0;
int pos5 = 0;
int pos2 = 0;
int pos6 = 0;
int pos7 =0;
int pos8 = 0;
int pos;
string bopt[] = {"BOUTPUTNAME=\"","BINPUTS=\""};
string flags[] = {"CPPFLAGS=\"","CFLAGS=\"","CCOM=\"","CPPCOM=\"","INSTALLPREFIX=\"","LINKING=\"","INCLUDES=\"","LIBDIR=\""};
string options[9000];
string includes[9000];
string libs[9000];
string inputs[100];
string output;
string paper[] = {"NAME=\"","FLAGS=\"","LDIR=\"","IDIR=\"","INPUTS=\"","MANFILE=\"","PREFIX=\"","LIBS=\""};
string gen_var[9000];

bool gcc = false;
bool clang = false;

int main(int argc, char* argv[])
{
	if(argv[1] == '\0')
		{
			cout << "wrong" << endl;
			return 0;
		}
	if(string(argv[1]) == "k")
		{
			string compp1 = GetStdoutFromCommand("g++ -c cmake.cpp -o testh.o -fpermissive");
			string compp8 = GetStdoutFromCommand("g++ -c test.c -o test.o -Wfatal-errors");
			ifstream i1("testh.o");
			ifstream i2("testh.o");
			if(!i1.is_open())
				{
					cout << compp1 << endl;
				}
			if(!i2.is_open())
				{
					cout << compp8 << endl;
				}
			}	
	if(string(argv[1]) == "build")
		{
			cout << "Researching" << endl;
			searchFile();
			cout << "Calculating Fall Path" << endl;
			build_func();
		}
	if(string(argv[1]) == "generate")
		{
			gen();
		}
	if(string(argv[1]) == "install")
		{
			searchFile();
			system("cd dist/");
			#ifdef WIN32
				system(("xcopy /s dist " + options[4]).c_str());
			#else
				system(("cp -v dist/ " + options[4]).c_str());
			#endif
		}
	if(string(argv[1]) == "clean")
		{
			#ifdef WIN32
				system("del /Q build");
			#else
				system("rm build/*");
			#endif
			rmdir("./build");
		}
	return 0;
}

void get_info()
{
	ifstream dataIn;
	dataIn.open("FallPath");
	string temp;
	string line;
	string word;
	if(pos4d == sizeof(bopt)/sizeof(bopt[0]))
		{
			return;
		}
	word = bopt[pos4d];
	if (dataIn.is_open())
		{
			while (getline(dataIn, temp))
				{
					line.append(temp);
					if (line.find(word) != string::npos)
						{
							if(word == "BOUTPUTNAME=\"")
								{
									temp.erase(0,14);
								}
							else if(word == "BINPUTS=\"")
								{
									temp.erase(0,10);
								}
							reverse(temp.begin(),temp.end());
							temp.erase (0,1);
							reverse(temp.begin(),temp.end());
							pos4d++;
							break;
						}		
				}
			dataIn.close();
		}
	if(word == "BOUTPUTNAME=\"")
		{
			output = temp;
		}
	else
		{
			string fil;
			string infile = temp;
			int TempNumOne = infile.size();
			char Filename[1000];
			for (int a = 0;a<=TempNumOne;a++)
				{
					Filename[a] = infile[a];
					fil += Filename[a];
					if(Filename[a] == ' ')
						{
                              fil = "";
                        }
					if(Filename[a] == ';')
                        {
							reverse(fil.begin(),fil.end());
							fil.erase (0,1);
							reverse(fil.begin(),fil.end());
							inputs[pos5] = fil;
							pos5++;
                            fil = "";
                        }
				}
		}
	get_info();
}

void build_func()
{
	system("mkdir build");
	system("mkdir \"build/dist\"");
	//Getting info
	get_info();
	cout << sizeof(inputs)/sizeof(inputs[0]) << endl;
	//Compileing
	while(pos2 < (sizeof(inputs)/sizeof(inputs[0])))
		{
			system((options[4] + " " + options[1] + " -I" + options[7] + " " + "-c " + inputs[pos2] + " -o " + "build/" + inputs[pos2] + ".o").c_str());
			pos2++;
		}
	system((options[4] + " " + " -L" + options[7] + " -o " + "build/dist/" + output + " build/*.cpp.o" + " " + options[6]).c_str());
	ifstream fin("build/dist/" + output);
	if(!fin)
		{
			cerr << "Path is Blocked" << endl;
		}
	else
		{
			cout << "Fall Complete!" << endl;
		}
}

void gen()
{
	cout << "Preparing" << endl;
	ifstream dataIn;
	dataIn.open("ResearchPaper.txt");
	string dd;
	string f;
	string g;
	if(pos == sizeof(flags)/sizeof(flags[0]))
		{
			return;
		}
	g = paper[pos3];
	if (dataIn.is_open())
		{
			while (getline(dataIn, dd))
				{
					f.append(dd);
					if (f.find(g) != string::npos)
						{
							if(g == "NAME=\"")
								{
									dd.erase(0,10);
								}
							else if(g == "FLAGS=\"")
								{
									dd.erase(0,8);
								}
							else if(g == "LDIR=\"")
								{
									dd.erase(0,6);
								}
							else if(g == "IDIR=\"")
								{
									dd.erase(0,8);
								}
							else if(g == "INPUTS=\"")
								{
									dd.erase(0,15);
								}
							else if(g == "PREFIX=\"")
								{
									dd.erase(0,10);
								}
							else if(g == "LIBS=\"")
								{
									dd.erase(0,8);
								}
							reverse(dd.begin(),dd.end());
							dd.erase (0,1);
							reverse(dd.begin(),dd.end());
							pos3++;
							break;
						}		
				}
			dataIn.close();
		}	
			/*if(g == "INPUTS=\"")
			{
				string fil;
				string infile = dd;
				int TempNumOne = infile.size();
				char Filename[1000];
				for (int a = 0;a<=TempNumOne;a++)
					{
						Filename[a] = infile[a];
						fil += Filename[a];
						if(Filename[a] == ' ')
							{
				                  fil = "";
				            }
						if(Filename[a] == ';')
				            {
								reverse(fil.begin(),fil.end());
								fil.erase (0,1);
								reverse(fil.begin(),fil.end());
								inputs[pos5] = fil;
								pos8++;
				                fil = "";
				            }
					}
			}
			else if(g == "LDIR=\"")
				{
					string fil;
					string infile = dd;
					int TempNumOne = infile.size();
					char Filename[1000];
					for (int a = 0;a<=TempNumOne;a++)
						{
							Filename[a] = infile[a];
							fil += Filename[a];
							if(Filename[a] == ' ')
								{
					                  fil = "";
					            }
							if(Filename[a] == ';')
					            {
									reverse(fil.begin(),fil.end());
									fil.erase (0,1);
									reverse(fil.begin(),fil.end());
									inputs[pos5] = fil;
									pos7++;
					                fil = "";
					            }
						}
				}
			else if(g == "IDIR=\"")
				{
					string fil;
					string infile = dd;
					int TempNumOne = infile.size();
					char Filename[1000];
					for (int a = 0;a<=TempNumOne;a++)
						{
							Filename[a] = infile[a];
							fil += Filename[a];
							if(Filename[a] == ' ')
								{
					                  fil = "";
					            }
							if(Filename[a] == ';')
					            {
									reverse(fil.begin(),fil.end());
									fil.erase (0,1);
									reverse(fil.begin(),fil.end());
									includes[pos6] = fil;
									pos6++;
					                fil = "";
					            }
						}
				}*/
			gen_var[pos3] = dd;
			cout << "===============================================" << endl;
			cout << gen_var[pos3] << endl;
			cout << "===============================================" << endl;
			cout << endl;
			#ifdef WIN32
				system("echo #include^<stdio.h^> >> test.c");
				system("echo int main(int argc, char **argv) { printf(\"hello world\"); } >> test.c");
			#else
				system("echo -e \"#include<stdio.h>\nint main(int argc, char **argv) { printf(\"hello world\"); }\" >> test.c");
			#endif
			string compp1 = GetStdoutFromCommand("g++ -o test test.c");
			#ifdef WIN32
				string compp2 = GetStdoutFromCommand("clang++ -o test.exe test.c");
			#else
				string compp2 = GetStdoutFromCommand("clang++ -o test test.c");
			#endif
			if(compp1 == "\0")
				{
					gcc = true;
				}
			if(compp2 == "\0")
				{
					clang = true;
				}
			if(clang == true && gcc == true)
				{
					string compilercon;
					cout << "I Have found two Compilers on your system,Which one shall I us:" << endl;
					cout << "1)GCC" << endl;
					cout << "2)Clang" << endl;
					cout << "Please Enter only the number" << endl;
					getline(cin,compilercon);
					if(compilercon == "1")
						{
							gen_var[pos3] = "gcc";
							pos3++;
							gen_var[pos3] = "g++";
						}
					if(compilercon == "2")
						{
							gen_var[pos3] = "clang";
							pos3++;
							gen_var[pos3] = "clang++";
						}
				}	
			cout << "Research Paper Read(FallPath Generated)" << endl;
			cout << "To Fall type:" << endl;
			cout << "station build" << endl;
}

void searchFile()
{
	ifstream dataIn;
	dataIn.open("FallPath");
	string temp;
	string line;
	string word;
	if(pos == sizeof(flags)/sizeof(flags[0]))
		{
			return 0;
		}
	word = flags[pos];
	if (dataIn.is_open())
		{
			while (getline(dataIn, temp))
				{
					line.append(temp);
					if (line.find(word) != string::npos)
						{
							if(word == "CPPFLAGS=\"")
								{
									temp.erase(0,10);
								}
							else if(word == "CFLAGS=\"")
								{
									temp.erase(0,8);
								}
							else if(word == "CCOM=\"")
								{
									temp.erase(0,6);
								}
							else if(word == "CPPCOM=\"")
								{
									temp.erase(0,8);
								}
							else if(word == "INSTALLPREFIX=\"")
								{
									temp.erase(0,15);
								}
							else if(word == "LINKING=\"")
								{
									temp.erase(0,9);
								}
							else if(word == "INCLUDES=\"")
								{
									temp.erase(0,10);
								}
							else if(word == "LIBDIR=\"")
								{
									temp.erase(0,8);
								}
							reverse(temp.begin(),temp.end());
							temp.erase (0,1);
							reverse(temp.begin(),temp.end());
							pos++;
							break;
						}		
				}
			dataIn.close();
		}
	options[pos] = temp;
	searchFile();
}
