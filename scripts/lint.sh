# Exit if any lines fail
set -e

echo Running cpplint...
cpplint --recursive src/ include/ test/
echo
echo Running cppcheck...
# cppcheck doesn't know about built in c++ libraries, this supresses warnings
cppcheck --enable=all --suppress=missingIncludeSystem src/ include/ test/
echo
echo Passed linters
