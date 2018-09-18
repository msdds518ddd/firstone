/******************************************************************************
 *
 *               (c) Copyright 2018, Chengdu Excite. 
 *                       All Rights Reserved.
 * 
 * Copying of this document or code and giving it to others and the 
 * use or communication of the contents thereof, are forbidden without
 * expressed authority. Offenders are liable to the payment of damages.
 *
 * Issued by Chengdu Excite Information Technology Co.,Ltd.
 *
 ******************************************************************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <signal.h>
#include <math.h>
#include <string.h>
#include <malloc.h>
#include <pthread.h>
#include <assert.h>
#include <sys/time.h>
#include "globaldef.h"
#include "xtdcore.h"
#include "mp5capture.h"

clusterresinfo *g_clusterres = NULL;
void *g_picshader = NULL;
void *g_brushshader = NULL;
void *g_cubeShader = NULL;
int g_movepic = 0;
int g_savepic = 0;
int g_resloadmode = 0;
int g_showaxis = 0;
int g_sysinfo = 0;
int g_test = 1;

int userRandom(void)
{
	static int g_userRandom = 0;
	if (!g_userRandom) {
		g_userRandom = 1;
		srand(50);
	}
	return rand()%4;
}
int userTimer(int timelength)
{
	static timeval time_start, time_current;
	static int time_flag = 0;
	int totaltime;
	if (!time_flag) {
		time_flag = 1;
		gettimeofday(&time_start, 0);
		return -1;
	}

	gettimeofday(&time_current, 0);
	totaltime = (time_current.tv_sec - time_start.tv_sec) * 1000000L;
	totaltime += time_current.tv_usec - time_start.tv_usec;
	if (totaltime > timelength) {
		gettimeofday(&time_start, 0);	
		return 0;
	} 
	return -1;
}


int needle_left_rotation_flag = 0;
int classic_needle_left()
{
#if 0
	g_clusterres->picres[5].update = RESUPDATE_POSITION;
	if (g_clusterres->picres[5].rotation >= 360.0)
		g_clusterres->picres[5].rotation = 0.0;
	else
		g_clusterres->picres[5].rotation += 1.0;
#endif
#if 0
	g_clusterres->picres[5].update = RESUPDATE_POSITION;
	if (needle_left_rotation_flag == 0) {
		if (g_clusterres->picres[5].rotation <= 271.0) {
			needle_left_rotation_flag = 1;
		}	
		else 
			g_clusterres->picres[5].rotation -= 0.983333;		
	}	
	else if (needle_left_rotation_flag == 1) {
		if (g_clusterres->picres[5].rotation >= 509.0) 
			needle_left_rotation_flag = 0;
		else 
			g_clusterres->picres[5].rotation += 0.983333;		
	}
	else {
		printf("rotation out of range! Please set rotation around -509~271");
		return 0;
	}
#endif
#if 1
	g_clusterres->picres[5].update = RESUPDATE_POSITION;
	if (g_clusterres->picres[2].rotation <= 0) {
			g_clusterres->picres[5].rotation = 450 + g_clusterres->picres[2].rotation;		
	}
	else if (g_clusterres->picres[2].rotation > 0)
		g_clusterres->picres[5].rotation = 450 + g_clusterres->picres[2].rotation;	
	else {
		printf("rotation out of range! Please set rotation around 510~270");
		return 0;
	}
#endif
	return 0;
}

int classic_needle_right()
{
	g_clusterres->picres[14].update = RESUPDATE_POSITION;
	if (g_clusterres->picres[6].rotation <= 0) {
			g_clusterres->picres[14].rotation = 540 + g_clusterres->picres[6].rotation;		
	}
	else {
		printf("rotation out of range! Please set rotation around 480~237");
		return 0;
	}
	return 0;
}

int ecogage_efc_flage = 0;
int dial_ecogage_efc()
{
#if 0
	g_clusterres->picres[2].update = RESUPDATE_POSITION;
	if (g_clusterres->picres[2].rotation >= 360)
		g_clusterres->picres[2].rotation = 0.0;
	else
		g_clusterres->picres[2].rotation += 1.0;
#endif
#if 1
	g_clusterres->picres[2].update = RESUPDATE_POSITION;
	if (ecogage_efc_flage == 0) {
		if (g_clusterres->picres[2].rotation <= -180.0) 
			ecogage_efc_flage = 1;
		else 
			g_clusterres->picres[2].rotation -= 2.0;		
	}	
	else if (ecogage_efc_flage == 1) {
		if (g_clusterres->picres[2].rotation >= 58.0) 
			ecogage_efc_flage = 0;
		else 
			g_clusterres->picres[2].rotation += 2.0;		
	}
	else {
		printf("rotation out of range! Please set rotation around -179~59");
		return 0;
	}
#endif

	return 0;
}

int gage_efc_flage = 0;
int dial_gage_efc()
{
#if 1
	g_clusterres->picres[6].update = RESUPDATE_POSITION;
	if (gage_efc_flage == 0) {
		if (g_clusterres->picres[6].rotation <= -303.0) 
			gage_efc_flage = 1;
		else 
			g_clusterres->picres[6].rotation -= 1.0;		
	}	
	else if (gage_efc_flage == 1) {
		if (g_clusterres->picres[6].rotation >= -60.0) 
			gage_efc_flage = 0;
		else 
			g_clusterres->picres[6].rotation += 1.0;		
	}
	else {
		printf("rotation out of range! Please set rotation around -303~-60");
		return 0;
	}
#endif	
	return 0;
}

int classic_temp_f_flage = 0;
int classic_temp_f()
{
#if 1
	g_clusterres->picres[4].update = RESUPDATE_POSITION;
	if (classic_temp_f_flage == 0) {
		if (g_clusterres->picres[4].rotation >= 57.0){			 
			classic_temp_f_flage = 1;
//			sleep(1);
		}
		else {
			g_clusterres->picres[4].rotation += 0.5;
#if 0
			if (g_clusterres->picres[4].rotation == 9.5)
				sleep(1);
			else if (g_clusterres->picres[4].rotation == 16.5)
				sleep(1);
			else if (g_clusterres->picres[4].rotation == 23.5)
				sleep(1);
			else if (g_clusterres->picres[4].rotation == 30.5)
				sleep(1);	
			else if (g_clusterres->picres[4].rotation == 37.5)
				sleep(1);	
			else if (g_clusterres->picres[4].rotation == 44.5)
				sleep(1);	
			else if (g_clusterres->picres[4].rotation == 51.5)
				sleep(1);
#endif
		}		
	}	
	else if (classic_temp_f_flage == 1) {
		if (g_clusterres->picres[4].rotation <= 1.0) 
			classic_temp_f_flage = 0;
		else 
			g_clusterres->picres[4].rotation -= 0.5;		
	}
	else {
		printf("rotation out of range! Please set rotation around 1~-57");
		return 0;
	}
#endif
	return 0;
}

int classic_fuel_f_flage = 0;
int classic_fuel_f()
{
#if 1
	g_clusterres->picres[4].update = RESUPDATE_POSITION;
	if (classic_fuel_f_flage == 0) {
		if (g_clusterres->picres[4].rotation >= 57.0){			 
			classic_fuel_f_flage = 1;
			sleep(1);
		}
		else {
			g_clusterres->picres[4].rotation += 0.5;
			if (g_clusterres->picres[4].rotation == 9.5)
				sleep(1);
			else if (g_clusterres->picres[4].rotation == 16.5)
				sleep(1);
			else if (g_clusterres->picres[4].rotation == 23.5)
				sleep(1);
			else if (g_clusterres->picres[4].rotation == 30.5)
				sleep(1);	
			else if (g_clusterres->picres[4].rotation == 37.5)
				sleep(1);	
			else if (g_clusterres->picres[4].rotation == 44.5)
				sleep(1);	
			else if (g_clusterres->picres[4].rotation == 51.5)
				sleep(1);
		}		
	}	
	else if (classic_fuel_f_flage == 1) {
		if (g_clusterres->picres[4].rotation <= 1.0) 
			classic_fuel_f_flage = 0;
		else 
			g_clusterres->picres[4].rotation -= 0.5;		
	}
	else {
		printf("rotation out of range! Please set rotation around 1~-57");
		return 0;
	}
#endif
	return 0;
}
#if 1
void updateResource(void)
{
#if 0
	if (usertimer(100000) == 0) {
#else
	if (1) {
#endif
		// bitmap
		classic_needle_left();
//		usleep(30000);

		classic_needle_right();
//		usleep(30000);

		// dial
		dial_ecogage_efc();
		dial_gage_efc();
		usleep(60000);

		classic_temp_f();
//		classic_fuel_f();
//		sleep(1);

		// string 

		// progressbar

		// progressbar

	}
}
#endif
#if 0
void updateResource(void)
{
#if 0
	if (usertimer(100000) == 0) {
#else
	if (1) {
#endif
		// bitmap
		g_clusterres->picres[2].update = RESUPDATE_POSITION;	
		if (g_clusterres->picres[2].rotation >= 360.0)
			g_clusterres->picres[2].rotation = 0.0;
		else
			g_clusterres->picres[2].rotation += 1.0;
		// dial
		g_clusterres->picres[1].update = RESUPDATE_POSITION;	
		if (g_clusterres->picres[1].rotation >= 360.0)
			g_clusterres->picres[1].rotation = 0.0;
		else
			g_clusterres->picres[1].rotation += 1.0;

		// string 
		static int g_stringcnt = 0;
		g_stringcnt++;
		if (g_stringcnt == 40) {
			g_stringcnt = 0;

			g_clusterres->picres[3].update = RESUPDATE_POSITION;	
			int ret = userRandom();
			int val = 20;
			if (ret == 0 && g_clusterres->picres[3].position_x <= SCREEN_WIDTH-val)
				g_clusterres->picres[3].position_x += val;
			if (ret == 1 && g_clusterres->picres[3].position_x >= val)
				g_clusterres->picres[3].position_x -= val;	
			if (ret == 0 && g_clusterres->picres[3].position_y <= SCREEN_HEIGHT-val)
				g_clusterres->picres[3].position_y += val;
			if (ret == 1 && g_clusterres->picres[3].position_y >= val)
				g_clusterres->picres[3].position_y -= val;
		}		

		// progressbar
		g_clusterres->picres[4].update = RESUPDATE_POSITION;	
		if (g_clusterres->picres[4].rotation >= 180.0)
			g_clusterres->picres[4].rotation = 0.0;
		else
			g_clusterres->picres[4].rotation += 1.0;
		// progressbar
		g_clusterres->picres[5].update = RESUPDATE_POSITION;	
		if (g_clusterres->picres[5].rotation <= 0.0)
			g_clusterres->picres[5].rotation = 180.0;
		else
			g_clusterres->picres[5].rotation -= 1.0;
	}
}
#endif
void userFunction(void)
{
	if (g_savepic) {
		g_savepic = 0;
		xtdcore_saveJpgTextures(SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	if (g_test)
		updateResource();
}




int process_cmdline(int argc, char **argv)
{
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-m") == 0) {
			g_movepic = atoi(argv[++i]);
		} else if (strcmp(argv[i], "-s") == 0) {
			g_savepic = 1;
		} else if (strcmp(argv[i], "-d") == 0) {
			g_resloadmode = 1;
		} else if (strcmp(argv[i], "-a") == 0) {
			g_showaxis = 1;
		} else if (strcmp(argv[i], "-i") == 0) {
			g_sysinfo = 1;
		} else if (strcmp(argv[i], "-t") == 0) {
			g_test = 1;
		} else if (strcmp(argv[i], "-h") == 0) {
			printf("function descriptions:\n" 								\
			   	" -s <Save screen to jpg file>\n"							\
			   	" -d <use Default mode load cluster resource>\n"			\
			   	" -a <show Axis>\n"											\
			   	" -i <show system Infomation>\n"							\
			   	" -t <enable test function>\n"								\
               	" -h <help>\n");
			return -1;
		}
	}

	return 0;
}

int main(int argc, char **argv)
{
	if (process_cmdline(argc, argv) < 0) {
		return -1;
	}

	xtdcore_systemInit();

	// cluster resource init
 	g_clusterres = (clusterresinfo *)xtdcore_clusterResInit(g_resloadmode, g_sysinfo);
	if (g_clusterres == NULL) {
		printf("xtd_clusterResInit error!\n");
		return -1;
	}

	// picshader init
	g_picshader = xtdcore_picShaderInit(g_clusterres);
	if (g_picshader == NULL) {
		printf("xtd_picShaderInit error!\n");
		return -1;
	}
	xtdcore_picRenderInit(g_picshader);

	// brushshader init
	g_brushshader = xtdcore_brushShaderInit(g_clusterres);
	if (g_brushshader == NULL) {
		printf("xtd_brushShaderInit error!\n");
		return -1;
	}
	xtdcore_brushRenderInit(g_brushshader);

#ifdef ENABLE_CUBESHADER
if (g_test) {
	// cubeshader init
	g_cubeShader = xtdcore_cubeShaderInit(g_clusterres);
	if (g_cubeShader == NULL) {
		printf("xtd_cubeShaderInit error!\n");
		return -1;
	}
	xtdcore_cubeRenderInit(g_cubeShader);
}
#endif

	// init video capture (for running in no video device! Enable video after resolve resource!!)
	void *g_mp5cap = NULL;
	if (g_clusterres->videoEnable) {
    	g_mp5cap = mp5capture_init();
    	if (g_mp5cap == NULL) {
       	 printf("videocapture_init error!\n");
        	return -1;
    	}
		mp5capinfo *mp5cap = (mp5capinfo*)g_mp5cap;
		g_clusterres->g2dbuf = mp5cap->g2dbuf;
	}	

	while (1) {
		if (g_clusterres->videoEnable)
			mp5capture_capdata(g_mp5cap);
		xtdcore_clearRenderBuffer();
		xtdcore_picRender(g_picshader);
		if (g_showaxis)
			xtdcore_brushRender(g_brushshader);

#ifdef ENABLE_CUBESHADER
if (g_test) {
		xtdcore_cubeRender(g_cubeShader);
}
#endif		

		if (g_clusterres->videoEnable)
			mp5capture_freebuf(g_mp5cap);
		userFunction();

		xtdcore_systemUpdate();
	}

	return 0;
}
