#include "BearEngine.hpp"
BearCore::BearMap <BearCore::BearStringAnsiConteniar, BearCore::BearString> *MapType = 0;
const BearCore::BearString & BearEngine::BearObject::GetType(const char * name)
{
	auto item=MapType->find(BearCore::BearStringAnsiConteniar(name, false));
	if (item == MapType->end())
	{
#ifdef UNICODE
		MapType->insert(name, *BearCore::BearEncoding::ToUTF16(name));
#else
		MapType->insert(name, name);
#endif
		item = MapType->find(BearCore::BearStringAnsiConteniar(name, false));
		item->second.to_char(TEXT(' '));
		item->second++;
	}
	return item->second;
}
void BearEngine::BearObject::Save(BearCore::BearOutputStream * stream)
{
	
}

void BearEngine::BearObject::Load(const BearCore::BearInputStream * stream)
{
}

void BearEngine::BearObject::value( const bchar * key, float & data)
{
	auto section = *m_type.to_string();
	if (m_flags.test(BO_ForGame))
	{
		GGameConfig->Key(section, key)[0].scanf(TEXT("%f"), &data);
	}
	else
	{
		if (GGameConfig->Exist(section, key))
			GGameConfig->Key(section, key)[0].scanf(TEXT("%f"), &data);
		else	if (GPlatformConfig->Exist(section, key))
			GPlatformConfig->Key(section, key)[0].scanf(TEXT("%f"), &data);
		else
			GSystemConfig->Key(section, key)[0].scanf(TEXT("%f"), &data);
	}
}

void BearEngine::BearObject::value(const bchar * key, uint8 & data)
{
	auto section = *m_type.to_string();
	if (m_flags.test(BO_ForGame))
	{
		GGameConfig->Key(section, key)[0].scanf(TEXT("%hhu"), &data);
	}
	else
	{
		if (GGameConfig->Exist(section, key))
			GGameConfig->Key(section, key)[0].scanf(TEXT("%hhu"), &data);
		else	if (GPlatformConfig->Exist(section, key))
			GPlatformConfig->Key(section, key)[0].scanf(TEXT("%hhu"), &data);
		else
			GSystemConfig->Key(section, key)[0].scanf(TEXT("%hhu"), &data);
	}
}

void BearEngine::BearObject::value(const bchar * key, uint16 & data)
{
	auto section = *m_type.to_string();
	if (m_flags.test(BO_ForGame))
	{

		GGameConfig->Key(section, key)[0].scanf(TEXT("%hu"), &data);
	}
	else
	{
		if (GGameConfig->Exist(section, key))
			GGameConfig->Key(section, key)[0].scanf(TEXT("%hu"), &data);
		else if (GPlatformConfig->Exist(section, key))
			GPlatformConfig->Key(section, key)[0].scanf(TEXT("%hu"), &data);
		else
			GSystemConfig->Key(section, key)[0].scanf(TEXT("%hu"), &data);
	}
}

void BearEngine::BearObject::value(const bchar * key, uint32 & data)
{
	auto section = *m_type.to_string();
	if (m_flags.test(BO_ForGame))
	{

		GGameConfig->Key(section, key)[0].scanf(TEXT("%u"), &data);
	}
	else
	{
		if (GGameConfig->Exist(section, key))
			GGameConfig->Key(section, key)[0].scanf(TEXT("%u"), &data);
		else if (GPlatformConfig->Exist(section, key))
			GPlatformConfig->Key(section, key)[0].scanf(TEXT("%u"), &data);
		else
			GSystemConfig->Key(section, key)[0].scanf(TEXT("%u"), &data);
	}
}

