#ifndef BRANCH_HINTS_H
#define BRANCH_HINTS_H

#if defined(__GNUC__) || defined(__clang__)
#define LIKELY(x)	__builtin_expect(!!(x), 1)
#define UNLIKELY(x)	__builtin_expect(!!(x), 0)
#else
#define LIKELY(x) (x)
#define UNLIKELY(x) (x)
#endif

#endif
