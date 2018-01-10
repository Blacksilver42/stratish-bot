import discord
import time
import subprocess
import random
from profanity import profanity
from os import system

import helpers
import actions

IGNORE_CHITCHAT = False


with open("token", "r") as f:
	TOKEN = f.read().rstrip()

client = discord.Client();

RAZOR = False
try:
	from git import Repo
	repo = Repo('.')
	branch = repo.active_branch

	if(branch.name == "razor"):
		RAZOR = True
		print("*** Razor's edge ***")
except:
	print("Couldn't check branch, assuming master.")
	#TODO: fallback


if(RAZOR):
	PREFIX = "?"
else:
	PREFIX = "/"

print("PREFIX =", PREFIX)

print("IGNORE_CHITCHAT =", IGNORE_CHITCHAT)




###############################################################################



@client.event
async def on_ready():
	print('Logged in as')
	print(client.user.name)
	print(client.user.id)
	print('------')
	#await client.change_presence(game=discord.Game(name='/stratish ...'))
	



@client.event
async def on_message(M):
	if(IGNORE_CHITCHAT):
		# Do we even care?
		try:
			if(M.content[0] != PREFIX): return
		except Exception:
			# No message content, might be a push from github
			if(str(M.author) == "GitHub#0000"):
				await pull(M)
				return
	
	
	print("#"+M.channel.name,"\t<"+str(M.author)+">\t", M.content)
	
	if(M.content.startswith(PREFIX + 'stratish')):
		await stratish(M, M.content[9:])

	if(M.content.startswith(PREFIX + 's') or M.content.startswith(PREFIX+"S")):
		await stratish(M, M.content[3:])

	if(M.content.startswith(PREFIX + 'pull') or str(M.author) == "GitHub#0000"):
		await pull(M)
	
	if(M.content.startswith(PREFIX + 'make')):
		await make(M)
	
	if(M.content.startswith(PREFIX + 'chnick')):
		if(M.author.id == "247841704386756619"):
			await client.change_nickname(M.server.me, M.content[7:])
		else:
			await nope(M)
	
	if(M.content.startswith(PREFIX + 'refuse')):
		await refuse(M)
	
	if(M.content.startswith(PREFIX + "file")):
		await client.send_file(M.channel,
			"characters/"+M.content[6:])


client.run(TOKEN);
