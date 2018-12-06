using BearBuildTool.Projects;
using System.IO;
using System;
public class bear_engine :Project
{
	public bear_engine(string ProjectPath)
	{
		PCHFile=Path.Combine(ProjectPath,"source","PCH.cpp");
		PCHIncludeFile = "BearEngine.hpp";
		AddSourceFiles(Path.Combine(ProjectPath,"source"));
        Include.Private.Add(Path.Combine(ProjectPath, "include"));
        Include.Public.Add(Path.Combine(ProjectPath,"include"));
		Projects.Public.Add("bear_core");
        Projects.Public.Add("bear_graphics");
        Projects.Public.Add("bear_sound");
        Projects.Public.Add("box2d");
        Projects.Private.Add("freetype");
        Defines.Public.Add("EDITOR");
		if(BearBuildTool.Config.Global.Platform == BearBuildTool.Config.Platform.Win64
		||BearBuildTool.Config.Global.Platform == BearBuildTool.Config.Platform.Win32)
		{
			LibrariesStatic.Private.Add("freetype26.lib");
		}
	}
} 