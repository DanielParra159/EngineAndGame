#ifndef _ENGINE_SCRIPT_SCRIPTMANAGER_H_
#define _ENGINE_SCRIPT_SCRIPTMANAGER_H_

#include "Defs.h"
#include "Types.h"

#include <string>

struct lua_State;
typedef int(*lua_CFunction) (lua_State *L);

namespace script
{
	/**
	This class will be responsible to manager and execute scripts
	*/
	class ScriptManager
	{
		SINGLETON_HEAD(ScriptManager);
	private:
		lua_State*										mLuaState;
	public:
		BOOL											Init();
		void											Release();

		BOOL											LoadScript(const int8* aScriptName);
		BOOL											ExecuteScript(const int8* aScriptName);

		int32											GetGlobalInt32(const int8* aVarName, int32 aDefaultValue);
		float32											GetGlobalFloat32(const int8* aVarName, float32 aDefaultValue);
		BOOL											GetGlobalBOOL(const int8* aVarName, BOOL aDefaultValue);
		std::string										GetGlobalString(const int8* aVarName, const int8* aDefaultValue);

		int32											GetFieldInt32(const int8* aTableName, const int8* aFieldName, int32 aDefaultValue);
		float32											GetFieldFloat32(const int8* aTableName, const int8* aFieldName, float32 aDefaultValue);
		BOOL											GetFieldBOOL(const int8* aTableName, const int8* aFieldName, BOOL aDefaultValue);
		std::string										GetFieldString(const int8* aTableName, const int8* aFieldName, const int8* aDefaultValue);

		void											RegisterFunction(lua_CFunction aFunction, const char *aLuaFunctionName);

		lua_State*										GetNativeInterpreter() { return mLuaState; }

	private:
		ScriptManager() : mLuaState() {}
		~ScriptManager(){}

	}; // ScriptManager
} // namespace script
#endif // _ENGINE_SCRIPT_SCRIPTMANAGER_H_
