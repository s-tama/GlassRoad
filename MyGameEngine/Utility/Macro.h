//
// Macro.h
//
#pragma once


#define SAFE_RELEASE(x) if(x){x->Release(); x = NULL;}
#define SAFE_DELETE(x) if(x){delete x; x = nullptr;}
#define SAFE_RESET(x) if(x){x.reset(); x = nullptr;}

#define ALIGN16 _declspec(align(16))