from selenium import webdriver
from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver import ActionChains
from selenium.webdriver.common.keys import Keys

# driver = webdriver.Chrome(executable_path="C:\Users\Shashank Gupta\Desktop\chromedriver")

profile = webdriver.FirefoxProfile()
profile.set_preference('browser.download.folderList', 2) # custom location
profile.set_preference('browser.download.manager.showWhenStarting', False)
profile.set_preference('browser.download.dir', 'C:\Users\Shashank Gupta\Desktop')
profile.set_preference('browser.helperApps.neverAsk.saveToDisk', 'application/pdf')

driver = webdriver.Firefox(profile)
driver.get("http://trai.gov.in/Content/PressReleases.aspx")
assert "Press Release" in driver.title
# actionChains = ActionChains(driver)

divs = driver.find_elements_by_class_name("upcoming_right")

print divs[0].text
link1 = divs[0].find_element_by_tag_name("a")
link1.click()
print "link1 clicked"
link2 = driver.find_element_by_xpath('//*[@id="content"]/div/div[2]/div[3]/div/div[2]/div/ul[2]/li/a')


ActionChains(driver).context_click(link2).send_keys(Keys.ARROW_DOWN).send_keys(Keys.ARROW_DOWN).send_keys(Keys.ARROW_DOWN).send_keys(Keys.ARROW_DOWN).send_keys(Keys.ARROW_DOWN).send_keys(Keys.RETURN).perform()
print "link2 right clicked"

driver.implicitly_wait(30)
driver.close()