/* monitor.c -- Geiger-Müller particle detector monitor
 *
 * Copyright 2015 AM Sajo-Castelli.
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Base code from http://www.linuxjournal.com/article/6735?page=0,2
 * author Sep 30, 2004  By Jeff Tranter base on "Listing 4. Simple Sound Recording"
 *
 * Modified by AM Sajo-Castelli
 *
*/

/* Use the newer ALSA API */
#define ALSA_PCM_NEW_HW_PARAMS_API
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <alsa/asoundlib.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>
#include <error.h>
/* #include <string.h> */

#define NAME "monitor"
#define VERSION_MAJOR  1
#define VERSION_MINOR  0
#define DET_THRESHOLD  -500
#define DET_SKIPS      3
#define SAMPLE_RATE    44100
#define TIME_INCREMENT 0.05
#define FALSE          0
#define TRUE           1
#define SPAN           15        /* seconds */

unsigned long detect(char *, int);

int main() {
        long loops;
        long lc;
        int rc;
        int size;
        int rectime = 180;
        snd_pcm_t *handle;
        snd_pcm_hw_params_t *params;
        unsigned int val;
        int dir;
        snd_pcm_uframes_t frames;
        char *buffer;
        double atime = 0;
        double time_inc;
        time_t curtime;
        unsigned long cnt, tcnt;
        unsigned long delta, delta_sum;
        unsigned long CNT[SPAN] = { 0 };
        double sectime;
        unsigned int seccnt;

        printf("%s, version: %i.%i\n", NAME, VERSION_MAJOR, VERSION_MINOR);
        printf("AM Sajo Castelli (c) 2015. Licensed under the GPL +3\nThis is free software with ABSOLUTELY NO WARRANTY.\n");

        /* Open PCM device for recording (capture). */
        rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);
        if (rc < 0) {
                fprintf(stderr, "Error: %s: unable to open pcm device: %s.\n", NAME, snd_strerror(rc));
                exit(EXIT_FAILURE);
        }

        /* Allocate a hardware parameters object. */
        snd_pcm_hw_params_alloca(&params);

        /* Fill it in with default values. */
        snd_pcm_hw_params_any(handle, params);

        /* Set the desired hardware parameters. */

        /* Interleaved mode */
        snd_pcm_hw_params_set_access(handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);

        /* Signed 16-bit little-endian format */
        snd_pcm_hw_params_set_format(handle, params, SND_PCM_FORMAT_S16_LE);

        /* ONE channel (mono) */
        snd_pcm_hw_params_set_channels(handle, params, 1);

        /* 44100 bits/second sampling rate (CD quality) */
        val = SAMPLE_RATE;
        snd_pcm_hw_params_set_rate_near(handle, params, &val, &dir);

        /* Set period size to 2205 frames. */
        frames =  11025 / 5; /*32;*/
        snd_pcm_hw_params_set_period_size_near(handle, params, &frames, &dir);
        /* printf("frames=%li\n", frames); */
        /* Write the parameters to the driver */
        rc = snd_pcm_hw_params(handle, params);
        if (rc < 0) {
                fprintf(stderr, "Error %s: unable to set hw parameters: %s.\n", NAME, snd_strerror(rc));
                exit(EXIT_FAILURE);
        }

        /* Use a buffer large enough to hold one period */
        snd_pcm_hw_params_get_period_size(params, &frames, &dir);
        size = frames * 2; /* 2 bytes/sample, 1 channel */
        buffer = (char *) malloc(size);

        /* We want to loop for rectime seconds */
        snd_pcm_hw_params_get_period_time(params, &val, &dir);
        loops = rectime * SAMPLE_RATE / frames;
        /* printf("val=%i\t\t, loops=%li\n", val, loops); */
        time(&curtime);
        printf("Starting detection at %s", ctime(&curtime));
        printf("Press Ctrl-C (^C) at any time to quit.\n");
        sectime = 0;
        cnt = 0;
        tcnt = 0;
        seccnt = 0;
        delta_sum = 0;
        for (lc = 1; lc <= loops; lc++) {
                rc = snd_pcm_readi(handle, buffer, frames);
                time_inc = TIME_INCREMENT;
                if (rc == -EPIPE) {
                        /* EPIPE means overrun */
                        fprintf(stderr, "Warning: %s: overrun occurred.\n", NAME);
                        snd_pcm_prepare(handle);
                } else if (rc < 0) {
                        fprintf(stderr, "Warning %s: error from read: %s.\n", NAME, snd_strerror(rc));
                } else if (rc != (int)frames) {
                        fprintf(stderr, "Warning %s: short read, read %d frames.\n", NAME, rc);
                        time_inc = ((double)rc) / ((double)SAMPLE_RATE);
                }
                atime += time_inc;
                sectime += time_inc;
                delta = detect(buffer, rc);
                cnt += delta;
                tcnt += delta;
                delta_sum += delta;
                if ( sectime >= 1 ) {
                        sectime = 0;
                        if ( seccnt == SPAN ) { seccnt = 0; }
                        cnt -= CNT[seccnt];
                        CNT[seccnt] = delta_sum;
                        printf("Elapsed time: %3.1f    Counts %10lu    CPM %10.1f (estimated)      seccnt %3u    delta %10lu\n", atime, tcnt, ((double)cnt) * (60.0 / ((double)SPAN)), seccnt, delta_sum);
                        delta_sum = 0;
                        seccnt++;
                }
        }

        snd_pcm_drain(handle);
        snd_pcm_close(handle);
        free(buffer);

        return EXIT_SUCCESS;
}

unsigned long detect(char *buffer, int rc) {
        int k;
        int hit = FALSE;
        unsigned long cnt = 0;
        int skip;
        /*int pause;*/
        union con_c_to_s {
                char c[2];
                short s;
        };
        union con_c_to_s conv;
        for ( k = 0; k <= rc; k += 2 ) {
                conv.c[0] = buffer[k];
                conv.c[1] = buffer[k+1];
                /* printf("converted 2char to short: %i\n", conv.s);
                 * pause = getchar();
                 */
                if ( ( conv.s <= DET_THRESHOLD ) & ( hit == FALSE ) ) {
                                cnt = cnt + 1;
                                hit = TRUE;
                                skip = 0;
                                /* printf("found a HIT!!! ==> %lu\n", cnt); */
                } else {
                        if ( skip == DET_SKIPS ) {
                                hit = FALSE;
                        } else {
                                skip = skip + 1;
                        }
                }
        }
        return(cnt);
}
