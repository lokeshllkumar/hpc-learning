set terminal pngcairo enhanced font 'Verdana,12'

set output 'ex_2_time_vs_N.png'
set title 'Time Taken by Method 1 and Method 2 vs N'
set xlabel 'N (Matrix Size)'
set ylabel 'Time taken (seconds)'
plot 'data2.dat' using 1:2 with linespoints title 'Method 1', \
     'data2.dat' using 1:3 with linespoints title 'Method 2'

set output 'ex_2_flops_vs_N.png'
set title 'FLOPs vs N'
set xlabel 'N (Matrix Size)'
set ylabel 'FLOPs'
plot 'data2.dat' using 1:4 with linespoints title 'FLOPs'