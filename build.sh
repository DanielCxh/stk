
ProjectName="stk.exe"

echo " === compile start"

source_files=`find . -type f | grep .cpp`

head_files="./stk/include/"

for element in ${source_files[@]}
do
    echo " ==> ${element}"
done

g++ ${source_files} -I ${head_files} -std=c++14 -o ${ProjectName}

echo " === compile done!"