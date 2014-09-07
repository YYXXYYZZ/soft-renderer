#/usr/bin

echo "copying files..."
cp $1.h ./include/core
cp $1.cpp ./src/core
rm $1.h $1.cpp
echo "done!"

