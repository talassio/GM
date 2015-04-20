# monitor 1.0
A pc monitoring interface for a Geiger-Müller particle detector.

The testbed is an old unbranded device on which it was adapted and 1/8 mic jack to interface with
a pc sound card's mic input.

![testbed](https://github.com/talassio/GM/raw/master/img/gmdevice.png)

## Compiling
Compilation is straight forward:
```bash
gcc -Wall -o monitor monitor.c -lasound
```
## Example 
```
cesma@andromeda:~/GM$ ./monitor 
monitor, version: 1.0
AM Sajo Castelli (c) 2015. Licensed under the GPL 2
This is free software with ABSOLUTELY NO WARRANTY.

Working parameters:
 Recording time se to 180 seconds
 Average window time set to 15 seconds
 Detector threshold set to -500
 Detector fram skip amount is 3 frames

Starting detection at Sun Apr 19 14:09:37 2015
Press Ctrl-C (^C) at any time to quit.
Elapsed time: 1.0    Counts          0    CPM        0.0 (estimated)      seccnt   0    delta          0
Elapsed time: 2.0    Counts          0    CPM        0.0 (estimated)      seccnt   1    delta          0
Elapsed time: 3.0    Counts          0    CPM        0.0 (estimated)      seccnt   2    delta          0
Elapsed time: 4.0    Counts          0    CPM        0.0 (estimated)      seccnt   3    delta          0
Elapsed time: 5.0    Counts          0    CPM        0.0 (estimated)      seccnt   4    delta          0
Elapsed time: 6.0    Counts          0    CPM        0.0 (estimated)      seccnt   5    delta          0
Elapsed time: 7.0    Counts          0    CPM        0.0 (estimated)      seccnt   6    delta          0
Elapsed time: 8.0    Counts          0    CPM        0.0 (estimated)      seccnt   7    delta          0
Elapsed time: 9.0    Counts          0    CPM        0.0 (estimated)      seccnt   8    delta          0
Elapsed time: 10.0    Counts          1    CPM        4.0 (estimated)      seccnt   9    delta          1
Elapsed time: 11.0    Counts          1    CPM        4.0 (estimated)      seccnt  10    delta          0
Elapsed time: 12.0    Counts          1    CPM        4.0 (estimated)      seccnt  11    delta          0
Elapsed time: 13.0    Counts          1    CPM        4.0 (estimated)      seccnt  12    delta          0
Elapsed time: 14.0    Counts          1    CPM        4.0 (estimated)      seccnt  13    delta          0
Elapsed time: 15.0    Counts          1    CPM        4.0 (estimated)      seccnt  14    delta          0
Elapsed time: 16.0    Counts          2    CPM        8.0 (estimated)      seccnt   0    delta          1
Elapsed time: 17.0    Counts          2    CPM        8.0 (estimated)      seccnt   1    delta          0
Elapsed time: 18.0    Counts          4    CPM       16.0 (estimated)      seccnt   2    delta          2
Elapsed time: 19.0    Counts          4    CPM       16.0 (estimated)      seccnt   3    delta          0
Elapsed time: 20.0    Counts          4    CPM       16.0 (estimated)      seccnt   4    delta          0
Elapsed time: 21.0    Counts          4    CPM       16.0 (estimated)      seccnt   5    delta          0
Elapsed time: 22.0    Counts          4    CPM       16.0 (estimated)      seccnt   6    delta          0
Elapsed time: 23.0    Counts          4    CPM       16.0 (estimated)      seccnt   7    delta          0
Elapsed time: 24.0    Counts          4    CPM       16.0 (estimated)      seccnt   8    delta          0
Elapsed time: 25.0    Counts          4    CPM       12.0 (estimated)      seccnt   9    delta          0
Elapsed time: 26.0    Counts          4    CPM       12.0 (estimated)      seccnt  10    delta          0
Elapsed time: 27.0    Counts          5    CPM       16.0 (estimated)      seccnt  11    delta          1
Elapsed time: 28.0    Counts          5    CPM       16.0 (estimated)      seccnt  12    delta          0
Elapsed time: 29.0    Counts          5    CPM       16.0 (estimated)      seccnt  13    delta          0
Elapsed time: 30.0    Counts          5    CPM       16.0 (estimated)      seccnt  14    delta          0
Elapsed time: 31.0    Counts          5    CPM       12.0 (estimated)      seccnt   0    delta          0
Elapsed time: 32.0    Counts          6    CPM       16.0 (estimated)      seccnt   1    delta          1
Elapsed time: 33.0    Counts          6    CPM        8.0 (estimated)      seccnt   2    delta          0
Elapsed time: 34.0    Counts          6    CPM        8.0 (estimated)      seccnt   3    delta          0
Elapsed time: 35.0    Counts          7    CPM       12.0 (estimated)      seccnt   4    delta          1
Elapsed time: 36.0    Counts          7    CPM       12.0 (estimated)      seccnt   5    delta          0
Elapsed time: 37.0    Counts          7    CPM       12.0 (estimated)      seccnt   6    delta          0
Elapsed time: 38.0    Counts          7    CPM       12.0 (estimated)      seccnt   7    delta          0
Elapsed time: 39.0    Counts          7    CPM       12.0 (estimated)      seccnt   8    delta          0
Elapsed time: 40.0    Counts          7    CPM       12.0 (estimated)      seccnt   9    delta          0
Elapsed time: 41.0    Counts          7    CPM       12.0 (estimated)      seccnt  10    delta          0
Elapsed time: 42.0    Counts          7    CPM        8.0 (estimated)      seccnt  11    delta          0
Elapsed time: 43.0    Counts          7    CPM        8.0 (estimated)      seccnt  12    delta          0
Elapsed time: 44.0    Counts          7    CPM        8.0 (estimated)      seccnt  13    delta          0
Elapsed time: 45.0    Counts          7    CPM        8.0 (estimated)      seccnt  14    delta          0
Elapsed time: 46.0    Counts          7    CPM        8.0 (estimated)      seccnt   0    delta          0
Elapsed time: 47.0    Counts          7    CPM        4.0 (estimated)      seccnt   1    delta          0
Elapsed time: 48.0    Counts          7    CPM        4.0 (estimated)      seccnt   2    delta          0
Elapsed time: 49.0    Counts          7    CPM        4.0 (estimated)      seccnt   3    delta          0
Elapsed time: 50.0    Counts          7    CPM        0.0 (estimated)      seccnt   4    delta          0
Elapsed time: 51.0    Counts          7    CPM        0.0 (estimated)      seccnt   5    delta          0
Elapsed time: 52.0    Counts          7    CPM        0.0 (estimated)      seccnt   6    delta          0
Elapsed time: 53.0    Counts          7    CPM        0.0 (estimated)      seccnt   7    delta          0
Elapsed time: 54.0    Counts          7    CPM        0.0 (estimated)      seccnt   8    delta          0
Elapsed time: 55.0    Counts          7    CPM        0.0 (estimated)      seccnt   9    delta          0
Elapsed time: 56.0    Counts          8    CPM        4.0 (estimated)      seccnt  10    delta          1
Elapsed time: 57.0    Counts          8    CPM        4.0 (estimated)      seccnt  11    delta          0
Elapsed time: 58.0    Counts          8    CPM        4.0 (estimated)      seccnt  12    delta          0
Elapsed time: 59.0    Counts          9    CPM        8.0 (estimated)      seccnt  13    delta          1
Elapsed time: 60.0    Counts          9    CPM        8.0 (estimated)      seccnt  14    delta          0
Elapsed time: 61.0    Counts         10    CPM       12.0 (estimated)      seccnt   0    delta          1
Elapsed time: 62.0    Counts         10    CPM       12.0 (estimated)      seccnt   1    delta          0
Elapsed time: 63.0    Counts         10    CPM       12.0 (estimated)      seccnt   2    delta          0
Elapsed time: 64.0    Counts         10    CPM       12.0 (estimated)      seccnt   3    delta          0
Elapsed time: 65.0    Counts         10    CPM       12.0 (estimated)      seccnt   4    delta          0
Elapsed time: 66.0    Counts         11    CPM       16.0 (estimated)      seccnt   5    delta          1
Elapsed time: 67.0    Counts         11    CPM       16.0 (estimated)      seccnt   6    delta          0
Elapsed time: 68.0    Counts         11    CPM       16.0 (estimated)      seccnt   7    delta          0
Elapsed time: 69.0    Counts         11    CPM       16.0 (estimated)      seccnt   8    delta          0
Elapsed time: 70.0    Counts         11    CPM       16.0 (estimated)      seccnt   9    delta          0
Elapsed time: 71.0    Counts         11    CPM       12.0 (estimated)      seccnt  10    delta          0
Elapsed time: 72.0    Counts         11    CPM       12.0 (estimated)      seccnt  11    delta          0
Elapsed time: 73.0    Counts         12    CPM       16.0 (estimated)      seccnt  12    delta          1
Elapsed time: 74.0    Counts         12    CPM       12.0 (estimated)      seccnt  13    delta          0
Elapsed time: 75.0    Counts         12    CPM       12.0 (estimated)      seccnt  14    delta          0
Elapsed time: 76.0    Counts         13    CPM       12.0 (estimated)      seccnt   0    delta          1
Elapsed time: 77.0    Counts         13    CPM       12.0 (estimated)      seccnt   1    delta          0
Elapsed time: 78.0    Counts         13    CPM       12.0 (estimated)      seccnt   2    delta          0
Elapsed time: 79.0    Counts         14    CPM       16.0 (estimated)      seccnt   3    delta          1
Elapsed time: 80.0    Counts         14    CPM       16.0 (estimated)      seccnt   4    delta          0
Elapsed time: 81.0    Counts         14    CPM       12.0 (estimated)      seccnt   5    delta          0
Elapsed time: 82.0    Counts         14    CPM       12.0 (estimated)      seccnt   6    delta          0
Elapsed time: 83.0    Counts         14    CPM       12.0 (estimated)      seccnt   7    delta          0
Elapsed time: 84.0    Counts         14    CPM       12.0 (estimated)      seccnt   8    delta          0
Elapsed time: 85.0    Counts         16    CPM       20.0 (estimated)      seccnt   9    delta          2
Elapsed time: 86.0    Counts         16    CPM       20.0 (estimated)      seccnt  10    delta          0
Elapsed time: 87.0    Counts         16    CPM       20.0 (estimated)      seccnt  11    delta          0
Elapsed time: 88.0    Counts         16    CPM       16.0 (estimated)      seccnt  12    delta          0
Elapsed time: 89.0    Counts         17    CPM       20.0 (estimated)      seccnt  13    delta          1
Elapsed time: 90.0    Counts         17    CPM       20.0 (estimated)      seccnt  14    delta          0
Elapsed time: 91.0    Counts         19    CPM       24.0 (estimated)      seccnt   0    delta          2
Elapsed time: 92.0    Counts         23    CPM       40.0 (estimated)      seccnt   1    delta          4
Elapsed time: 93.0    Counts         61    CPM      192.0 (estimated)      seccnt   2    delta         38
Elapsed time: 94.0    Counts        233    CPM      876.0 (estimated)      seccnt   3    delta        172
Elapsed time: 95.0    Counts        312    CPM     1192.0 (estimated)      seccnt   4    delta         79
Elapsed time: 96.0    Counts        378    CPM     1456.0 (estimated)      seccnt   5    delta         66
Elapsed time: 97.0    Counts        436    CPM     1688.0 (estimated)      seccnt   6    delta         58
Elapsed time: 98.0    Counts        474    CPM     1840.0 (estimated)      seccnt   7    delta         38
Elapsed time: 99.0    Counts        523    CPM     2036.0 (estimated)      seccnt   8    delta         49
Elapsed time: 100.0    Counts        525    CPM     2036.0 (estimated)      seccnt   9    delta          2
Elapsed time: 101.0    Counts        526    CPM     2040.0 (estimated)      seccnt  10    delta          1
Elapsed time: 102.0    Counts        526    CPM     2040.0 (estimated)      seccnt  11    delta          0
Elapsed time: 103.0    Counts        526    CPM     2040.0 (estimated)      seccnt  12    delta          0
Elapsed time: 104.0    Counts        528    CPM     2044.0 (estimated)      seccnt  13    delta          2
Elapsed time: 105.0    Counts        533    CPM     2064.0 (estimated)      seccnt  14    delta          5
Elapsed time: 106.0    Counts        553    CPM     2136.0 (estimated)      seccnt   0    delta         20
Elapsed time: 107.0    Counts        562    CPM     2156.0 (estimated)      seccnt   1    delta          9
Elapsed time: 108.0    Counts        562    CPM     2004.0 (estimated)      seccnt   2    delta          0
Elapsed time: 109.0    Counts        562    CPM     1316.0 (estimated)      seccnt   3    delta          0
Elapsed time: 110.0    Counts        562    CPM     1000.0 (estimated)      seccnt   4    delta          0
Elapsed time: 111.0    Counts        562    CPM      736.0 (estimated)      seccnt   5    delta          0
Elapsed time: 112.0    Counts        562    CPM      504.0 (estimated)      seccnt   6    delta          0
Elapsed time: 113.0    Counts        563    CPM      356.0 (estimated)      seccnt   7    delta          1
Elapsed time: 114.0    Counts        564    CPM      164.0 (estimated)      seccnt   8    delta          1
Elapsed time: 115.0    Counts        564    CPM      156.0 (estimated)      seccnt   9    delta          0
Elapsed time: 116.0    Counts        564    CPM      152.0 (estimated)      seccnt  10    delta          0
Elapsed time: 117.0    Counts        564    CPM      152.0 (estimated)      seccnt  11    delta          0
Elapsed time: 118.0    Counts        564    CPM      152.0 (estimated)      seccnt  12    delta          0
Elapsed time: 119.0    Counts        565    CPM      148.0 (estimated)      seccnt  13    delta          1
Elapsed time: 120.0    Counts        576    CPM      172.0 (estimated)      seccnt  14    delta         11
Elapsed time: 121.0    Counts        625    CPM      288.0 (estimated)      seccnt   0    delta         49
Elapsed time: 122.0    Counts        684    CPM      488.0 (estimated)      seccnt   1    delta         59
Elapsed time: 123.0    Counts        735    CPM      692.0 (estimated)      seccnt   2    delta         51
Elapsed time: 124.0    Counts        796    CPM      936.0 (estimated)      seccnt   3    delta         61
Elapsed time: 125.0    Counts        811    CPM      996.0 (estimated)      seccnt   4    delta         15
Elapsed time: 126.0    Counts        811    CPM      996.0 (estimated)      seccnt   5    delta          0
Elapsed time: 127.0    Counts        811    CPM      996.0 (estimated)      seccnt   6    delta          0
Elapsed time: 128.0    Counts        811    CPM      992.0 (estimated)      seccnt   7    delta          0
Elapsed time: 129.0    Counts        812    CPM      992.0 (estimated)      seccnt   8    delta          1
Elapsed time: 130.0    Counts        812    CPM      992.0 (estimated)      seccnt   9    delta          0
Elapsed time: 131.0    Counts        812    CPM      992.0 (estimated)      seccnt  10    delta          0
Elapsed time: 132.0    Counts        812    CPM      992.0 (estimated)      seccnt  11    delta          0
Elapsed time: 133.0    Counts        812    CPM      992.0 (estimated)      seccnt  12    delta          0
Elapsed time: 134.0    Counts        812    CPM      988.0 (estimated)      seccnt  13    delta          0
Elapsed time: 135.0    Counts        812    CPM      944.0 (estimated)      seccnt  14    delta          0
Elapsed time: 136.0    Counts        813    CPM      752.0 (estimated)      seccnt   0    delta          1
Elapsed time: 137.0    Counts        813    CPM      516.0 (estimated)      seccnt   1    delta          0
Elapsed time: 138.0    Counts        813    CPM      312.0 (estimated)      seccnt   2    delta          0
Elapsed time: 139.0    Counts        814    CPM       72.0 (estimated)      seccnt   3    delta          1
Elapsed time: 140.0    Counts        816    CPM       20.0 (estimated)      seccnt   4    delta          2
Elapsed time: 141.0    Counts        822    CPM       44.0 (estimated)      seccnt   5    delta          6
Elapsed time: 142.0    Counts        835    CPM       96.0 (estimated)      seccnt   6    delta         13
Elapsed time: 143.0    Counts        885    CPM      296.0 (estimated)      seccnt   7    delta         50
Elapsed time: 144.0    Counts       1034    CPM      888.0 (estimated)      seccnt   8    delta        149
Elapsed time: 145.0    Counts       1270    CPM     1832.0 (estimated)      seccnt   9    delta        236
Elapsed time: 146.0    Counts       2322    CPM     6040.0 (estimated)      seccnt  10    delta       1052
Elapsed time: 147.0    Counts       3955    CPM    12572.0 (estimated)      seccnt  11    delta       1633
Elapsed time: 148.0    Counts       4008    CPM    12784.0 (estimated)      seccnt  12    delta         53
Elapsed time: 149.0    Counts       4340    CPM    14112.0 (estimated)      seccnt  13    delta        332
Elapsed time: 150.0    Counts       5023    CPM    16844.0 (estimated)      seccnt  14    delta        683
Elapsed time: 151.0    Counts       5197    CPM    17536.0 (estimated)      seccnt   0    delta        174
Elapsed time: 152.0    Counts       5240    CPM    17708.0 (estimated)      seccnt   1    delta         43
Elapsed time: 153.0    Counts       5284    CPM    17884.0 (estimated)      seccnt   2    delta         44
Elapsed time: 154.0    Counts       5310    CPM    17984.0 (estimated)      seccnt   3    delta         26
Elapsed time: 155.0    Counts       5400    CPM    18336.0 (estimated)      seccnt   4    delta         90
Elapsed time: 156.0    Counts       6354    CPM    22128.0 (estimated)      seccnt   5    delta        954
Elapsed time: 157.0    Counts       8056    CPM    28884.0 (estimated)      seccnt   6    delta       1702
Elapsed time: 158.0    Counts       9641    CPM    35024.0 (estimated)      seccnt   7    delta       1585
Elapsed time: 159.0    Counts      12404    CPM    45480.0 (estimated)      seccnt   8    delta       2763
Elapsed time: 160.0    Counts      13974    CPM    50816.0 (estimated)      seccnt   9    delta       1570
Elapsed time: 161.0    Counts      16309    CPM    55948.0 (estimated)      seccnt  10    delta       2335
Elapsed time: 162.0    Counts      17489    CPM    54136.0 (estimated)      seccnt  11    delta       1180
Elapsed time: 163.0    Counts      20765    CPM    67028.0 (estimated)      seccnt  12    delta       3276
Elapsed time: 164.0    Counts      21427    CPM    68348.0 (estimated)      seccnt  13    delta        662
Elapsed time: 165.0    Counts      21428    CPM    65620.0 (estimated)      seccnt  14    delta          1
Elapsed time: 166.0    Counts      21428    CPM    64924.0 (estimated)      seccnt   0    delta          0
Elapsed time: 167.0    Counts      21428    CPM    64752.0 (estimated)      seccnt   1    delta          0
Elapsed time: 168.0    Counts      21428    CPM    64576.0 (estimated)      seccnt   2    delta          0
Elapsed time: 169.0    Counts      21428    CPM    64472.0 (estimated)      seccnt   3    delta          0
Elapsed time: 170.0    Counts      21428    CPM    64112.0 (estimated)      seccnt   4    delta          0
Elapsed time: 171.0    Counts      21428    CPM    60296.0 (estimated)      seccnt   5    delta          0
Elapsed time: 172.0    Counts      21428    CPM    53488.0 (estimated)      seccnt   6    delta          0
Elapsed time: 173.0    Counts      21429    CPM    47152.0 (estimated)      seccnt   7    delta          1
Elapsed time: 174.0    Counts      21429    CPM    36100.0 (estimated)      seccnt   8    delta          0
Elapsed time: 175.0    Counts      21429    CPM    29820.0 (estimated)      seccnt   9    delta          0
Elapsed time: 176.0    Counts      21429    CPM    20480.0 (estimated)      seccnt  10    delta          0
Elapsed time: 177.0    Counts      21429    CPM    15760.0 (estimated)      seccnt  11    delta          0
Elapsed time: 178.0    Counts      21429    CPM     2656.0 (estimated)      seccnt  12    delta          0
Elapsed time: 179.0    Counts      21429    CPM        8.0 (estimated)      seccnt  13    delta          0
Elapsed time: 180.0    Counts      21429    CPM        4.0 (estimated)      seccnt  14    delta          0
```
