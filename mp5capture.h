#ifndef __MP5CAPTURE_H__
#define __MP5CAPTURE_H__

#include "ipu.h"
#include "g2d.h"
#include <pthread.h>

struct capturebuffer
{
	unsigned char *start;
	size_t offset;
	unsigned int length;
};
typedef struct _mp5capinfo_
{
    int                 	capflag;						// capture flag
	int 					errflag;						// error flag
	int 					bufindex;						// inner buffer number
    struct capturebuffer 	*databuf;						// v4l2 data buffer
	int 					fd_ipu;
	struct ipu_task 		task1;
	struct g2d_buf 			*g2dbuf;						// user data buffer
    pthread_mutex_t     	mutex;	
    pthread_cond_t      	cond;
} mp5capinfo;

void *mp5capture_init(void);
int mp5capture_capdata(void *pdata);
void mp5capture_freebuf(void *pdata);
void mp5capture_deinit(void *pdata);

#endif	//__MP5CAPTURE_H__

