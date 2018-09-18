#ifndef __XTDCORE_H__
#define __XTDCORE_H__

void xtdcore_systemInit(void);
void xtdcore_systemUpdate(void);
void xtdcore_clearRenderBuffer(void);
int xtdcore_saveJpgTextures(int width, int height);

typedef struct _brushresinfo_
{
	int     		visible;
	int				position_x1;
	int				position_y1;
	int				position_x2;
	int				position_y2;
} brushresinfo;

#define VIDEO_CHN1				0
#define RESTYPE_BACKGROUND		0
#define RESTYPE_VIDEO			1
#define RESTYPE_DIAL			2
#define RESTYPE_PROGRESSBAR		3
#define RESTYPE_BITMAP			4
#define RESTYPE_STRING			5
#define RESUPDATE_DONNOT		0
#define RESUPDATE_TEXTURE		1
#define RESUPDATE_POSITION		2
typedef struct  _picresinfo_
{
	int 			update;
	int				visible;
	int 			restype;						// 0:background  1:video  2:dial  3:progressbar  4:bitmap  5:string 
	char			filename[40];
	int				position_x;
	int				position_y;
	int				size_x;
	int				size_y;
	int 			color;
	float			rotation;
	int				rotation_centerx;
	int 			rotation_centery;
	float 			rotation_alpha;
	int 			rotation_area;
	int				shaderinfoid;
} picresinfo;
typedef struct _clusterresinfo_
{
	int 						resloadmode;				// 0:config file  1:program create
	int							totalres;
	picresinfo					picres[MAXRESOURCENUM];
	int							brushnum;	
	brushresinfo				brushres[MAXBRUSHNUM];	
	struct g2d_buf 				*g2dbuf;					// only one video channel 
	int 						videoEnable;
	int 						sysinfoEnable;
	int 						sysinfoid;
	int 						sysfps;
} clusterresinfo;

#define screen2gl_x(x) 		(x)*(2.0/SCREEN_WIDTH)-1.0
#define screen2gl_y(y) 		-(y)*(2.0/SCREEN_HEIGHT)+1.0
void *xtdcore_clusterResInit(int mode, int sysinfoenable);
void xtdcore_clearRenderBuffer(void);

void *xtdcore_brushShaderInit(void *res);
void xtdcore_brushRenderInit(void *pdata);
void xtdcore_brushRender(void *pdata);

void *xtdcore_picShaderInit(void *res);
void xtdcore_picRenderInit(void *pdata);
void xtdcore_picRender(void *pdata);
#ifdef ENABLE_CUBESHADER
void *xtdcore_cubeShaderInit(void *res);
void xtdcore_cubeRenderInit(void *pdata);
void xtdcore_cubeRender(void *pdata);
#endif

#endif	//__XTDCORE_H__

