#include "../../Utility/SupportFunc.h"
#include "Day7.h"
#include <stack>

class Folder
{
	public:
	int size = 0;
	string name = "none";

	Folder* above;
	vector<Folder*> inside;

	int CalcSize()
	{
		int sum = 0;
		for (Folder *a : inside)
		{
			sum+=a->CalcSize();
		}
		return size + sum;
	}
};

void Day7()
{
	myFile in = myFile();
	in.Open("Days/Day7/in.txt");
	in.ReadFile();

	//topmost folder
	Folder* computer = new Folder();
	computer->name = "computer";

	//a list of all folders
	vector<Folder*> Folders; 
	//remembers folders which were above
	stack<Folder*> dependency;

	dependency.push(computer);

	for (int i = 0; i < in.nol; i++)
	{
		//if command
		if (in.inputWords[i][0] == "$")
		{
			if (in.inputWords[i][1] == "cd")
			{
				if (in.inputWords[i][2] == "..")
				{
					dependency.pop();
				}
				else
				{
					Folder* a = new Folder();
					a->name = in.inputWords[i][2];

					dependency.top()->inside.push_back(a);
					a->above = dependency.top();

					dependency.push(a);
					Folders.push_back(a);
				}
			}
			//if not cd just skip
		}
		//by default if not command then its list from $ ls
		else
		{
			//if listed file, not folder 
			if (in.inputWords[i][0] != "dir")
			{
				dependency.top()->size += stoi(in.inputWords[i][0]);
			}
		}
	}
	int sum = 0;
	int maxdelsize = computer->CalcSize(),
	    unusedSpace = 70000000 - computer->CalcSize(),
	    toFree = 30000000 - unusedSpace;

	Folder* ToDelete = computer;

	for (Folder* a : Folders)
	{
		int s = a->CalcSize();
		if (s < 100000)
		{
			sum += s;
		}
		if (s < maxdelsize && s > toFree)
		{
			maxdelsize = s;
			ToDelete = a;
		}
	}
	cout << sum << " " << ToDelete->name << " " << maxdelsize;
}
