
#ifndef __ANTISOCIALDLL_H__
#define __ANTISOCIALDLL_H__

#ifdef DLL_EXPORT
#define ANTISOCIAL_API __declspec(dllexport)
#else
#define ANTISOCIAL_API __declspec(dllimport)
#endif

#endif // __ANTISOCIALDLL_H__
