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
#include <getopt.h>
#include <math.h>

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

unsigned long detect(char *, int, short, int);

int main(int argc, char *argv[]) {
        long loops;
        long lc;
        int rc;
        int c;
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
        int span = SPAN;
        time_t curtime;
        unsigned long cnt, tcnt;
        unsigned long delta, delta_sum;
        unsigned long *CNT; /* [SPAN] = { 0 }; */
        double sectime;
        unsigned int seccnt;
        short det_threshold = DET_THRESHOLD;
        int det_skips = DET_SKIPS;
        printf("%s, version: %i.%i\n", NAME, VERSION_MAJOR, VERSION_MINOR);
        printf("AM Sajo Castelli (c) 2015. Licensed under the GPL 2\nThis is free software with ABSOLUTELY NO WARRANTY.\n\n");

        static struct option long_options[] =
        {
          /* These options set a flag. */
          {"time",            required_argument,   0, 't'}, /* default: 180 sec */
          {"average-time",    required_argument,   0, 'A'}, /* default: 15 sec */
          {"threshold",       required_argument,   0, 'T'}, /* default: -500, range 0, -32767 */
          {"skips",           required_argument,   0, 'S'}, /* default: 3 frames */
          {"help",            no_argument,         0, 'h'},
          {0, 0, 0, 0}
        };

        while (1) {
                int option_index = 0;

                c = getopt_long (argc, argv, "t:A:T:S:h", long_options, &option_index);
                if (c == -1) break;

                switch (c) {
                        case 'h':
                                printf("help and usage:\n"
                                "--time <sec>, -t <sec>          sets the recording time in seconds, default 180s\n"
                                "--average-time <sec>, -A <sec>  sets the time window in seconds on which to average the counts, default 15s\n"
                                "--threshold <int>, -T <int>     changes the discriminization level, range (-1 to -32767), default -500\n"
                                "--skips <int>, -S <int>         number of frams to skip after detecting a particle, defaults to 3 frames\n");
                                exit(EXIT_SUCCESS);
                        case 't':
                                rectime = atoi(optarg);
                                if ( rectime <= 0 ) {
                                        fprintf(stderr, "Error: recording time must be positive integer in seconds.\n");
                                        exit(EXIT_FAILURE);
                                }
                                break;
                        case 'T':
                                det_threshold = (short)atoi(optarg);
                                if ( det_threshold >= 0 ) {
                                        fprintf(stderr, "Error: detector threshold must be negative integer between -1 and -32767.\n");
                                        exit(EXIT_FAILURE);
                                }
                                break;

                        case 'A':
                                span = atof(optarg);
                                if ( span <= 0 ) {
                                        fprintf(stderr, "Error: average span window must be positive integer number greater than one.\n");
                                        exit(EXIT_FAILURE);
                                }
                                break;
                        case 'S':
                                det_skips = (int)atoi(optarg);
                                if ( det_skips <= 0 ) {
                                        fprintf(stderr, "Error: number of frames to skip must be a positive integer.\n");
                                        exit(EXIT_FAILURE);
                                }
                                break;
                        case '?':
                                fprintf(stderr, "Try %s --help\n", argv[0]);
                                exit(EXIT_FAILURE);
                        default:
                                fprintf(stderr, "Error: unknown option \"%s\".\n", optarg);
                                exit(EXIT_FAILURE);
                }
        }

        CNT = (unsigned long *) calloc(sizeof(cnt), span);
        if (CNT < 0) {
                fprintf(stderr, "Error: unable to allocate %i block of memory.\n", span);
                exit(EXIT_FAILURE);
        }

        /* Open PCM device for recording (capture). */
        rc = snd_pcm_open(&handle, "default", SND_PCM_STREAM_CAPTURE, 0);
        if (rc < 0) {
                fprintf(stderr, "Error: %s: unable to open pcm device: %s.\n", NAME, snd_strerror(rc));
                exit(EXIT_FAILURE);
        }

        printf("Working parameters:\n Recording time se to %i seconds\n"
        " Average window time set to %i seconds\n"
        " Detector threshold set to %i\n"
        " Detector fram skip amount is %i frames\n\n", rectime, span, det_threshold, det_skips);

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
                delta = detect(buffer, rc, det_threshold, det_skips);
                cnt += delta;
                tcnt += delta;
                delta_sum += delta;
                if ( sectime >= 1 ) {
                        sectime = 0;
                        if ( seccnt == span ) { seccnt = 0; }
                        cnt -= CNT[seccnt];
                        CNT[seccnt] = delta_sum;
                        printf("Elapsed time: %3.1f    Counts %10lu    CPM %10.1f (estimated)      seccnt %3u    delta %10lu\n", atime, tcnt, ((double)cnt) * (60.0 / (double)(span)), seccnt, delta_sum);
                        delta_sum = 0;
                        seccnt++;
                }
        }

        snd_pcm_drain(handle);
        snd_pcm_close(handle);
        free(buffer);

        return EXIT_SUCCESS;
}

unsigned long detect(char *buffer, int rc, short det_threshold, int det_skips) {
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
                if ( ( conv.s <= det_threshold ) & ( hit == FALSE ) ) {
                                cnt = cnt + 1;
                                hit = TRUE;
                                skip = 0;
                                /* printf("found a HIT!!! ==> %lu\n", cnt); */
                } else {
                        if ( skip == det_skips ) {
                                hit = FALSE;
                        } else {
                                skip = skip + 1;
                        }
                }
        }
        return(cnt);
}
