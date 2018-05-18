import os
import sys

def ListAndSizeDirectory(Path, Depth):
	try:
		total_size=0
		filename=Path.rsplit('\\',1)[1]
		if os.path.isdir(Path):
			for subfile in os.listdir(Path):
				total_size=total_size+ListAndSizeDirectory(Path+'\\'+subfile, Depth+1)
		else:
			total_size=os.path.getsize(Path)
		print("  "*Depth, filename," "*(50-len(filename)-2*Depth), total_size)

		return total_size

	except FileExistsError as e:
		raise("File or directory doesn't exist\n")
	else:
		pass
	finally:
		pass

if __name__ == '__main__':
	ListAndSizeDirectory(sys.argv[1],0)