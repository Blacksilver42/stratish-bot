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

def check_branch():
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

	return (RAZOR, PREFIX)





###############################################################################
