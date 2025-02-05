set terminal push
set term png
set term png size 1920, 1080

set output "plot_xyz.png"

set title "change of ion currents with time"


set xlabel "current z" 
set ylabel "current y"
set zlabel "time t"



splot "Test" using 4:3:1 with lines 


set term pop  