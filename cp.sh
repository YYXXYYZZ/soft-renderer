#/usr/bin

echo "copying files..."
cp $1.h ./include/core
cp $1.cpp ./src/core
rm $1.h $1.cpp
git add ./include/core/$1.h
git add ./src/core/$1.cpp

sed "/set(SRC$/a \ \ \ \ $\{INCROOT\}/$1.h\n\ \ \ \ $\{SRCROOT\}/$1.cpp" ./src/core/CMakeLists.txt  > temp
mv temp ./src/core/CMakeLists.txt

sed "/#include/c #include <core/$1.h>" ./src/core/$1.cpp > temp
mv temp ./src/core/$1.cpp

echo "done!"

