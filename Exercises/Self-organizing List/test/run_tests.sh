#!/bin/zsh

CASES_NUM=$(cd test/test_cases/in && ls | wc -l)
cd main/bin || return

for i in {1..$CASES_NUM}
do
  ./products_self_organizing_linked_list < ../../test/test_cases/in/$i.in > ../../test/test_cases/out/$i.res

  DIFF=$(diff ../../test/test_cases/out/$i.out ../../test/test_cases/out/$i.res)

  if [ "$DIFF" != "" ]
  then
    echo "TEST CASE" $i".in: FAIL" >> ../../test/result.test
  else
    echo "TEST CASE" $i".in: PASS" >> ../../test/result.test
  fi

done

cat ../../test/result.test