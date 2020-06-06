
ProjectName="stk"

echo " === compile start"

source_files=`find . -type f | grep .cpp`

for element in ${source_files[@]}
do
    echo " ==> ${element}"
done

g++ ${source_files} -std=c++14 -shared -fPIC -o libstk.so

echo " === compile done!"