void BearEngine::BearObject::value(const bchar * key, uint64 & data)
{
	auto section = *m_type.to_string();
	if (m_flags.test(BO_ForGame))
	{

		GGameConfig->Key(section, key)[0].scanf(TEXT("%llu"), &data);
	}
	else
	{
		if (GGameConfig->Exist(section, key))
			GGameConfig->Key(section, key)[0].scanf(TEXT("%llu"), &data);
		else if (GPlatformConfig->Exist(section, key))
			GPlatformConfig->Key(section, key)[0].scanf(TEXT("%llu"), &data);
		else
			GSystemConfig->Key(section, key)[0].scanf(TEXT("%llu"), &data);
	}
}

void BearEngine::BearObject::value(const bchar * key, int8 & data)
{
	auto section = *m_type.to_string();
	if (m_flags.test(BO_ForGame))
	{

		GGameConfig->Key(section, key)[0].scanf(TEXT("%hhd"), &data);
	}
	else
	{
		if (GGameConfig->Exist(section, key))
			GGameConfig->Key(section, key)[0].scanf(TEXT("%hhd"), &data);
		else if (GPlatformConfig->Exist(section, key))
			GPlatformConfig->Key(section, key)[0].scanf(TEXT("%hhd"), &data);
		else
			GSystemConfig->Key(section, key)[0].scanf(TEXT("%hhd"), &data);
	}
}

void BearEngine::BearObject::value(const bchar * key, int16 & data)
{
	auto section = *m_type.to_string();
	if (m_flags.test(BO_ForGame))
	{

		GGameConfig->Key(section, key)[0].scanf(TEXT("%hd"), &data);
	}
	else
	{
		if (GGameConfig->Exist(section, key))
			GGameConfig->Key(section, key)[0].scanf(TEXT("%hd"), &data);
		else	if (GPlatformConfig->Exist(section, key))
			GPlatformConfig->Key(section, key)[0].scanf(TEXT("%hd"), &data);
		else
			GSystemConfig->Key(section, key)[0].scanf(TEXT("%hd"), &data);
	}
}

void BearEngine::BearObject::value(const bchar * key, int32 & data)
{
	auto section = *m_type.to_string();
	if (m_flags.test(BO_ForGame))
	{

		GGameConfig->Key(section, key)[0].scanf(TEXT("%d"), &data);
	}
	else
	{
		if (GGameConfig->Exist(section, key))
			GGameConfig->Key(section, key)[0].scanf(TEXT("%d"), &data);
		else if (GPlatformConfig->Exist(section, key))
			GPlatformConfig->Key(section, key)[0].scanf(TEXT("%d"), &data);
		else
			GSystemConfig->Key(section, key)[0].scanf(TEXT("%d"), &data);
	}
}

void BearEngine::BearObject::value(const bchar * key, int64 & data)
{
	auto section = *m_type.to_string();
	if (m_flags.test(BO_ForGame))
	{

		GGameConfig->Key(section, key)[0].scanf(TEXT("%lld"), &data);
	}
	else
	{
		if (GGameConfig->Exist(section, key))
			GGameConfig->Key(section, key)[0].scanf(TEXT("%lld"), &data);
		else if (GPlatformConfig->Exist(section, key))
			GPlatformConfig->Key(section, key)[0].scanf(TEXT("%lld"), &data);
		else
			GSystemConfig->Key(section, key)[0].scanf(TEXT("%lld"), &data);
	}
}

void BearEngine::BearObject::value(const bchar * key, bool & data)
{
	auto section = *m_type.to_string();
	BearCore::BearString*str = 0;
	if (m_flags.test(BO_ForGame))
	{
		str = &GGameConfig->Key(section, key)[0];
	}
	else
	{
		if (GGameConfig->Exist(section, key))
			str = &GGameConfig->Key(section, key)[0];
		else	if (GPlatformConfig->Exist(section, key))
			str = &GPlatformConfig->Key(section, key)[0];
		else
			str = &GSystemConfig->Key(section, key)[0];
	}
	if (*str == TEXT("true"))
	{
		data = true;
	}
	else if (*str == TEXT("false"))
	{
		data = false;
	}
	else
	{
		int64 number;
		str->scanf(TEXT("%lld"), &number);
		if (number)
			data = true;
		else
			data = false;
	}
}

