#ifndef __XMLOutputArchive_H__
#define __XMLOutputArchive_H__

#include "Engine/Resource/Serialize/SerializeListener.h"

class TiXmlDocument;
class TiXmlElement;
class IAllocator;

namespace ma
{
	class ENGINE_API XMLOutputArchive : public SerializeListener 
	{
		std::string		m_strFilename;
		TiXmlDocument*	m_pDoc;
		TiXmlElement*	m_pParentElem;

	public:
		XMLOutputArchive();

		~XMLOutputArchive();

		void Release();

		bool IsReading() const;

		bool Open(const char* pszFilename);

		void Close();

		bool OpenToMemory();

		//bool SaveToMemory(char** ppData,UINT* pDataSize,IAllocator* pAlloc);

		void BeginSection(const char* pszLable);

		void EndSection();

		void Serialize(bool& val,const char* pszLable = "bool");

		void Serialize(unsigned char& val, const char* pszLabel = "unsigned char");

		void Serialize(char& val,const char* pszLable);

		void Serialize(short& val,const char* pszLable);

		void Serialize(unsigned short& val, const char* pszLabel);

		void Serialize(unsigned int&val,const char* pszLable = "unsigned int");

		void Serialize(int&val,const char* pszLable = "int");

		void Serialize(unsigned long &val,const char* pszLable = "unsigned long");

		void Serialize(long &val,const char* pszLable = "long");


		void Serialize(Uint64&val,const char* pszLable = "Uint64");

		void Serialize(float& val,const char* pszLable = "float");

		void Serialize(std::string& val,const char* pszLable = "string");

		//void Serialize(IStringWrapper* val,const char* pszLable = "string");

		SerializeListener* GetSerializeListener();

	};

}



#endif// __XMLOutputArchive_H__