#!/usr/bin/python3
import discord, time, subprocess, random, os
from profanity import profanity


from bot.helpers import *
from bot.actions import *
from bot.check64 import *

IGNORE_CHITCHAT = False

os.system("mkdir -p tmp");

with open("token", "r") as f:
	TOKEN = f.read().rstrip()

client = discord.Client();

RAZOR, PREFIX = check_branch()


print("PREFIX =", PREFIX)

print("IGNORE_CHITCHAT =", IGNORE_CHITCHAT)



@client.event
async def on_ready():
	print('Logged in as')
	print(client.user.name)
	print(client.user.id)
	print('------')
	if(RAZOR):
		await client.change_presence(game=discord.Game(name='Chess'))
	else:
		await client.change_presence(game=discord.Game(name='with neurotoxin'))
		
	



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
	
	await check64(client, M)
	
	if(M.content.startswith(PREFIX + 'stratish')):
		await stratish(client, M, M.content[10:])
		return

	if(M.content.startswith(PREFIX + 's') or M.content.startswith(PREFIX+"S")):
		await stratish(client, M, M.content[3:])
		return

	if(M.content.startswith(PREFIX + 'pull') or str(M.author) == "GitHub#0000"):
		await pull(client, M)
		return
	
	if(M.content.startswith(PREFIX + 'make')):
		await make(client, M)
		return
	
	if(M.content.startswith(PREFIX + 'chnick')):
		if(M.author.id == "247841704386756619"):
			await client.change_nickname(M.server.me, M.content[7:])
		else: # This bit shouldn't work with no arguments ^~~~~~~~~~~~~
			await nope(client, M)
		return
	
	if(M.content.startswith(PREFIX + 'reboot')):
		if(M.author.id == "247841704386756619"):
			system("sudo shutdown -r now")
		else:
			await refuse(client, M)
	
	if(M.content.startswith(PREFIX + 'refuse')):
		await refuse(client, M)
		return
	
	if(M.content.startswith(PREFIX + "character")):
		try:
			await client.send_typing(M.channel)
			await client.send_file(M.channel,
				"characters/"+M.content[11:])
		except:
			await nope(client, M)
			
		return
	
	if(M.content.startswith(PREFIX + "files")):
		if(M.content == PREFIX + "files"):
			proc = subprocess.Popen(["ls", "-C", "files"], stdout=subprocess.PIPE)
			(out, err) = proc.communicate()
			out = out.decode()
			await client.send_message(M.channel, "```"+out+"```")
			return
		try:
			await client.send_typing(M.channel)
			await client.send_file(M.channel,
				"files/"+M.content[7:])
		except:
			await nope(client, M)
			

client.run(TOKEN);
