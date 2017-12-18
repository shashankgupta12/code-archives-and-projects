import textract
text = textract.process('abc.pdf', method='pdfminer')