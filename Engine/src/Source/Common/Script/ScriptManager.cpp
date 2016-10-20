#include "Script/ScriptManager.h"

#include "Core/Log.h"

#include "IO/FileSystem.h"

extern "C" {
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

namespace script
{
	SINGLETON_BODY(ScriptManager);

	BOOL ScriptManager::Init()
	{
		mLuaState = luaL_newstate();

		if (!mLuaState)
			return FALSE;

		luaopen_base(mLuaState);

		luabind::open(mLuaState);

		return TRUE;
	}

	void ScriptManager::Release()
	{
		if (mLuaState)
			lua_close(mLuaState);
	}

	BOOL ScriptManager::LoadScript(const int8* aScriptName)
	{
		if (luaL_loadfile(mLuaState, (io::FileSystem::Instance()->GetCurrentDir() + "/" + aScriptName).c_str()) != NULL) {
			core::LogFormatString("Can\'t find script %s or syntax error\n", aScriptName);
			return FALSE;
		}

		if (lua_pcall(mLuaState, 0, 0, 0) != NULL) {
			core::LogFormatString("Error executting script %s: %s\n", aScriptName, lua_tostring(mLuaState, -1));
			lua_pop(mLuaState, 1);
			return FALSE;
		}

		return TRUE;

	}

	BOOL ScriptManager::ExecuteScript(const int8* aScriptName)
	{
		int32 lError = luaL_loadstring(mLuaState, aScriptName);
		if (lError != NULL)
		{
			core::LogFormatString("Error executting script %s: %d\n", aScriptName, lError);
			return FALSE;
		}

		lua_call(mLuaState, 0, 0);

		return TRUE;

	}

	int32 ScriptManager::GetGlobalInt32(const int8* aVarName, int32 aDefaultValue)
	{
		int32 lResult;

		lua_getglobal(mLuaState, aVarName);

		if (!lua_isnumber(mLuaState, -1))
			lResult = aDefaultValue;
		else
			lResult = (int32)lua_tonumber(mLuaState, -1);

		lua_pop(mLuaState, 1);

		return lResult;
	}

	float32 ScriptManager::GetGlobalFloat32(const int8* aVarName, float32 aDefaultValue)
	{
		float32 lResult;

		lua_getglobal(mLuaState, aVarName);

		if (!lua_isnumber(mLuaState, -1))
			lResult = aDefaultValue;
		else
			lResult = (float32)lua_tonumber(mLuaState, -1);

		lua_pop(mLuaState, 1);

		return lResult;
	}

	BOOL ScriptManager::GetGlobalBOOL(const int8* aVarName, BOOL aDefaultValue)
	{
		BOOL lResult;

		lua_getglobal(mLuaState, aVarName);

		if (!lua_isnumber(mLuaState, -1))
			lResult = aDefaultValue;
		else
			lResult = (int32)lua_toboolean(mLuaState, -1) == 0 ? FALSE : TRUE;
		
		lua_pop(mLuaState, 1);

		return lResult;
	}

	std::string ScriptManager::GetGlobalString(const int8* aVarName, const int8* aDefaultValue)
	{
		uint32 lLen;
		const char* lResult;

		lua_getglobal(mLuaState, aVarName);

		if (!lua_isstring(mLuaState, -1))
			lResult = aDefaultValue;
		else
			lResult = lua_tolstring(mLuaState, -1, &lLen);

		std::string lResultCopy(lResult);

		lua_pop(mLuaState, 1);

		return lResultCopy;
	}

	int32 ScriptManager::GetFieldInt32(const int8* aTableName, const int8* aFieldName, int32 aDefaultValue)
	{
		int32 lResult;

		lua_getglobal(mLuaState, aTableName);

		if (!lua_istable(mLuaState, -1)) {
			lResult = aDefaultValue;
			
			lua_pop(mLuaState, 1);
		}
		else {
			lua_pushstring(mLuaState, aFieldName);

			lua_gettable(mLuaState, -2);

			if (!lua_isnumber(mLuaState, -1))
				lResult = aDefaultValue;
			else
				lResult = (int32)lua_tonumber(mLuaState, -1);

			lua_pop(mLuaState, 2);
		}

		return lResult;
	}

	float32 ScriptManager::GetFieldFloat32(const int8* aTableName, const int8* aFieldName, float32 aDefaultValue)
	{
		float32 lResult;

		lua_getglobal(mLuaState, aTableName);

		if (!lua_istable(mLuaState, -1)) {
			lResult = aDefaultValue;

			lua_pop(mLuaState, 1);
		}
		else {
			lua_pushstring(mLuaState, aFieldName);

			lua_gettable(mLuaState, -2);

			if (!lua_isnumber(mLuaState, -1))
				lResult = aDefaultValue;
			else
				lResult = (float32)lua_tonumber(mLuaState, -1);

			lua_pop(mLuaState, 2);
		}

		return lResult;
	}

	BOOL ScriptManager::GetFieldBOOL(const int8* aTableName, const int8* aFieldName, BOOL aDefaultValue)
	{
		BOOL lResult;

		lua_getglobal(mLuaState, aTableName);

		if (!lua_istable(mLuaState, -1)) {
			lResult = aDefaultValue;

			lua_pop(mLuaState, 1);
		}
		else {
			lua_pushstring(mLuaState, aFieldName);

			lua_gettable(mLuaState, -2);

			if (!lua_isnumber(mLuaState, -1))
				lResult = aDefaultValue;
			else
				lResult = (int32)lua_toboolean(mLuaState, -1) == 0 ? FALSE : TRUE;

			lua_pop(mLuaState, 2);
		}

		return lResult;
	}

	std::string ScriptManager::GetFieldString(const int8* aTableName, const int8* aFieldName, const int8* aDefaultValue)
	{
		uint32 lLen;
		const char* lResult;
		std::string lResultCopy;

		lua_getglobal(mLuaState, aTableName);

		if (!lua_istable(mLuaState, -1)) {

			lResult = aDefaultValue;
			lResultCopy = std::string(lResult);

			// Limpiamos la pila
			lua_pop(mLuaState, 1);
		}
		else {
			lua_pushstring(mLuaState, aFieldName);

			lua_gettable(mLuaState, -2);

			if (!lua_isstring(mLuaState, -1))
				lResult = aDefaultValue;
			else {
				lResult = lua_tolstring(mLuaState, -1, &lLen);
			}

			lResultCopy = std::string(lResult);

			lua_pop(mLuaState, 2);
		}

		return lResultCopy;
	}

	void ScriptManager::RegisterFunction(lua_CFunction f, const char *aLuaFunctionName)
	{
		lua_register(mLuaState, aLuaFunctionName, f);
	}

} // namespace script