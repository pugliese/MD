# movie.tcl
# To run, in the vmd tckon type: 'source movie.tcl'

# Script requires TopoTools and pbctools

package require topotools
package require pbctools

color change rgb  1 0.937 0.231 0.173 ;# red

#set molid [topo readlammpsdata in.lammpstrj]
mol new data.pdb
#mol addfile in.dcd

#set mol [molinfo top]
#set protons  [atomselect $mol {type 1}]
#set neutrons [atomselect $mol {type 2}]
#$protons  colorID 1
#$neutrons colorID 2

# Set the representation, delete the initial representation
# created by vmd

mol delrep 0 top
mol representation VDW 0.10
#mol selection {type 1}
#mol color ColorID 1
#mol ~selection {Type 1}
#mol  selection {Type 2}
#mol ~selection {Type 2}
#mol color Type 1 red
#mol color Type 2 white
#mol material Edgy
#mol addrep top
#mol selection {type 2}
#mol color ColorID 8
#mol material Edgy
mol addrep top

display height 12
#rotate y by -30
#trans y by 0 0 -5 # not working!

# change background color
color Display Background white
color Display FPS black
color Axes Labels black

# Draw the periodic box centered at the origin
#pbc box_draw -center origin -color black
pbc box_draw -color black
#pbc box_molecule -color black
#pbc box

# Get the number of frames
#set nframes [molinfo $molid get numframes]


# Loop over frames, calling render.
# Format the output filename as snap-03.00001.tga
# Skip the first "junk" frame from lammpsdata

#for {set i 1} {$i < $nframes} {incr i} {
#      render TachyonInternal\
#        [format “snap-03.%05d.tga" $i]
#}

## Call external script to encode movie
#exec ./03-encode-vmd.sh
#exec ffmpeg -i snap-03.%05d.tga movie.mp4
#exec rm snap-03.*.tga

# Set the scene: adjust display height
# and rotate axes a bit, set the background
# to white

#display height 5
## rotate x by -45; rotate y by 45; rotate z by 45
#rotate z by -90; rotate x by -45
#translate to 0 0.5 0

## set some variables
#global VMDDIR
#set VMDDIR $env(VMDDIR)

##load user scripts (by ajasja)
#source $env(VMDDIR)/scripts/user/init.tcl

# position and turn on menus

##main
#menu main on
#menu main move 24 50
##graphics
#menu graphics on
#menu graphics move 843 70
##tkcon
#menu tkcon off
#menu tkcon on
#menu tkcon move 1869 -67

#box_molecule top

# miny=9
# maxy=11

# set sel [atomselect top all]
# draw color yellow
# draw line "20 $miny  0" "20 $maxy 0.5"

#pbc box_draw -center origin

#set nframes [molinfo $molid get numframes]
#set nframes 100

#for {set i 1} {$i < $nframes} {incr i} {
#render TachyonInternal\
#[format “snap-03.%05d.tga" $i]
#}
#exec ffmpeg -i snap-03.%05d.tga movie.mp4
#exec rm snap-03.*.tga


