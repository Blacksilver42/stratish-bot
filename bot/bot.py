import discord
import time
import subprocess


with open("token", "r") as f:
	TOKEN = f.read().rstrip()

client = discord.Client();


async def pull():
	proc = subprocess.Popen(["git", "pull"], stdout=subprocess.PIPE)
	(out, err) = proc.communicate()
	out = out.decode()
	await client.send_message(M.channel, "`"+out+"`")

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
	print("#"+M.channel.name,"\t<"+str(M.author)+">\t", M.content)
	
	if(M.content.startswith('/stratish')):
		await client.send_typing(M.channel)
		words=M.content[10:]
		ut = time.strftime("%s")
		tmpfile = "tmp/img-"+str(ut)+".png"
		command = "writer/sbdraw '%s' >%s" % (words, tmpfile)
		print("$", command)
		system("touch "+tmpfile)
		system(command)
		await client.send_file(M.channel, tmpfile)
	
	if(M.content.startswith('/pull')):
		await pull()
	
	if(M.content.startswith('/make')):
		proc = subprocess.Popen(["make", "-C", "writer"], stdout=subprocess.PIPE)
		(out, err) = proc.communicate()
		out = out.decode()
		await client.send_message(M.channel, "```\n"+out+"\n```")
	
	if(M.content.startswith('/chnick')):
		if(M.author.id == "247841704386756619"):
			await client.change_nickname(M.server.me, M.content[7:])
		else:
			await client.send_message(M.channel, "no.")
	
	if(str(M.author) == "GitHub#0000"):
		await pull()
		

client.run(TOKEN);
