import discord

async def wtf(client, M):
	await client.add_reaction(M, "❓")

async def nope(client, M):
	await client.add_reaction(M, "🚫")

async def check(client, M):
	await client.add_reaction(M, "✅")



async def refuse(client, M):
	proc = subprocess.Popen(["/usr/games/fortune", "bofh-excuses"],
		stdout=subprocess.PIPE)
	(out, err) = proc.communicate()
	out = out.decode()
	msg = "**Error:** " + out.split("\n",2)[2];
	await client.send_message(M.channel,msg)
