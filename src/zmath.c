/*
 * Some simple mathematical functions.
 */
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/internal/zmath.h>


/* ******* Gestion des matrices 4x4 ****** */

void gl_M4_Id(M4 *a)
{
	int i,j;
	for(i=0;i<4;i++)
	for(j=0;j<4;j++) 
	if (i==j) a->m[i][j]=int2sll(1); else a->m[i][j]=int2sll(0);
}

int gl_M4_IsId(M4 *a)
{
	int i,j;
	for(i=0;i<4;i++)
    for(j=0;j<4;j++) {
      if (i==j) { 
        if (sllvalue(a->m[i][j]) != sllvalue(int2sll(1))) return 0;
      } else if (sllvalue(a->m[i][j]) != sllvalue(int2sll(0))) return 0;
    }
  return 1;
}

void gl_M4_Mul(M4 *c,M4 *a,M4 *b)
{
  int i,j,k;
  GLfloat s;
  for(i=0;i<4;i++)
    for(j=0;j<4;j++) {
      s=int2sll(0);
      for(k=0;k<4;k++) s=slladd(s,sllmul(a->m[i][k],b->m[k][j]));
      c->m[i][j]=s;
    }
}

/* c=c*a */
void gl_M4_MulLeft(M4 *c,M4 *b)
{
  int i,j,k;
  GLfloat s;
  M4 a;

  /*memcpy(&a, c, 16*sizeof(GLfloat));
  */
  a=*c;

  for(i=0;i<4;i++)
    for(j=0;j<4;j++) {
      s=int2sll(0);
      for(k=0;k<4;k++) s=slladd(s,sllmul(a.m[i][k],b->m[k][j]));
      c->m[i][j]=s;
    }
}

void gl_M4_Move(M4 *a,M4 *b)
{
	memcpy(a,b,sizeof(M4));
}

void gl_MoveV3(V3 *a,V3 *b)
{
	memcpy(a,b,sizeof(V3));
}


void gl_MulM4V3(V3 *a,M4 *b,V3 *c)
{
	 a->X=slladd(slladd(slladd(sllmul(b->m[0][0],c->X), sllmul(b->m[0][1],c->Y)), sllmul(b->m[0][2], c->Z)), b->m[0][3]);
	 a->Y=slladd(slladd(slladd(sllmul(b->m[1][0],c->X), sllmul(b->m[1][1],c->Y)), sllmul(b->m[1][2], c->Z)), b->m[1][3]);
	 a->Z=slladd(slladd(slladd(sllmul(b->m[2][0],c->X), sllmul(b->m[2][1],c->Y)), sllmul(b->m[2][2], c->Z)), b->m[2][3]);
}

void gl_MulM3V3(V3 *a,M4 *b,V3 *c)
{
	 a->X=slladd(slladd(sllmul(b->m[0][0],c->X), sllmul(b->m[0][1],c->Y)), sllmul(b->m[0][2],c->Z));
	 a->Y=slladd(slladd(sllmul(b->m[1][0],c->X), sllmul(b->m[1][1],c->Y)), sllmul(b->m[1][2],c->Z));
	 a->Z=slladd(slladd(sllmul(b->m[2][0],c->X), sllmul(b->m[2][1],c->Y)), sllmul(b->m[2][2],c->Z));
}

void gl_M4_MulV4(V4 *a,M4 *b,V4 *c)
{
	 a->X=slladd(slladd(slladd(sllmul(b->m[0][0],c->X), sllmul(b->m[0][1],c->Y)), sllmul(b->m[0][2],c->Z)), sllmul(b->m[0][3],c->W));
	 a->Y=slladd(slladd(slladd(sllmul(b->m[1][0],c->X), sllmul(b->m[1][1],c->Y)), sllmul(b->m[1][2],c->Z)), sllmul(b->m[1][3],c->W));
	 a->Z=slladd(slladd(slladd(sllmul(b->m[2][0],c->X), sllmul(b->m[2][1],c->Y)), sllmul(b->m[2][2],c->Z)), sllmul(b->m[2][3],c->W));
	 a->W=slladd(slladd(slladd(sllmul(b->m[3][0],c->X), sllmul(b->m[3][1],c->Y)), sllmul(b->m[3][2],c->Z)), sllmul(b->m[3][3],c->W));
}
	
