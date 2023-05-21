#ifndef _PICOTK_H_
#define _PICOTK_H_

#include <GL/gl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

/* Macros */
/* Define macros here */

/* Types */
/* Define types here */

#ifdef __cplusplus
extern "C"
{
#endif

    /* Function declarations */
    /* Declare functions here */
    void reshape(int width, int height);
    int ui_init(int (*init)(void), int (*update)(void));
    void ui_loop(void);
    void tkSwapBuffers(void);

    /* Extern variable declarations */
    /* Declare functions here */

#ifdef __cplusplus
}
#endif

#endif /* defined(_PICOTK_H_) */
