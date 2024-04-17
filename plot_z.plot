set term png
set term png size 640, 480
set output "plot_z_t.png"

set title "Voltage"


set xlabel "time(seconds)"
set ylabel "current z(ampere)"



plot "Test" using 1:4 with lines


pause -1