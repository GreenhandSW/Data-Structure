import os
import sys

def ListDirectory(Path, Depth):
	try:
		filename=Path.rsplit('\\',1)[1]
		print("  "*Depth, filename)
		if os.path.isdir(Path):
			for subfile in os.listdir(Path):
				ListDirectory(Path+'\\'+subfile, Depth+1)

	except FileExistsError as e:
		raise("File or directory doesn't exist\n")
	else:
		pass
	finally:
		pass

if __name__ == '__main__':
	ListDirectory(sys.argv[1],0)