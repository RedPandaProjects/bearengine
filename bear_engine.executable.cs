using BearBuildTool.Projects;
using System.IO;
using System;
public class bear_engine :Executable
{
	public bear_engine(string ProjectPath)
	{
		PCHFile=Path.Combine(ProjectPath,"source","BearEngine.cpp");
		PCHIncludeFile = "BearEngine.hpp";
        Console = true;
		AddSourceFiles(Path.Combine(ProjectPath,"source"));
        Include.Private.Add(Path.Combine(ProjectPath, "include"));
        Include.Public.Add(Path.Combine(ProjectPath,"include"));
		Projects.Public.Add("bear_core");
        Projects.Private.Add("bear_graphics");
		Projects.Private.Add("box2d");
		IncludeAutonomousProjects.Add("bear_game");
	}
} 