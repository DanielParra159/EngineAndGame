#ifndef _ENGINE_IDREFERENCES_H_
#define _ENGINE_IDREFERENCES_H_

#include "Types.h"
/**
Auxiliar class to keep the number of references of an id
*/
class IdReferences
{
public:
	int32											mId;
	uint32											mReferences;
public:
	IdReferences(int32 aId, uint32 aReferences) : mId(aId), mReferences(aReferences) {}
}; // IdReferences
#endif // _ENGINE_IDREFERENCES_H_