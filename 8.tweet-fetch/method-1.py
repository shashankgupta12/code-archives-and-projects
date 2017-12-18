## pip install tweepy

import tweepy
from tweepy import OAuthHandler
import json
 
consumer_key = 'dpDWfLst0yJYi9mnqmIlhG3op'
consumer_secret = 'Z2dkqBGMP21FVGelrc0n3TggxkD4abRwsOV9IjNp89FAru9g36'
access_token = '711116895978557440-5VCynuW5c6Jf1IJEYBbihVueryvoYZy'
access_secret = 'tqq2Tb9kF0h73aLRtJIxQHQTXhf1lEcD46qxouQaOoQhZ'
 
 
auth = OAuthHandler(consumer_key, consumer_secret)
auth.set_access_token(access_token, access_secret)
 
api = tweepy.API(auth)

for tweet in tweepy.Cursor(api.user_timeline).items(1):
    with open('data.json', 'a') as outfile:
    	json.dumps(tweet._json, outfile)