void BearEngine::BearObject::value(const bchar * key, BearCore::BearString & data)
{
	auto section = *m_type.to_string();
	if (m_flags.test(BO_ForGame))
	{
		data=GGameConfig->Key(section, key)[0];
	}
	else
	{
		if (GGameConfig->Exist(section, key))
			data = GGameConfig->Key(section, key)[0];
		else if (GPlatformConfig->Exist(section, key))
			data = GPlatformConfig->Key(section, key)[0];
		else
			data = GSystemConfig->Key(section, key)[0];
	}
}

void BearEngine::BearObject::value(const bchar * key, BearCore::BearVector<BearCore::BearString>& data)
{
	auto section = *m_type.to_string();
	if (m_flags.test(BO_ForGame))
	{
		data = GGameConfig->Key(section, key);
	}
	else
	{
		if (GPlatformConfig->Exist(section, key))
			data = GPlatformConfig->Key(section, key);
		else
			data = GSystemConfig->Key(section, key);
	}
}

BearEngine::BearObject * BearEngine::BearObject::getValueClass( const bchar * key)
{
	auto section = *m_type.to_string();
	BearCore::BearString*str = 0;
	if (m_flags.test(BO_ForGame))
	{

		str = &GGameConfig->Key(section, key)[0];
	}
	else
	{
		if (GGameConfig->Exist(section, key))
			str = &GGameConfig->Key(section, key)[0];
		else if (GPlatformConfig->Exist(section, key))
			str = &GPlatformConfig->Key(section, key)[0];
		else
			str = &GSystemConfig->Key(section, key)[0];
	}
	return GObjectManager->Create< BearObject>(BearName(**str));
}



void BearEngine::BearObject::valueFromUser(const bchar * key, uint8 & data)
{
	auto section = *m_type.to_string();
	if (GUser->Exist(section, key))
		GUser->Key(section, key)[0].scanf(TEXT("%hhu"), &data);
	else
		value(key, data);
}

void BearEngine::BearObject::valueFromUser(const bchar * key, uint16 & data)
{
	auto section = *m_type.to_string();
	if (GUser->Exist(section, key))
		GUser->Key(section, key)[0].scanf(TEXT("%hu"), &data);
	else
		value(key, data);
}

void BearEngine::BearObject::valueFromUser(const bchar * key, uint32 & data)
{
	auto section = *m_type.to_string();
	if (GUser->Exist(section, key))
		GUser->Key(section, key)[0].scanf(TEXT("%u"), &data);
	else
		value(key, data);
}

void BearEngine::BearObject::valueFromUser(const bchar * key, uint64 & data)
{
	auto section = *m_type.to_string();
	if (GUser->Exist(section, key))
		GUser->Key(section, key)[0].scanf(TEXT("%llu"), &data);
	else
		value(key, data);
}

void BearEngine::BearObject::valueFromUser(const bchar * key, int8 & data)
{
	auto section = *m_type.to_string();
	if (GUser->Exist(section, key))
		GUser->Key(section, key)[0].scanf(TEXT("%hhd"), &data);
	else
		value(key, data);
}

void BearEngine::BearObject::valueFromUser(const bchar * key, int16 & data)
{
	auto section = *m_type.to_string();
	if (GUser->Exist(section, key))
		GUser->Key(section, key)[0].scanf(TEXT("%hd"), &data);
	else
		value(key, data);
}

void BearEngine::BearObject::valueFromUser(const bchar * key, int32 & data)
{
	auto section = *m_type.to_string();
	if (GUser->Exist(section, key))
		GUser->Key(section, key)[0].scanf(TEXT("%d"), &data);
	else
		value(key, data);
}

void BearEngine::BearObject::valueFromUser(const bchar * key, int64 & data)
{
	auto section = *m_type.to_string();
	if (GUser->Exist(section, key))
		GUser->Key(section, key)[0].scanf(TEXT("%lld"), &data);
	else
		value(key, data);
}

