set terminal pngcairo enhanced font 'Arial,10'
set output 'spmv_plot_1_0.png'

set title "Execution Time vs. Number of Threads"
set xlabel "Number of Threads"
set ylabel "Time (seconds)"
set grid

set logscale y 10
set xrange [0:9]

plot "data_1_0.dat" using 1:2 with linespoints \
     title "Execution Time" lw 2 pt 7 lc rgb "blue"
