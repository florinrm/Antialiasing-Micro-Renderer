#!/usr/bin/env bash

#color
./homework in/lenna_color.pnm out/2_1_lenna_color.pnm 2 1 > /dev/null
./homework in/lenna_color.pnm out/2_2_lenna_color.pnm 2 2 > /dev/null
./homework in/lenna_color.pnm out/2_4_lenna_color.pnm 2 4 > /dev/null
./homework in/lenna_color.pnm out/2_8_lenna_color.pnm 2 8 > /dev/null
./homework in/lenna_color.pnm out/3_1_lenna_color.pnm 3 1 > /dev/null
./homework in/lenna_color.pnm out/3_2_lenna_color.pnm 3 2 > /dev/null
./homework in/lenna_color.pnm out/3_4_lenna_color.pnm 3 4 > /dev/null
./homework in/lenna_color.pnm out/3_8_lenna_color.pnm 3 8 > /dev/null
#./homework in/lenna_color.pnm out/4_1_lenna_color.pnm 4 1 > /dev/null
#./homework in/lenna_color.pnm out/4_2_lenna_color.pnm 4 2 > /dev/null
#./homework in/lenna_color.pnm out/4_4_lenna_color.pnm 4 4 > /dev/null
#./homework in/lenna_color.pnm out/4_8_lenna_color.pnm 4 8 > /dev/null
./homework in/lenna_color.pnm out/8_1_lenna_color.pnm 8 1 > /dev/null
./homework in/lenna_color.pnm out/8_2_lenna_color.pnm 8 2 > /dev/null
./homework in/lenna_color.pnm out/8_4_lenna_color.pnm 8 4 > /dev/null
./homework in/lenna_color.pnm out/8_8_lenna_color.pnm 8 8 > /dev/null

#grayscale
./homework in/lenna_bw.pgm out/2_1_lenna_bw.pgm 2 1 > /dev/null
./homework in/lenna_bw.pgm out/2_2_lenna_bw.pgm 2 2 > /dev/null
./homework in/lenna_bw.pgm out/2_4_lenna_bw.pgm 2 4 > /dev/null
./homework in/lenna_bw.pgm out/2_8_lenna_bw.pgm 2 8 > /dev/null
./homework in/lenna_bw.pgm out/3_1_lenna_bw.pgm 3 1 > /dev/null
./homework in/lenna_bw.pgm out/3_2_lenna_bw.pgm 3 2 > /dev/null
./homework in/lenna_bw.pgm out/3_4_lenna_bw.pgm 3 4 > /dev/null
./homework in/lenna_bw.pgm out/3_8_lenna_bw.pgm 3 8 > /dev/null
#./homework in/lenna_bw.pgm out/4_1_lenna_bw.pgm 4 1 > /dev/null
#./homework in/lenna_bw.pgm out/4_2_lenna_bw.pgm 4 2 > /dev/null
#./homework in/lenna_bw.pgm out/4_4_lenna_bw.pgm 4 4 > /dev/null
#./homework in/lenna_bw.pgm out/4_8_lenna_bw.pgm 4 8 > /dev/null
./homework in/lenna_bw.pgm out/8_1_lenna_bw.pgm 8 1 > /dev/null
./homework in/lenna_bw.pgm out/8_2_lenna_bw.pgm 8 2 > /dev/null
./homework in/lenna_bw.pgm out/8_4_lenna_bw.pgm 8 4 > /dev/null
./homework in/lenna_bw.pgm out/8_8_lenna_bw.pgm 8 8 > /dev/null

#checking
diff out_ref/2lenna_bw.pgm out/2_1_lenna_bw.pgm | wc -l && echo "2_1_lenna_bw.pgm"
diff out_ref/2lenna_bw.pgm out/2_2_lenna_bw.pgm | wc -l && echo "2_2_lenna_bw.pgm"
diff out_ref/2lenna_bw.pgm out/2_4_lenna_bw.pgm | wc -l && echo "2_4_lenna_bw.pgm"
diff out_ref/2lenna_bw.pgm out/2_8_lenna_bw.pgm | wc -l && echo "2_8_lenna_bw.pgm"
diff out_ref/3lenna_bw.pgm out/3_1_lenna_bw.pgm | wc -l && echo "3_1_lenna_bw.pgm"
diff out_ref/3lenna_bw.pgm out/3_2_lenna_bw.pgm | wc -l && echo "3_2_lenna_bw.pgm"
diff out_ref/3lenna_bw.pgm out/3_4_lenna_bw.pgm | wc -l && echo "3_4_lenna_bw.pgm"
diff out_ref/3lenna_bw.pgm out/3_8_lenna_bw.pgm | wc -l && echo "3_8_lenna_bw.pgm"
diff out_ref/8lenna_bw.pgm out/8_1_lenna_bw.pgm | wc -l && echo "8_1_lenna_bw.pgm"
diff out_ref/8lenna_bw.pgm out/8_2_lenna_bw.pgm | wc -l && echo "8_2_lenna_bw.pgm"
diff out_ref/8lenna_bw.pgm out/8_4_lenna_bw.pgm | wc -l && echo "8_4_lenna_bw.pgm"
diff out_ref/8lenna_bw.pgm out/8_8_lenna_bw.pgm | wc -l && echo "8_8_lenna_bw.pgm"

diff out_ref/2lenna_color.pnm out/2_1_lenna_color.pnm | wc -l && echo "2_1_lenna_color.pnm"
diff out_ref/2lenna_color.pnm out/2_2_lenna_color.pnm | wc -l && echo "2_2_lenna_color.pnm"
diff out_ref/2lenna_color.pnm out/2_4_lenna_color.pnm | wc -l && echo "2_4_lenna_color.pnm"
diff out_ref/2lenna_color.pnm out/2_8_lenna_color.pnm | wc -l && echo "2_8_lenna_color.pnm"
diff out_ref/3lenna_color.pnm out/3_1_lenna_color.pnm | wc -l && echo "3_1_lenna_color.pnm"
diff out_ref/3lenna_color.pnm out/3_2_lenna_color.pnm | wc -l && echo "3_2_lenna_color.pnm"
diff out_ref/3lenna_color.pnm out/3_4_lenna_color.pnm | wc -l && echo "3_4_lenna_color.pnm"
diff out_ref/3lenna_color.pnm out/3_8_lenna_color.pnm | wc -l && echo "3_8_lenna_color.pnm"
diff out_ref/8lenna_color.pnm out/8_1_lenna_color.pnm | wc -l && echo "8_1_lenna_color.pnm"
diff out_ref/8lenna_color.pnm out/8_2_lenna_color.pnm | wc -l && echo "8_2_lenna_color.pnm"
diff out_ref/8lenna_color.pnm out/8_4_lenna_color.pnm | wc -l && echo "8_4_lenna_color.pnm"
diff out_ref/8lenna_color.pnm out/8_8_lenna_color.pnm | wc -l && echo "8_8_lenna_color.pnm"