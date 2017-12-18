#import all the necessary modules
from selenium import webdriver
from selenium.common.exceptions import NoSuchElementException, StaleElementReferenceException 
import urllib

#load PhantomJS webdriver and visit the url
driver = webdriver.PhantomJS(executable_path=r'C:\Program Files\phantomjs-2.1.1-windows\bin\phantomjs.exe')
driver.get("http://trai.gov.in/Content/PressReleases.aspx")

#function that downloads the pdf and forms the filename as "date-of-release_pdf-count.pdf"
def downloadFile(date,pdflink,pdfCount):
	filename = date.replace('/','_') + "_{}.pdf".format(pdfCount)
	urllib.urlretrieve(pdflink,filename)

pdfCount = 0
while True:
	linkCount = 0
	while True:
		try:
			#obtian all the div tags having links of pdfs
			divs = driver.find_elements_by_class_name("upcoming_right")
			date = driver.find_element_by_id("ctl00_ContentPlaceHolder1_Repeater_PressRelease_ctl0{}_lbldate".format(linkCount)).text

			#extract link from each div tag obtained above and click on it
			divs[linkCount].find_element_by_tag_name("a").click()
			pdfCount += 1
			
			#from the new page, extract the downloadable link of the pdf and pass to download function for file download
			pdflink = driver.find_element_by_xpath('//*[@id="content"]/div/div[2]/div[3]/div/div[2]/div/ul[2]/li/a').get_attribute("href")
			downloadFile(date,pdflink,pdfCount)

			#find and click on back button; to extract next pdf's link
			driver.find_element_by_id("ctl00_ContentPlaceHolder1_ibBack").click()
			linkCount += 1

			#check if all the links on a page have been travelled, then go to next page, if not, travel the next link
			if not linkCount < len(divs):
				break

		#in case of non existence of an element, handle the exception		
		except NoSuchElementException:
			print "Element not found"
			driver.close()
			exit(1)

		#in case of searching an element on the wrong page, handle the exception
		except StaleElementReferenceException:
			print "Page refreshed or changed; element doesn't exist"
			driver.close()
			exit(1)

	#locate the 'next' button and click on it, and do same as above for next page
	try:
		next = driver.find_element_by_link_text("Next")
		next.click()
	
	#if next button doesn't exist i.e. we are on last past, quit the program 
	except NoSuchElementException:
		print "All pdfs downloaded!"
		break

driver.close()
#for a complete understanding of the program refer write_up.pdf and user_manual.pdf