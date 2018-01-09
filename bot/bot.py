import discord
import time
import subprocess
import random
from profanity import profanity
from os import system

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


async def wtf(M):
	await client.add_reaction(M, "❓")

async def nope(M):
	await client.add_reaction(M, "🚫")

async def check(M):
	await client.add_reaction(M, "✅")



async def refuse(M):
	proc = subprocess.Popen(["/usr/games/fortune", "bofh-excuses"],
		stdout=subprocess.PIPE)
	(out, err) = proc.communicate()
	out = out.decode()
	msg = "**Error:** " + out.split("\n",2)[2];
	await client.send_message(M.channel,msg)


async def pull(M):
	proc = subprocess.Popen(["git", "pull"], stdout=subprocess.PIPE)
	(out, err) = proc.communicate()
	out = out.decode()
	print("'"+out+"'")
	if(out != "Already up-to-date.\n"):
		await client.send_message(M.channel, "```\n"+out+"\n```")
		make()
	else:
		await check(M)


async def make(M):
	await client.send_typing(M.channel)
	proc = subprocess.Popen(["bot/make.sh"], stdout=subprocess.PIPE)
	(out, err) = proc.communicate()
	out = out.decode()
	await client.send_message(M.channel, "```\n"+out+"\n```")


async def stratish(M, words):
	if(words[0]!=' '):
		await wtf(M)
		return
	
	if(profanity.contains_profanity(words)):
		await refuse(M)
		try:
			await client.delete_message(M)
		finally:
			return
	
	await client.send_typing(M.channel)
	ut = time.strftime("%s")
	tmpfile = "tmp/img-"+str(ut)+".png"
	command = "writer/sbdraw '%s' '%s'" % (words, tmpfile)
	print("$", command)
	system("touch "+tmpfile)
	system(command)
	await client.send_file(M.channel, tmpfile, content="`"+words+"`")
	


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
	# Do we even care?
	try:
		if(M.content[0] != PREFIX): return
	except Exception:
		pass
	
	print("#"+M.channel.name,"\t<"+str(M.author)+">\t", M.content)
	
	if(M.content.startswith(PREFIX + 'stratish')):
		await stratish(M, M.content[9:])

	if(M.content.startswith(PREFIX + 's') or M.content.startswith(PREFIX+"S")):
		await stratish(M, M.content[2:])

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
