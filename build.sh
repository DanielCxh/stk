#!/bin/bash

start_ts=`date +%s`

ProjectName="stk.elf"

echo " === compile start"

source_files=`find . -type f | grep .cpp`

head_files="./stk/include/"

libs="-lpthread"

for element in ${source_files[@]}
do
    echo " [ FIND ] ${element}"
done

g++ ${source_files} -I ${head_files} -L. ${libs} -std=c++14 -o ${ProjectName}

end_ts=`date +%s`

ts=`expr $end_ts - $start_ts`

echo " === compile done! ..." ${ts}"ms"
