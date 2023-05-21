#ifndef _GEAR_H_
#define _GEAR_H_

#include <Arduino.h>
#include <picotk.h>

/* Macros */
/* Define macros here */
#define EXAMPLE_GEAR

/* Types */
/* Define types here */

/* Function declarations */
/* Declare functions here */

extern int scene_init(void);
extern void set_rotation(GLfloat x, GLfloat y, GLfloat z);
extern int scene_update(void);

/* Extern variable declarations */
/* Declare functions here */
#endif /* defined(_GEAR_H_) */
