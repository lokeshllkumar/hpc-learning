set terminal pngcairo enhanced font 'Verdana,12'

set output 'test.png'
set title 'Test Graph'
set xlabel 'Serial'
set ylabel 'Time'

set grid
set key right top

set style line 1 lt 1 lw 2 pt 7 ps 1.5 lc rgb "blue"
set style line 2 lt 1 lw 2 pt 7 ps 1.5 lc rgb "red"

set xrange [0:5]
set yrange [0:10]

plot 'data1.dat' using 1:2 with linespoints title 'Time', \
'data1.dat' using 1:3 with linespoints title 'Dummy' 