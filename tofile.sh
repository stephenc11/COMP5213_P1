for file in ../extracted/*.txt
do
#	  java -cp HLTA.jar:HLTA-deps.jar tm.pdf.ExtractText  extracted
	fname=$(basename "$file")
	fname="${fname%.*}"
	mkdir ../extracted/$fname
	mv $file ../extracted/$fname/$fname.txt
	java -cp HLTA.jar:HLTA-deps.jar tm.text.Convert $fname 2000 1 ../extracted/$fname	 
done
