input="input"
if [ -d $input ] 
then
	rm -r $input
fi
mkdir $input
g++ testfile.cpp
./a.out