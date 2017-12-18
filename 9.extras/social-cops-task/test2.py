import urllib

url = "http://trai.gov.in/WriteReadData/PressRealease/Document/PR_No.20of2016.pdf"
num=0
urllib.urlretrieve(url,"ab%d.pdf" % num)