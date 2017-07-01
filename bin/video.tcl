# Get the number of frames
set molid top
set nframes [molinfo $molid get numframes]
set step 10
set n [expr $nframes/10]

animate goto start

set frame 0
for {set i 0} {$i < $n} {incr i} {

			set frame [expr $step*$i]
			animate goto $frame
			render snapshot final.vmd.[format "%d" $i].rgb
			exec convert final.vmd.$i.rgb final.vmd.$i.jpg


}

exec bash merge.sh
