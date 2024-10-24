set terminal pngcairo enhanced font 'Verdana,10'
set output 'ex_1_vs_2_plot.png'

set title "Matrix Multiplication Duration Comparison"
set xlabel "Iteration"
set ylabel "Duration"

set grid

set key outside

set style line 1 lt 1 lw 2 pt 7 ps 1.5 lc rgb "blue"
set style line 2 lt 1 lw 2 pt 7 ps 1.5 lc rgb "red"

plot 'data_1_0.dat' using 1:3 with linespoints linestyle 1 title 'Without parallelization', \
'data_2_0.dat' using 1:3 with linespoints linestyle 2 title 'With parallelization'

