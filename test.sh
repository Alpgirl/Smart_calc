#!/bin/bash

#Directory for the html-report(deleting)
rm -rf report

#Testing
ctest --test-dir build

#Directory for the report (creating)
mkdir report

#HTML - report
lcov -c -d . -o ./report/name.info
genhtml  ./report/name.info -o report
