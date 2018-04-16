import subprocess, time, discord
from bot.helpers import *
from profanity import profanity
from os import system

if(__name__ == "__main__"):
	print("?!")
	exit(1)

async def pull(client, M):
	proc = subprocess.Popen(["git", "pull"], stdout=subprocess.PIPE)
	(out, err) = proc.communicate()
	out = out.decode()
	#print("'"+out+"'")
	if(out != "Already up-to-date.\n"):
		await client.send_message(M.channel, "```\n"+out+"\n```")
		make()
	else:
		await check(client, M)


async def make(client, M):
	await client.send_typing(M.channel)
	proc = subprocess.Popen(["bot/make.sh"], stdout=subprocess.PIPE)
	(out, err) = proc.communicate()
	out = out.decode()
	await client.send_message(M.channel, "```\n"+out+"\n```")


async def stratish(client, M, words):
	#await client.send_message(M.channel, "Currently broken, sorry :(")
	#return

	if(profanity.contains_profanity(words)):
		await refuse(client, M)
		try:
			await client.delete_message(M)
		finally:
			return
	
	await client.send_typing(M.channel)
	ut = time.strftime("%s")
	font = "sans"
	tmpfile = "tmp/img-"+str(ut)+".png"
	command = "SbTeX/sbtex %s -o %s -f %s" % (words, tmpfile, font)
	print("$", command)
	system("touch "+tmpfile)
	system(command)
	await client.send_file(M.channel, tmpfile, content="`"+words+"`")
	with open("bot.log", "a") as f:
		f.write("<{}> {}\n".format(str(M.author),words))
	