/* transposition of a 4x4 matrix */
void gl_M4_Transpose(M4 *a,M4 *b)
{
  a->m[0][0]=b->m[0][0]; 
  a->m[0][1]=b->m[1][0]; 
  a->m[0][2]=b->m[2][0]; 
  a->m[0][3]=b->m[3][0]; 

  a->m[1][0]=b->m[0][1]; 
  a->m[1][1]=b->m[1][1]; 
  a->m[1][2]=b->m[2][1]; 
  a->m[1][3]=b->m[3][1]; 

  a->m[2][0]=b->m[0][2]; 
  a->m[2][1]=b->m[1][2]; 
  a->m[2][2]=b->m[2][2]; 
  a->m[2][3]=b->m[3][2]; 

  a->m[3][0]=b->m[0][3]; 
  a->m[3][1]=b->m[1][3]; 
  a->m[3][2]=b->m[2][3]; 
  a->m[3][3]=b->m[3][3]; 
}

/* inversion of an orthogonal matrix of type Y=M.X+P */ 
void gl_M4_InvOrtho(M4 *a,M4 b)
{
	int i,j;
	GLfloat s;
	for(i=0;i<3;i++)
	for(j=0;j<3;j++) a->m[i][j]=b.m[j][i];
	a->m[3][0]=int2sll(0); a->m[3][1]=int2sll(0); a->m[3][2]=int2sll(0); a->m[3][3]=int2sll(1);
	for(i=0;i<3;i++) {
		s=int2sll(0);
		for(j=0;j<3;j++) s=sllsub(s, sllmul(b.m[j][i],b.m[j][3]));
		a->m[i][3]=s;
	}
}

/* Inversion of a general nxn matrix.
   Note : m is destroyed */

int Matrix_Inv(GLfloat *r,GLfloat *m,int n)
{
	 int i,j,k,l;
	 GLfloat max,tmp,t;

	 /* identit�e dans r */
	 for(i=0;i<n*n;i++) r[i]=int2sll(0);
	 for(i=0;i<n;i++) r[i*n+i]=int2sll(1);
	 
	 for(j=0;j<n;j++) {
			
			/* recherche du nombre de plus grand module sur la colonne j */
			max=m[j*n+j];
			k=j;
			for(i=j+1;i<n;i++)
				if (sllvalue(sll_abs(m[i*n+j]))>sllvalue(sll_abs(max))) {
					 k=i;
					 max=m[i*n+j];
				}

      /* non intersible matrix */
      if (sllvalue(max)==sllvalue(int2sll(0))) return 1;

			
			/* permutation des lignes j et k */
			if (k!=j) {
				 for(i=0;i<n;i++) {
						tmp=m[j*n+i];
						m[j*n+i]=m[k*n+i];
						m[k*n+i]=tmp;
						
						tmp=r[j*n+i];
						r[j*n+i]=r[k*n+i];
						r[k*n+i]=tmp;
				 }
			}
			
			/* multiplication de la ligne j par 1/max */
			max=slldiv(int2sll(1), max);
			for(i=0;i<n;i++) {
				tmp=m[j*n+i];
				 m[j*n+i]=sllmul(tmp, max);
				tmp=r[j*n+i];
				 r[j*n+i]=sllmul(tmp, max);
			}
			
			
			for(l=0;l<n;l++) if (l!=j) {
				 t=m[l*n+j];
				 for(i=0;i<n;i++) {
						tmp=m[l*n+i];
						m[l*n+i]=sllsub(tmp, sllmul(m[j*n+i],t));
						tmp=r[l*n+i];
						r[l*n+i]=sllsub(tmp, sllmul(r[j*n+i],t));
				 }
			}
	 }

	 return 0;
}


/* inversion of a 4x4 matrix */

