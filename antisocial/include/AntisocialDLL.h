
#ifndef __ANTISOCIALDLL_H__
#define __ANTISOCIALDLL_H__

#if defined(ANTISOCIAL_EXPORT) && !defined(__UNIX__)
#define ANTISOCIAL_API __declspec(dllexport)
#else
#define ANTISOCIAL_API __declspec(dllimport)
#endif

#endif // __ANTISOCIALDLL_H__
