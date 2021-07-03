#pragma once

#define DLL_INTERFACE __declspec( dllexport )   


class DLL_INTERFACE COptimizedAccessor
{
public:
	static ITest* GetObj();
};
