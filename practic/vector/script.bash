#!/bin/bash


make fclean
make CPPFLAGS='-Wall -Wextra -Werror -std=c++11 -D STD' NAME='std.out';
make fclean;
make CPPFLAGS='-Wall -Wextra -Werror -std=c++11' NAME='ft.out';

rm std.log ft.log diff.log;

./std.out > std.log;
./ft.out > ft.log;

diff std.log ft.log > diff.log;

if [ -s diff.log ]; then
    echo "Errors found";
else
    echo "OK";
fi