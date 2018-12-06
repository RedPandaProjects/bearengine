#ifndef REGISTER_NAME 
#define REGISTER_NAME(name,text) BEARENGINE_API extern  BearName N##name;
#endif
	REGISTER_NAME(None, TEXT(""));
	REGISTER_NAME(Null, TEXT("null"));
	REGISTER_NAME(Default, TEXT("default"));
	REGISTER_NAME(Alpha, TEXT("alpha"));
	REGISTER_NAME(Sprite, TEXT("sprite"));
	REGISTER_NAME(Font, TEXT("font"));
	REGISTER_NAME(Terrain, TEXT("terrain"));
	REGISTER_NAME(Bear, TEXT("bear"));
	REGISTER_NAME(Console, TEXT("console"));
#undef REGISTER_NAME