void BearEngine::BearObject::valueFromUser(const bchar * key, bool & data)
{
	auto section = *m_type.to_string();
	if (GUser->Exist(section, key))
	{
		BearCore::BearString*str = 0;
		str=&GUser->Key(section, key)[0];
		if (*str == TEXT("true"))
		{
			data = true;
		}
		else if (*str == TEXT("false"))
		{
			data = false;
		}
		else
		{
			int64 number;
			str->scanf(TEXT("%lld"), &number);
			if (number)
				data = true;
			else
				data = false;
		}
	}
	else
	{
		value(key, data);
	}
}

void BearEngine::BearObject::valueFromUser(const bchar * key, BearCore::BearString & data)
{
	auto section = *m_type.to_string();
	if (GUser->Exist(section, key))
		data=	GUser->Key(section, key)[0];
	else
		value(key, data);
}

void BearEngine::BearObject::valueFromUser(const bchar * key, BearCore::BearVector<BearCore::BearString>& data)
{
	auto section = *m_type.to_string();
	if (GUser->Exist(section, key))
		data = GUser->Key(section, key);
	else
		value(key, data);
}

void BearEngine::BearObject::valueToUser(const bchar * key, uint8 data)
{
	auto section = *m_type.to_string();
	GUser->Key(section, key, BearCore::BearString())[0].assign_printf(TEXT("%hhu"), data);
}

void BearEngine::BearObject::valueToUser(const bchar * key, uint16 data)
{
	auto section = *m_type.to_string();
	GUser->Key(section, key, BearCore::BearString())[0].assign_printf(TEXT("%hu"), data);
}

void BearEngine::BearObject::valueToUser(const bchar * key, uint32 data)
{
	auto section = *m_type.to_string();
	GUser->Key(section, key, BearCore::BearString())[0].assign_printf(TEXT("%u"), data);
}

void BearEngine::BearObject::valueToUser(const bchar * key, uint64 data)
{
	auto section = *m_type.to_string();
	GUser->Key(section, key, BearCore::BearString())[0].assign_printf(TEXT("%llu"), data);
}

void BearEngine::BearObject::valueToUser(const bchar * key, int8 data)
{
	auto section = *m_type.to_string();
	GUser->Key(section, key, BearCore::BearString())[0].assign_printf(TEXT("%hhd"), data);
}

void BearEngine::BearObject::valueToUser(const bchar * key, int16 data)
{
	auto section = *m_type.to_string();
	GUser->Key(section, key, BearCore::BearString())[0].assign_printf(TEXT("%hd"), data);
}

void BearEngine::BearObject::valueToUser(const bchar * key, int32 data)
{
	auto section = *m_type.to_string();
	GUser->Key(section, key, BearCore::BearString())[0].assign_printf(TEXT("%d"), data);
}

void BearEngine::BearObject::valueToUser(const bchar * key, int64 data)
{
	auto section = *m_type.to_string();
	GUser->Key(section, key, BearCore::BearString())[0].assign_printf(TEXT("%lld"), data);
}

void BearEngine::BearObject::valueToUser(const bchar * key, bool data)
{
	auto section = *m_type.to_string();
	if(data)
		GUser->Key(section, key, BearCore::BearString())[0]=TEXT("true");
	else
		GUser->Key(section, key, BearCore::BearString())[0] = TEXT("false");
}

void BearEngine::BearObject::valueToUser(const bchar * key, const BearCore::BearString & data)
{
	auto section = *m_type.to_string();
	GUser->Key(section, key, BearCore::BearString())[0] = data;
}

void BearEngine::BearObject::valueToUser(const bchar * key, const BearCore::BearVector<BearCore::BearString>& data)
{
	auto section = *m_type.to_string();
	GUser->Key(section, key, BearCore::BearString()) = data;
}
