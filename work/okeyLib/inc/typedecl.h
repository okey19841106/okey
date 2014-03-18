#ifndef __TYPEDECL_H__
#define __TYPEDECL_H__

#define RTTI_FIELD(x, flags) \
    *new RTTIFieldDescriptor(#x, (char*)&x-(char*)this, sizeof(x), flags, RTTITypeOf(x))

#define RTTI_ARRAY(x, flags) \
    *new RTTIFieldDescriptor(#x, (char*)&x-(char*)this, sizeof(x), flags, \
			    new RTTIArrayType(RTTITypeOf(*x), sizeof(x)/sizeof(*x)))

#define RTTI_PTR(x, flags) \
    *new RTTIFieldDescriptor(#x, (char*)&x-(char*)this, sizeof(x), flags, \
			    RTTITypeOfPtr(&x))

#define RTTI_PTR_TO_PTR(x, flags) \
    *new RTTIFieldDescriptor(#x, (char*)&x-(char*)this, sizeof(x), flags, \
			    RTTITypeOfPtrToPtr(&x))

#define RTTI_BASE_CLASS(BC, flags)  \
    *new RTTIFieldDescriptor(#BC, (char*)(BC*)this - (char*)this, sizeof(BC), flags, \
                             new RTTIDerivedType(&BC::RTTIDescriptor))


#define RTTI_NO_FIELDS  (*(RTTIFieldDescriptor*)0)
#define RTTI_NO_METHODS (*(RTTIMethodDescriptor*)0)

#define RTTI_FUNC(x, flags) *new RTTIMethodDescriptor(#x, flags, RTTIFuncTypeOf(&self::x))

#define RTTI_PROC(x, flags) *new RTTIMethodDescriptor(#x, flags, RTTIProcTypeOf(&self::x))

#define RTTI_OVL_FUNC(x, signature, return_type, flags) *new RTTIMethodDescriptor(#x #signature, flags, RTTIFuncTypeOf((return_type(self::*)signature)&self::x))

#define RTTI_OVL_PROC(x, signature, flags) *new RTTIMethodDescriptor(#x #signature, flags, RTTIProcTypeOf((void(self::*)signature)&self::x))


#define RTTI_DESCRIBE_STRUCT(components) \
    static RTTIClassDescriptor RTTIDescriptor; \
    static RTTIClassDescriptor* RTTIGetClass() { \
	return &RTTIDescriptor; \
    } \
    RTTIFieldDescriptor* RTTIDescribeFields() { \
	return &components; \
    } \
    RTTIMethodDescriptor* RTTIDescribeMethods() { \
        return NULL; \
    }

#define RTTI_DESCRIBE_CLASS(T, fields, methods) \
    static RTTIClassDescriptor RTTIDescriptor; \
    static RTTIClassDescriptor* RTTIGetClass() { \
	return &RTTIDescriptor; \
    } \
    RTTIFieldDescriptor* RTTIDescribeFields() { \
	return &fields; \
    } \
    typedef T self; \
    RTTIMethodDescriptor* RTTIDescribeMethods() { \
	return &methods; \
    } \
     

#define RTTI_REGISTER_STRUCT(T, flags) RTTI_REGISTER_CLASS(T, flags)

#if defined(__GNUC__) && __GNUC_MINOR__ < 96
#define RTTI_REGISTER_CLASS(T, flags) \
    static RTTIFieldDescriptor* RTTIDescribeFieldsOf##T() { \
        return T().RTTIDescribeFields(); \
    } \
    static RTTIMethodDescriptor* RTTIDescribeMethodsOf##T() { \
        return T().RTTIDescribeMethods(); \
    } \
    static T* RTTIDefaultConstructorOf##T() { \
        return new T(); \
    } \
    RTTIClassDescriptor T::RTTIDescriptor(#T, sizeof(T), &RTTIDescribeFieldsOf##T, \
					  &RTTIDescribeMethodsOf##T, \
					 (RTTIClassDescriptor::RTTICreateInstanceFunc)&RTTIDefaultConstructorOf##T, flags); \
    RTTIClassDescriptor* RTTIGetClassDescriptor(T*) {   \
        return &T::RTTIDescriptor; \
    }

template<class __T>
inline RTTIType* RTTITypeOf(__T&) { 
    extern RTTIClassDescriptor* RTTIGetClassDescriptor(__T*);
    return RTTIGetClassDescriptor((__T*)0);
}

#else

#define RTTI_REGISTER_CLASS(T, flags) \
    static RTTIFieldDescriptor* RTTIDescribeFieldsOf##T() { \
        return T().RTTIDescribeFields(); \
    } \
    static RTTIMethodDescriptor* RTTIDescribeMethodsOf##T() { \
        return T().RTTIDescribeMethods(); \
    } \
    static T* RTTIDefaultConstructorOf##T() { \
        return new T(); \
    } \
    RTTIClassDescriptor T::RTTIDescriptor(#T, sizeof(T), &RTTIDescribeFieldsOf##T, \
					  &RTTIDescribeMethodsOf##T, \
					 (RTTIClassDescriptor::RTTICreateInstanceFunc)&RTTIDefaultConstructorOf##T, flags); \
    template<> \
    RTTIClassDescriptor* RTTIClassDescriptorHelper<T>::getClassDescriptor() {   \
        return &T::RTTIDescriptor; \
    }

template<class __T>
class RTTIClassDescriptorHelper { 
 public:
    static RTTIClassDescriptor* getClassDescriptor();
};

template<class __T>
inline RTTIType* RTTITypeOf(__T&) { 
    return RTTIClassDescriptorHelper<__T>::getClassDescriptor();
}
#endif

template<>
inline RTTIType* RTTITypeOf(char&) { 
    return &RTTIType::charType;
}

template<>
inline RTTIType* RTTITypeOf(unsigned char&) {
    return &RTTIType::ucharType;
}

template<>
inline RTTIType* RTTITypeOf(signed char&) {
    return &RTTIType::scharType;
}

template<>
inline RTTIType* RTTITypeOf(short&) {
    return &RTTIType::shortType;
}

template<>
inline RTTIType* RTTITypeOf(unsigned short&) { 
    return &RTTIType::ushortType;
}

template<>
inline RTTIType* RTTITypeOf(int&) {
    return &RTTIType::intType;
}

template<>
inline RTTIType* RTTITypeOf(unsigned int&) { 
    return &RTTIType::uintType;
}

template<>
inline RTTIType* RTTITypeOf(long&) { 
    return &RTTIType::longType;
}

template<>
inline RTTIType* RTTITypeOf(unsigned long&) { 
    return &RTTIType::ulongType;
}

template<>
inline RTTIType* RTTITypeOf(float&) { 
    return &RTTIType::floatType;
}

template<>
inline RTTIType* RTTITypeOf(double&) { 
    return &RTTIType::doubleType;
}

template<>
inline RTTIType* RTTITypeOf(bool&) { 
    return &RTTIType::boolType;
}


const int RTTI_MAX_PARAMETERS = 5;


inline RTTIType* RTTITypeOfPtr(char*) { 
    return &RTTIType::charType;
}

inline RTTIType* RTTITypeOfPtr(unsigned char*) {
    return &RTTIType::ucharType;
}

inline RTTIType* RTTITypeOfPtr(signed char*) {
    return &RTTIType::scharType;
}

inline RTTIType* RTTITypeOfPtr(short*) {
    return &RTTIType::shortType;
}

inline RTTIType* RTTITypeOfPtr(unsigned short*) { 
    return &RTTIType::ushortType;
}

inline RTTIType* RTTITypeOfPtr(int*) {
    return &RTTIType::intType;
}

inline RTTIType* RTTITypeOfPtr(unsigned int*) { 
    return &RTTIType::uintType;
}

inline RTTIType* RTTITypeOfPtr(long*) { 
    return &RTTIType::longType;
}

inline RTTIType* RTTITypeOfPtr(unsigned long*) { 
    return &RTTIType::ulongType;
}

inline RTTIType* RTTITypeOfPtr(float*) { 
    return &RTTIType::floatType;
}

inline RTTIType* RTTITypeOfPtr(double*) { 
    return &RTTIType::doubleType;
}

inline RTTIType* RTTITypeOfPtr(bool*) { 
    return &RTTIType::boolType;
}
inline RTTIType* RTTITypeOfPtr(void*) { 
    return &RTTIType::voidType;
}


#if defined(__GNUC__) && __GNUC_MINOR__ < 96
template<class __P>
inline RTTIType* RTTITypeOfPtr(__P const*const*) { 
    extern RTTIClassDescriptor* RTTIGetClassDescriptor(__P*);
    return new RTTIPtrType(RTTIGetClassDescriptor((__P*)0));
}
#else
template<class __P>
inline RTTIType* RTTITypeOfPtr(__P const*const*) { 
    return new RTTIPtrType(&__P::RTTIDescriptor);
}
#endif


template<>
inline RTTIType* RTTITypeOfPtr(char const*const*) { 
    return new RTTIPtrType(&RTTIType::charType);
}

template<>
inline RTTIType* RTTITypeOfPtr(unsigned char const*const*) {
    return new RTTIPtrType(&RTTIType::ucharType);
}

template<>
inline RTTIType* RTTITypeOfPtr(signed char const*const*) {
    return new RTTIPtrType(&RTTIType::scharType);
}

template<>
inline RTTIType* RTTITypeOfPtr(short const*const*) {
    return new RTTIPtrType(&RTTIType::shortType);
}

template<>
inline RTTIType* RTTITypeOfPtr(unsigned short const*const*) { 
    return new RTTIPtrType(&RTTIType::ushortType);
}

template<>
inline RTTIType* RTTITypeOfPtr(int const*const*) {
    return new RTTIPtrType(&RTTIType::intType);
}

template<>
inline RTTIType* RTTITypeOfPtr(unsigned int const*const*) { 
    return new RTTIPtrType(&RTTIType::uintType);
}

template<>
inline RTTIType* RTTITypeOfPtr(long const*const*) { 
    return new RTTIPtrType(&RTTIType::longType);
}

template<>
inline RTTIType* RTTITypeOfPtr(unsigned long const*const*) { 
    return new RTTIPtrType(&RTTIType::ulongType);
}

template<>
inline RTTIType* RTTITypeOfPtr(float const*const*) { 
    return new RTTIPtrType(&RTTIType::floatType);
}

template<>
inline RTTIType* RTTITypeOfPtr(double const*const*) { 
    return new RTTIPtrType(&RTTIType::doubleType);
}

template<>
inline RTTIType* RTTITypeOfPtr(bool const*const*) { 
    return new RTTIPtrType(&RTTIType::boolType);
}

template<>
inline RTTIType* RTTITypeOfPtr(void const*const*) { 
    return new RTTIPtrType(&RTTIType::voidType);
}

#if defined(__GNUC__) && __GNUC_MINOR__ < 96
template<class __P>
inline RTTIType* RTTITypeOfPtrToPtr(__P const*const*const*) { 
    extern RTTIClassDescriptor* RTTIGetClassDescriptor(__P*);
    return new RTTIPtrType(new RTTIPtrType(RTTIGetClassDescriptor((__P*)0)));
}
#else
template<class __P>
inline RTTIType* RTTITypeOfPtrToPtr(__P const*const*const*) { 
    return new RTTIPtrType(new RTTIPtrType(&__P::RTTIDescriptor));
}
#endif
    
template<class __RT, class __C>
class RTTIFuncType0 : public RTTIMethodType { 
  public:
    typedef __RT (__C::*fptr)();
    fptr f;
    RTTIFuncType0(fptr f) { 
	this->f = f;
	methodClass = &__C::RTTIDescriptor;
	returnType = RTTITypeOfPtr((__RT*)0);
	nParams = 0;
	paramTypes = NULL;
    }
    void invoke(void* result, void* obj, void* params[]) { 
	*(__RT*)result = (((__C*)obj)->*f)();
    }
};

template<class __RT, class __C, class __P1>
class RTTIFuncType1 : public RTTIMethodType{ 
  public:
    typedef __RT (__C::*fptr)(__P1);
    fptr f;
    RTTIFuncType1(fptr f) { 
	this->f = f;
	methodClass = &__C::RTTIDescriptor;
	returnType = RTTITypeOfPtr((__RT*)0);
	nParams = 1;
	paramTypes = new RTTIType*[1];
	paramTypes[0] = RTTITypeOfPtr((__P1*)0);
    }
    void invoke(void* result, void* obj, void* params[]) { 
	*(__RT*)result = (((__C*)obj)->*f)(*(__P1*)params[0]);
    }
};

template<class __RT, class __C, class __P1, class __P2>
class RTTIFuncType2 : public RTTIMethodType{ 
  public:
    typedef __RT (__C::*fptr)(__P1, __P2);
    fptr f;
    RTTIFuncType2(fptr f) { 
	this->f = f;
	methodClass = &__C::RTTIDescriptor;
	returnType = RTTITypeOfPtr((__RT*)0);
	nParams = 2;
	paramTypes = new RTTIType*[2];
	paramTypes[0] = RTTITypeOfPtr((__P1*)0);
	paramTypes[1] = RTTITypeOfPtr((__P2*)0);
    }
    void invoke(void* result, void* obj, void* params[]) { 
	*(__RT*)result = (((__C*)obj)->*f)(*(__P1*)params[0], *(__P2*)params[1]);
    }
};

template<class __RT, class __C, class __P1, class __P2, class __P3>
class RTTIFuncType3 : public RTTIMethodType{ 
  public:
    typedef __RT (__C::*fptr)(__P1, __P2, __P3);
    fptr f;
    RTTIFuncType3(fptr f) { 
	this->f = f;
	methodClass = &__C::RTTIDescriptor;
	returnType = RTTITypeOfPtr((__RT*)0);
	nParams = 3;
	paramTypes = new RTTIType*[3];
	paramTypes[0] = RTTITypeOfPtr((__P1*)0);
	paramTypes[1] = RTTITypeOfPtr((__P2*)0);
	paramTypes[2] = RTTITypeOfPtr((__P3*)0);
    }
    void invoke(void* result, void* obj, void* params[]) { 
	*(__RT*)result = (((__C*)obj)->*f)(*(__P1*)params[0], *(__P2*)params[1], *(__P3*)params[2]);
    }
};

template<class __RT, class __C, class __P1, class __P2, class __P3, class __P4>
class RTTIFuncType4 : public RTTIMethodType{ 
  public:
    typedef __RT (__C::*fptr)(__P1, __P2, __P3, __P4);
    fptr f;
    RTTIFuncType4(fptr f) { 
	this->f = f;
	methodClass = &__C::RTTIDescriptor;
	returnType = RTTITypeOfPtr((__RT*)0);
	nParams = 4;
	paramTypes = new RTTIType*[4];
	paramTypes[0] = RTTITypeOfPtr((__P1*)0);
	paramTypes[1] = RTTITypeOfPtr((__P2*)0);
	paramTypes[2] = RTTITypeOfPtr((__P3*)0);
	paramTypes[3] = RTTITypeOfPtr((__P4*)0);
    }
    void invoke(void* result, void* obj, void* params[]) { 
	*(__RT*)result = (((__C*)obj)->*f)(*(__P1*)params[0], *(__P2*)params[1], *(__P3*)params[2], *(__P4*)params[3]);
    }
};

template<class __RT, class __C, class __P1, class __P2, class __P3, class __P4, class __P5>
class RTTIFuncType5 : public RTTIMethodType{ 
  public:
    typedef __RT (__C::*fptr)(__P1, __P2, __P3, __P4, __P5);
    fptr f;
    RTTIFuncType5(fptr f) { 
	this->f = f;
	methodClass = &__C::RTTIDescriptor;
	returnType = RTTITypeOfPtr((__RT*)0);
	nParams = 5;
	paramTypes = new RTTIType*[5];
	paramTypes[0] = RTTITypeOfPtr((__P1*)0);
	paramTypes[1] = RTTITypeOfPtr((__P2*)0);
	paramTypes[2] = RTTITypeOfPtr((__P3*)0);
	paramTypes[3] = RTTITypeOfPtr((__P4*)0);
	paramTypes[4] = RTTITypeOfPtr((__P5*)0);
    }
    void invoke(void* result, void* obj, void* params[]) { 
	*(__RT*)result = (((__C*)obj)->*f)(*(__P1*)params[0], *(__P2*)params[1], *(__P3*)params[2], *(__P4*)params[3], *(__P5*)params[4]);
    }
};


template<class __C>
class RTTIProcType0 : public RTTIMethodType { 
  public:
    typedef void (__C::*fptr)();
    fptr f;
    RTTIProcType0(fptr f) { 
	this->f = f;
	methodClass = &__C::RTTIDescriptor;
	returnType = &voidType;
	nParams = 0;
	paramTypes = NULL;
    }
    void invoke(void*, void* obj, void* params[]) { 
	(((__C*)obj)->*f)();
    }
};

template<class __C, class __P1>
class RTTIProcType1 : public RTTIMethodType{ 
  public:
    typedef void (__C::*fptr)(__P1);
    fptr f;
    RTTIProcType1(fptr f) { 
	this->f = f;
	methodClass = &__C::RTTIDescriptor;
	returnType = &voidType;
	nParams = 1;
	paramTypes = new RTTIType*[1];
	paramTypes[0] = RTTITypeOfPtr((__P1*)0);
    }
    void invoke(void*, void* obj, void* params[]) { 
	(((__C*)obj)->*f)(*(__P1*)params[0]);
    }
};

template<class __C, class __P1, class __P2>
class RTTIProcType2 : public RTTIMethodType{ 
  public:
    typedef void (__C::*fptr)(__P1, __P2);
    fptr f;
    RTTIProcType2(fptr f) { 
	this->f = f;
	methodClass = &__C::RTTIDescriptor;
	returnType = &voidType;
	nParams = 2;
	paramTypes = new RTTIType*[2];
	paramTypes[0] = RTTITypeOfPtr((__P1*)0);
	paramTypes[1] = RTTITypeOfPtr((__P2*)0);
    }
    void invoke(void*, void* obj, void* params[]) { 
	(((__C*)obj)->*f)(*(__P1*)params[0], *(__P2*)params[1]);
    }
};

template<class __C, class __P1, class __P2, class __P3>
class RTTIProcType3 : public RTTIMethodType{ 
  public:
    typedef void (__C::*fptr)(__P1, __P2, __P3);
    fptr f;
    RTTIProcType3(fptr f) { 
	this->f = f;
	methodClass = &__C::RTTIDescriptor;
	returnType = &voidType;
	nParams = 3;
	paramTypes = new RTTIType*[3];
	paramTypes[0] = RTTITypeOfPtr((__P1*)0);
	paramTypes[1] = RTTITypeOfPtr((__P2*)0);
	paramTypes[2] = RTTITypeOfPtr((__P3*)0);
    }
    void invoke(void*, void* obj, void* params[]) { 
	(((__C*)obj)->*f)(*(__P1*)params[0], *(__P2*)params[1], *(__P3*)params[2]);
    }
};

template<class __C, class __P1, class __P2, class __P3, class __P4>
class RTTIProcType4 : public RTTIMethodType{ 
  public:
    typedef void (__C::*fptr)(__P1, __P2, __P3, __P4);
    fptr f;
    RTTIProcType4(fptr f) { 
	this->f = f;
	methodClass = &__C::RTTIDescriptor;
	returnType = &voidType;
	nParams = 4;
	paramTypes = new RTTIType*[4];
	paramTypes[0] = RTTITypeOfPtr((__P1*)0);
	paramTypes[1] = RTTITypeOfPtr((__P2*)0);
	paramTypes[2] = RTTITypeOfPtr((__P3*)0);
	paramTypes[3] = RTTITypeOfPtr((__P4*)0);
    }
    void invoke(void*, void* obj, void* params[]) { 
	(((__C*)obj)->*f)(*(__P1*)params[0], *(__P2*)params[1], *(__P3*)params[2], *(__P4*)params[3]);
    }
};

template<class __C, class __P1, class __P2, class __P3, class __P4, class __P5>
class RTTIProcType5 : public RTTIMethodType { 
  public:
    typedef void (__C::*fptr)(__P1, __P2, __P3, __P4, __P5);
    fptr f;
    RTTIProcType5(fptr f) { 
	this->f = f;
	methodClass = &__C::RTTIDescriptor;
	returnType = &voidType;
	nParams = 5;
	paramTypes = new RTTIType*[5];
	paramTypes[0] = RTTITypeOfPtr((__P1*)0);
	paramTypes[1] = RTTITypeOfPtr((__P2*)0);
	paramTypes[2] = RTTITypeOfPtr((__P3*)0);
	paramTypes[3] = RTTITypeOfPtr((__P4*)0);
	paramTypes[4] = RTTITypeOfPtr((__P5*)0);
    }
    void invoke(void*, void* obj, void* params[]) { 
	(((__C*)obj)->*f)(*(__P1*)params[0], *(__P2*)params[1], *(__P3*)params[2], *(__P4*)params[3], *(__P5*)params[4]);
    }
};


template<class __RT, class __C>
inline RTTIMethodType* RTTIFuncTypeOf(__RT (__C::*f)()) { 
    return new RTTIFuncType0<__RT, __C>(f);
}

template<class __RT, class __C, class __P1>
inline RTTIMethodType* RTTIFuncTypeOf(__RT (__C::*f)(__P1)) { 
    return new RTTIFuncType1<__RT, __C, __P1>(f);
}

template<class __RT, class __C, class __P1, class __P2>
inline RTTIMethodType* RTTIFuncTypeOf(__RT (__C::*f)(__P1, __P2)) { 
    return new RTTIFuncType2<__RT, __C, __P1, __P2>(f);
}

template<class __RT, class __C, class __P1, class __P2, class __P3>
inline RTTIMethodType* RTTIFuncTypeOf(__RT (__C::*f)(__P1, __P2, __P3)) { 
    return new RTTIFuncType3<__RT, __C, __P1, __P2, __P3>(f);
}

template<class __RT, class __C, class __P1, class __P2, class __P3, class __P4>
inline RTTIMethodType* RTTIFuncTypeOf(__RT (__C::*f)(__P1, __P2, __P3, __P4)) { 
    return new RTTIFuncType4<__RT, __C, __P1, __P2, __P3, __P4>(f);
}

template<class __RT, class __C, class __P1, class __P2, class __P3, class __P4, class __P5>
inline RTTIMethodType* RTTIFuncTypeOf(__RT (__C::*f)(__P1, __P2, __P3, __P4, __P5)) { 
    return new RTTIFuncType5<__RT, __C, __P1, __P2, __P3, __P4, __P5>(f);
}


template<class __C>
inline RTTIMethodType* RTTIProcTypeOf(void (__C::*f)()) { 
    return new RTTIProcType0<__C>(f);
}

template<class __C, class __P1>
inline RTTIMethodType* RTTIProcTypeOf(void (__C::*f)(__P1)) { 
    return new RTTIProcType1<__C, __P1>(f);
}

template<class __C, class __P1, class __P2>
inline RTTIMethodType* RTTIProcTypeOf(void (__C::*f)(__P1, __P2)) { 
    return new RTTIProcType2<__C, __P1, __P2>(f);
}

template<class __C, class __P1, class __P2, class __P3>
inline RTTIMethodType* RTTIProcTypeOf(void (__C::*f)(__P1, __P2, __P3)) { 
    return new RTTIProcType3<__C, __P1, __P2, __P3>(f);
}

template<class __C, class __P1, class __P2, class __P3, class __P4>
inline RTTIMethodType* RTTIProcTypeOf(void (__C::*f)(__P1, __P2, __P3, __P4)) { 
    return new RTTIProcType4<__C, __P1, __P2, __P3, __P4>(f);
}

template<class __C, class __P1, class __P2, class __P3, class __P4, class __P5>
inline RTTIMethodType* RTTIProcTypeOf(void (__C::*f)(__P1, __P2, __P3, __P4, __P5)) { 
    return new RTTIProcType5<__C, __P1, __P2, __P3, __P4, __P5>(f);
}

#endif
