#!/bin/bash
function do_test() {
    ./main "$1" "$2"
    student=$?
    echo "$2" | grep "^$1$" > /dev/null
    ref=$?
    if [ $student -ne $ref ]; then
        echo "Failed Test: pattern=\"$1\", text=\"$2\"";
        exit 1;
    fi
}

# Write Your Tests Here
# The do_test function tests if your program gives the 
# same result as the reference implementation on the pattern
# and text provided.

#test literals
do_test '' 'XXXXXXXXXXXXX' #should be no match
do_test 'qqqqqqqqqq' 'q' #no match
do_test 'asdfasf' '' #no match
do_test 'UpperCase' 'UpperCase'
do_test 'ALLCAPS' 'ALLCAPS'

#test dot
do_test 'ad.m' 'ada' #should be no match
do_test 'j.e' 'joe' 
do_test 'al.ha..ts.up' 'alphabetsoup'
do_test 'U.pe..ase' 'UpperCase'
do_test '.LLC.PS' 'ALLCAPS'

#test star
do_test 'a*' ''
do_test 'a*B*c*' 'aaaaaBBBBBBBBBBc'
do_test 'ilo*vecs' 'ilooooooooooovecs'
do_test 'adamismyfavprof*' 'adamismyfavproffffffffff'
do_test 'l*m*ao' 'llllllllllmmmmmmao'

#test dot-star
do_test '.*' 'asdfafv'
do_test 'ilove.*' 'ilovezcvadviiii'
do_test '.*.*' 'ggggggasdfasdfjjjjjjjjjj'
do_test 'abc.*def' 'abcUUUUUUUUUdef'
do_test '.*abc.*' 'ssssssabciiiiiiii'

echo '-----------------';
echo 'All Tests Passed!';
