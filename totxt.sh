mkdir extracted
for file in ./PMC0050XXXXX/*.pdf
do
	fname=$(basename "$file")
	fname="${fname%.*}"
	
	##Move preprocessed .pdf to .txt
	java -cp HLTA.jar:HLTA-deps.jar tm.pdf.ExtractText $file ./extracted
done
