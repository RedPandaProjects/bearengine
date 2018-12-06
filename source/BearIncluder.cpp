#include "BearEngine.hpp"
BEARENGINE_API BearEngine::BearIncluder BearEngine::GIncluder;
BearEngine::BearIncluder::BearIncluder()
{
}

BearCore::BearStreamRef< BearCore::BearInputStream> BearEngine::BearIncluder::OpenAsStream(const bchar * name)
{
	return BearCore::FS->Read(TEXT("%config%"), name);
}

BearCore::BearStreamRef< BearCore::BearBufferedReader> BearEngine::BearIncluder::OpenAsBuffer(const bchar * name)
{
	return BearCore::BearStreamRef<BearCore::BearBufferedReader>(BearCore::bear_new<BearCore::BearMemoryStream>(**BearCore::FS->Read(TEXT("%config%"), name)));
}

BearEngine::BearIncluder::~BearIncluder()
{
}
