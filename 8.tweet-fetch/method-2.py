from requests_oauthlib import OAuth1
import requests

CONSUMER_KEY = 'dpDWfLst0yJYi9mnqmIlhG3op'
CONSUMER_SECRET = 'Z2dkqBGMP21FVGelrc0n3TggxkD4abRwsOV9IjNp89FAru9g36'
TWITTER_TOKEN = '711116895978557440-5VCynuW5c6Jf1IJEYBbihVueryvoYZy'
TWITTER_TOKEN_SECRET = 'tqq2Tb9kF0h73aLRtJIxQHQTXhf1lEcD46qxouQaOoQhZ'

oauth = OAuth1(CONSUMER_KEY, client_secret=CONSUMER_SECRET, resource_owner_key=TWITTER_TOKEN, resource_owner_secret=TWITTER_TOKEN_SECRET)
req = requests.get(url="https://api.twitter.com/1.1/statuses/user_timeline.json?screen_name={}&count={}".format("shashnk_gupta", 1), auth=oauth)

for tweet in req.json():
  print(tweet['text'])
  print()