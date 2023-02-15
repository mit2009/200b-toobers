
while [ true ] ; do
read -n 1 -p "Press any key to copy files to /Volumes/Untitled/1: "
echo "\n"
mkdir /Volumes/Untitled/1
for i in {1..9}
do
   cp ../mp3/000$i.mp3 /Volumes/Untitled/1 &&
   echo "Copied 000$i.mp3" 
done
for i in {10..37}
do
   cp ../mp3/00$i.mp3 /Volumes/Untitled/1 &&
   echo "Copied 00$i.mp3"
done
dot_clean /Volumes/Untitled/1
echo "done!\n"
done