void gl_M4_Inv(M4 *a,M4 *b)
{
  M4 tmp;
  memcpy(&tmp, b, 16*sizeof(GLfloat));
  /*tmp=*b;*/
  Matrix_Inv(&a->m[0][0],&tmp.m[0][0],4);
}

void gl_M4_Rotate(M4 *a,GLfloat t,int u)
{
	GLfloat s,c;
	int v,w;
	if ((v=u+1)>2) v=0;
	if ((w=v+1)>2) w=0;
	s=sllsin(t);
	c=sllcos(t);
	gl_M4_Id(a);
	a->m[v][v]=c;	a->m[v][w]=sllneg(s);
	a->m[w][v]=s;	a->m[w][w]=c;
}
	

/* inverse of a 3x3 matrix */
void gl_M3_Inv(M3 *a,M3 *m)
{
	 GLfloat det;
	 
	 det =
	     sllsub(
	      slladd(
	       slladd(	
		sllsub(
		 sllsub(sllmul(sllmul(m->m[0][0], m->m[1][1]), m->m[2][2]),
	 		sllmul(sllmul(m->m[0][0], m->m[1][2]), m->m[2][1])), 
		 sllmul(sllmul(m->m[1][0], m->m[0][1]), m->m[2][2])), 
		sllmul(sllmul(m->m[1][0], m->m[0][2]), m->m[2][1])),
	       sllmul(sllmul(m->m[2][0], m->m[0][1]), m->m[1][2])),
	      sllmul(sllmul(m->m[2][0], m->m[0][2]), m->m[1][1]));

	 a->m[0][0] = slldiv(sllsub(sllmul(m->m[1][1],m->m[2][2]), sllmul(m->m[1][2],m->m[2][1])), det);
	 a->m[0][1] = sllneg(slldiv(sllsub(sllmul(m->m[0][1],m->m[2][2]), sllmul(m->m[0][2],m->m[2][1])), det));
	 a->m[0][2] = sllneg(slldiv(slladd(sllmul(sllneg(m->m[0][1]),m->m[1][2]), sllmul(m->m[0][2], m->m[1][1])), det));
	 
	 a->m[1][0] = sllneg(slldiv(sllsub(sllmul(m->m[1][0],m->m[2][2]), sllmul(m->m[1][2],m->m[2][0])), det));
	 a->m[1][1] = slldiv(sllsub(sllmul(m->m[0][0],m->m[2][2]), sllmul(m->m[0][2],m->m[2][0])), det);
	 a->m[1][2] = sllneg(slldiv(sllsub(sllmul(m->m[0][0],m->m[1][2]), sllmul(m->m[0][2],m->m[1][0])), det));

	 a->m[2][0] = slldiv(sllsub(sllmul(m->m[1][0],m->m[2][1]), sllmul(m->m[1][1],m->m[2][0])), det);
	 a->m[2][1] = sllneg(slldiv(sllsub(sllmul(m->m[0][0],m->m[2][1]), sllmul(m->m[0][1],m->m[2][0])), det));
	 a->m[2][2] = slldiv(sllsub(sllmul(m->m[0][0],m->m[1][1]), sllmul(m->m[0][1],m->m[1][0])), det);
}

																										
/* vector arithmetic */

int gl_V3_Norm(V3 *a)
{
	GLfloat n;
	n=sllsqrt(slladd(slladd(sllmul(a->X,a->X), sllmul(a->Y,a->Y)), sllmul(a->Z,a->Z)));
	if (sllvalue(n)==sllvalue(int2sll(0))) return 1;
	a->X=slldiv(a->X, n);
	a->Y=slldiv(a->Y, n);
	a->Z=slldiv(a->Z, n);
	return 0;
}

V3 gl_V3_New(GLfloat x,GLfloat y,GLfloat z)
{
	 V3 a;
	 a.X=x;
	 a.Y=y;
	 a.Z=z;
	 return a;
}

V4 gl_V4_New(GLfloat x,GLfloat y,GLfloat z,GLfloat w)
{
  V4 a;
  a.X=x;
  a.Y=y;
  a.Z=z;
  a.W=w;
  return a;
}


