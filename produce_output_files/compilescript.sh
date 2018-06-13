g++ temp.cpp

input="input"
output="output" 
ext=".txt"
padding="0"

if [ -d $output ]
then
	rm -r $output
fi

mkdir $output

for idx in {0..0}; do
	if [ $idx -lt 10 ] 
	then
		tempin=$input$padding$idx$ext
		tempout=$output$padding$idx$ext
	else
		tempin=$input$idx$ext
		tempout=$output$idx$ext
	fi
	./a.out <$input/$tempin> $output/$tempout 
	echo "$tempin $tempout"
done
