#include "PreCom.h"
#include <string.h>
#include <stdio.h>
#include "type.h"
#include "field.h"
#include "method.h"
#include "class.h"
//#include "reflect.h"

namespace okey
{


	AnyType AnyType::unknownType(AnyType::RTTI_UNKNOWN);
	AnyType AnyType::voidType(AnyType::RTTI_VOID);
	AnyType AnyType::charType(AnyType::RTTI_CHAR);
	AnyType AnyType::uint8Type(AnyType::RTTI_UINT8);
	AnyType AnyType::int8Type(AnyType::RTTI_INT8);
	AnyType AnyType::int16Type(AnyType::RTTI_INT16);
	AnyType AnyType::uint16Type(AnyType::RTTI_UINT16);
	AnyType AnyType::int32Type(AnyType::RTTI_INT32);
	AnyType AnyType::uint32Type(AnyType::RTTI_UINT32);
	AnyType AnyType::int64Type(AnyType::RTTI_INT64);
	AnyType AnyType::uint64Type(AnyType::RTTI_UINT64);
	AnyType AnyType::f32Type(AnyType::RTTI_F32);
	AnyType AnyType::f64Type(AnyType::RTTI_F64);
	AnyType AnyType::boolType(AnyType::RTTI_BOOL);


	AnyType::~AnyType() {}

	std::string AnyType::getTypeName()
	{
		std::string p = "???";
		switch (tag)
		{ 
		case RTTI_UNKNOWN:
			p = "<???>";
			break;
		case RTTI_VOID:
			p = "void";
			break;
		case RTTI_CHAR:
			p = "char";
			break;
		case RTTI_UINT8:
			p = "uint8";
			break;
		case RTTI_INT8:
			p = "int8";
			break;
		case RTTI_INT16:
			p = "int16";
			break;
		case RTTI_UINT16:
			p = "uint16";
			break;
		case RTTI_INT32:
			p = "int32";
			break;
		case RTTI_UINT32:
			p = "uint32";
			break;
		case RTTI_INT64:
			p = "int64";
			break;
		case RTTI_UINT64:
			p = "uint64";
			break;
		case RTTI_F32:
			p = "f32";
			break;
		case RTTI_F64:
			p = "f64";
			break;
		case RTTI_BOOL:
			p = "bool";
			break;
		}
		return p;
	}


	std::string PtrType::getTypeName()
	{
		std::string ptrstring = ptrType->getTypeName();
		ptrstring += "*";
		return ptrstring;
	}

	std::string ArrayType::getTypeName()
	{
		char buf[128];
		sprintf(buf, "%s[%d]",  elemType->getTypeName().c_str(), nElems);
		return buf;
	}


	std::string DerivedType::getTypeName() 
	{ 
		return baseClass->getTypeName();
	}

	std::string MethodType::getTypeName()
	{
		std::string methodstring;
		methodstring = returnType->getTypeName();
		methodstring += '(';
		methodstring += methodClass->getTypeName();
		methodstring +="::*)(";
// 		*buf++  = ':';
// 		*buf++  = ':';
// 		*buf++  = '*';
// 		*buf++  = ')';
// 		*buf++  = '(';
		for (int i = 0; i < nParams; i++) 
		{ 
			if (i != 0) 
			{ 
				methodstring += ',';
			}
			methodstring += paramTypes[i]->getTypeName();
		}
		methodstring += ')';
		return methodstring;
	}


	std::string MethodType::getMethodDeclaration(const std::string& name)
	{
		std::string methodstring;
		methodstring = returnType->getTypeName();
		methodstring += " \t";
		methodstring += methodClass->getTypeName(); 
		methodstring += "::";
		methodstring += name + "(";
		//buf += sprintf(buf, "::%s(", name);
		for (int i = 0; i < nParams; i++) 
		{ 
			if (i != 0) 
			{ 
				methodstring +=  ',';
			}
			methodstring += paramTypes[i]->getTypeName();
		}
		methodstring += ");";
// 		*buf++ = ')';
// 		*buf++ = ';';
// 		*buf = '\0';
		return methodstring;
	}

}
    


