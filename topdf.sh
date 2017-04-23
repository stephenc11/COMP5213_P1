for file in ./PMC0050XXXXX/*.txt
do
	fname=$(basename "$file")
	fname="${fname%.*}" ###Get basename of the file

	##Transcribe .txt to .pdf 
	./text2pdf $file > ./PMC0050XXXXX/$fname.pdf;
done

