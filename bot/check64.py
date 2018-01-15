import discord, pycurl, io

def wikicurly(code):
	url = "http://stratzenblitz.wikia.com/wiki/{}".format(code)
	print(url)
	curl = pycurl.Curl()
	curl.setopt(curl.URL, url)
	curl.setopt(curl.WRITEFUNCTION, lambda x: None)
	curl.setopt(curl.FOLLOWLOCATION, True)
	curl.perform()

	status = int(curl.getinfo(curl.HTTP_CODE))
	
	print("wikicurly(%s) -- HTTP %d" % (code,status))
	if(status == 200):
		return "[ "+url+" ]"
	else:
		return None

def imgurcurly(code):
	url = "http://imgur.com/{}".format(code)
	curl = pycurl.Curl()
	curl.setopt(curl.URL, url)
	curl.setopt(curl.WRITEFUNCTION, lambda x: None)
	curl.setopt(curl.FOLLOWLOCATION, True)
	curl.perform()

	status = int(curl.getinfo(curl.HTTP_CODE))
	
	if(status == 200):
		return url
	else:
		return None
	

async def check64(client, M):
	if(M.author == M.server.me): return False

	# get the text in the curlies
	opencurly = M.content.find("{")
	closecurly = M.content.find("}")
	if(opencurly == -1 or closecurly == -1): return False
	code = M.content[opencurly+1:closecurly]
	
	print("len={}".format(len(code)))
	
	wiki = wikicurly(code)
	print(wiki)
	if(wiki != None):
		await client.send_message(M.channel, wiki)
		return
	
	# Dang, not a wiki page.
	imgur = imgurcurly(code)
	if(imgur != None):
		await client.send_message(M.channel, wiki)


