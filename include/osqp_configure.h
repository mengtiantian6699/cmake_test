#ifndef OSQP_CONFIGURE_H
#define OSQP_CONFIGURE_H

/* DEBUG */
/* #undef DEBUG */

/* Operating system */
/* #undef IS_LINUX */
/* #undef IS_MAC */
/* #undef IS_WINDOWS */

/* EMBEDDED */
/* #undef EMBEDDED */

/* PRINTING */
#define PRINTING

/* PROFILING */
/* #undef PROFILING */

/* CTRLC */
/* #undef CTRLC */

/* DFLOAT */
/* #undef DFLOAT */

/* DLONG */
/* #undef DLONG */

/* ENABLE_MKL_PARDISO */
/* #undef ENABLE_MKL_PARDISO */

/* MEMORY MANAGEMENT */
/* #undef OSQP_CUSTOM_MEMORY */
#ifdef OSQP_CUSTOM_MEMORY
#include ""
#endif

#endif /* ifndef OSQP_CONFIGURE_H */
