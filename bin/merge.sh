#!/bin/bash

mkdir -p data
mkdir -p data/result

rm *.rgb
mv *.jpg data/

python energia_video.py

mv *.png data/

cd data/

for i in {0..1999}
do
	echo $i
	#printf -v j "%05d" $i 
	convert final.vmd.$i.jpg graph$i.png +append result/joinres$i.png
done

cd result/

ffmpeg -framerate 24 -i joinres%d.png -vcodec libx264 output.mp4
